
#include <unknwn.h>

#include "impl_webrtc_VideoCaptureMediaSink.h"

#ifdef WINUWP
#ifdef CPPWINRT_VERSION

#include <zsLib/String.h>
#include <zsLib/IMessageQueueThread.h>

#include <wrapper/impl_org_webRtc_pre_include.h>
#include "rtc_base/logging.h"
#include <wrapper/impl_org_webRtc_post_include.h>

#include <strsafe.h>

#include <mferror.h>
#include <mfapi.h>

#include <windows.foundation.h>

using zsLib::String;
using zsLib::Time;
using zsLib::Seconds;
using zsLib::Milliseconds;
using zsLib::AutoRecursiveLock;

using winrt::Windows::Foundation::IPropertyValue;
using winrt::Windows::Foundation::PropertyType;
using winrt::Windows::Media::IMediaExtension;
using winrt::Windows::Media::MediaProperties::IMediaEncodingProperties;

namespace {

  //-----------------------------------------------------------------------------
  inline void ThrowIfError(HRESULT hr) {
    if (FAILED(hr)) {
      winrt::throw_hresult(hr);
    }
  }

  //-----------------------------------------------------------------------------
  inline void Throw(HRESULT hr) {
    assert(FAILED(hr));
    winrt::throw_hresult(hr);
  }

  //-----------------------------------------------------------------------------
  static void AddAttribute(_In_ GUID guidKey, _In_ IPropertyValue const& value,
    _In_ IMFAttributes *pAttr) {
    PropertyType type = value.Type();
    switch (type) {
    case PropertyType::UInt8Array:
      {
        winrt::com_array<BYTE> arr;
        value.GetUInt8Array(arr);

        ThrowIfError(pAttr->SetBlob(guidKey, arr.data(), arr.size()));
      }
      break;

    case PropertyType::Double:
      {
        ThrowIfError(pAttr->SetDouble(guidKey, value.GetDouble()));
      }
      break;

    case PropertyType::Guid:
      {
        ThrowIfError(pAttr->SetGUID(guidKey, value.GetGuid()));
      }
      break;

    case PropertyType::String:
      {
        ThrowIfError(pAttr->SetString(guidKey, value.GetString().c_str()));
      }
      break;

    case PropertyType::UInt32:
      {
        ThrowIfError(pAttr->SetUINT32(guidKey, value.GetUInt32()));
      }
      break;

    case PropertyType::UInt64:
      {
        ThrowIfError(pAttr->SetUINT64(guidKey, value.GetUInt64()));
      }
      break;
    }
  }

  //-----------------------------------------------------------------------------
  void ConvertPropertiesToMediaType(
    _In_ IMediaEncodingProperties const& mep,
    _Outptr_ IMFMediaType **ppMT) {
    if (mep == nullptr || ppMT == nullptr) {
      winrt::throw_hresult(E_INVALIDARG);
    }
    winrt::com_ptr<IMFMediaType> spMT;
    IPropertyValue propertyValue;
    *ppMT = nullptr;
    ThrowIfError(MFCreateMediaType(spMT.put()));

    auto it = mep.Properties().First();

    while (it.HasCurrent()) {
      auto currentValue = it.Current();
      propertyValue = nullptr;
      currentValue.Value().as(propertyValue);
      AddAttribute(currentValue.Key(),
        propertyValue,
        spMT.get());
      it.MoveNext();
    }

    propertyValue = nullptr;
    mep.Properties().Lookup(MF_MT_MAJOR_TYPE).as(propertyValue);
    GUID guidMajorType = propertyValue.GetGuid();

    if (guidMajorType != MFMediaType_Video) {
      Throw(E_UNEXPECTED);
    }

    *ppMT = spMT.detach();
  }

  //-----------------------------------------------------------------------------
  DWORD GetStreamId() {
    return 0;
  }
}  // namespace

namespace webrtc
{
  //-----------------------------------------------------------------------------
  VideoCaptureStreamSink::VideoCaptureStreamSink(DWORD dwIdentifier)
    : _cRef(1),
    _dwIdentifier(dwIdentifier),
    _state(State_TypeNotSet),
    _isShutdown(false),
    _fGetStartTimeFromSample(false),
    _startTime(0),
    _workQueueId(0),
    _pParent(nullptr),
    _workQueueCB(this, &VideoCaptureStreamSink::OnDispatchWorkItem) {
    ZeroMemory(&_guiCurrentSubtype, sizeof(_guiCurrentSubtype));
  }

  //-----------------------------------------------------------------------------
  VideoCaptureStreamSink::~VideoCaptureStreamSink() {
    assert(_isShutdown);
  }


  //-----------------------------------------------------------------------------
  // IUnknown methods
  IFACEMETHODIMP VideoCaptureStreamSink::QueryInterface(
    REFIID riid,
    void **ppv) {
    if (ppv == nullptr) {
      return E_POINTER;
    }
    (*ppv) = nullptr;

    HRESULT hr = S_OK;
    if (riid == IID_IUnknown ||
      riid == IID_IMFStreamSink ||
      riid == IID_IMFMediaEventGenerator) {
      (*ppv) = static_cast<IMFStreamSink*>(this);
      AddRef();
    } else if (riid == IID_IMFMediaTypeHandler) {
      (*ppv) = static_cast<IMFMediaTypeHandler*>(this);
      AddRef();
    } else {
      hr = E_NOINTERFACE;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP_(ULONG) VideoCaptureStreamSink::AddRef() {
    return InterlockedIncrement(&_cRef);
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP_(ULONG) VideoCaptureStreamSink::Release() {
    ULONG cRef = InterlockedDecrement(&_cRef);
    if (cRef == 0) {
      delete this;
    }
    return cRef;
  }

  //-----------------------------------------------------------------------------
  // IMFMediaEventGenerator methods.
  // Note: These methods call through to the event queue helper object.
  IFACEMETHODIMP VideoCaptureStreamSink::BeginGetEvent(
    IMFAsyncCallback *pCallback,
    IUnknown *punkState) {
    HRESULT hr = S_OK;

    rtc::CritScope lock(&_critSec);

    if (_isShutdown) {
      hr = MF_E_SHUTDOWN;
    }

    if (SUCCEEDED(hr)) {
      hr = _spEventQueue->BeginGetEvent(pCallback, punkState);
    }

    if (!SUCCEEDED(hr)) {
      RTC_LOG_F(LS_ERROR) << "Capture stream sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP VideoCaptureStreamSink::EndGetEvent(
    IMFAsyncResult *pResult,
    IMFMediaEvent **ppEvent) {
    HRESULT hr = S_OK;

    rtc::CritScope lock(&_critSec);

    if (_isShutdown) {
      hr = MF_E_SHUTDOWN;
    }

    if (SUCCEEDED(hr)) {
      hr = _spEventQueue->EndGetEvent(pResult, ppEvent);
    }

    if (!SUCCEEDED(hr)) {
      RTC_LOG_F(LS_ERROR) << "Capture stream sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP VideoCaptureStreamSink::GetEvent(
    DWORD dwFlags,
    IMFMediaEvent **ppEvent) {
    // NOTE:
    // GetEvent can block indefinitely, so we don't hold the lock.
    // This requires some juggling with the event queue pointer.

    HRESULT hr = S_OK;

    winrt::com_ptr<IMFMediaEventQueue> spQueue;

    {
      rtc::CritScope lock(&_critSec);

      // Check shutdown
      if (_isShutdown) {
        hr = MF_E_SHUTDOWN;
      }

      // Get the pointer to the event queue.
      if (SUCCEEDED(hr)) {
        spQueue = _spEventQueue;
      }
    }

    // Now get the event.
    if (SUCCEEDED(hr)) {
      hr = spQueue->GetEvent(dwFlags, ppEvent);
    }

    if (!SUCCEEDED(hr)) {
      RTC_LOG_F(LS_ERROR) << "Capture stream sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP VideoCaptureStreamSink::QueueEvent(
    MediaEventType met,
    REFGUID guidExtendedType,
    HRESULT hrStatus,
    PROPVARIANT const *pvValue) {
    HRESULT hr = S_OK;

    rtc::CritScope lock(&_critSec);

    if (_isShutdown) {
      hr = MF_E_SHUTDOWN;
    }

    if (SUCCEEDED(hr)) {
      hr = _spEventQueue->QueueEventParamVar(
        met, guidExtendedType, hrStatus, pvValue);
    }

    if (!SUCCEEDED(hr)) {
      RTC_LOG_F(LS_ERROR) << "Capture stream sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  /// IMFStreamSink methods
  IFACEMETHODIMP VideoCaptureStreamSink::GetMediaSink(
    IMFMediaSink **ppMediaSink) {
    if (ppMediaSink == nullptr) {
      return E_INVALIDARG;
    }

    rtc::CritScope lock(&_critSec);

    HRESULT hr = S_OK;
    if (_isShutdown) {
      hr = MF_E_SHUTDOWN;
    }

    if (SUCCEEDED(hr)) {
      _spSink.get()->QueryInterface(IID_IMFMediaSink,
        reinterpret_cast<void**>(ppMediaSink));
    } else {
      RTC_LOG_F(LS_ERROR) << "Capture stream sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP VideoCaptureStreamSink::GetIdentifier(
    DWORD *pdwIdentifier) {
    if (pdwIdentifier == nullptr) {
      return E_INVALIDARG;
    }

    rtc::CritScope lock(&_critSec);

    HRESULT hr = S_OK;
    if (_isShutdown) {
      hr = MF_E_SHUTDOWN;
    }

    if (SUCCEEDED(hr)) {
      *pdwIdentifier = _dwIdentifier;
    } else {
      RTC_LOG_F(LS_ERROR) << "Capture stream sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP VideoCaptureStreamSink::GetMediaTypeHandler(
    IMFMediaTypeHandler **ppHandler) {
    if (ppHandler == nullptr) {
      return E_INVALIDARG;
    }

    rtc::CritScope lock(&_critSec);

    HRESULT hr = S_OK;
    if (_isShutdown) {
      hr = MF_E_SHUTDOWN;
    }

    // This stream object acts as its own type handler, so we QI ourselves.
    if (SUCCEEDED(hr)) {
      hr = QueryInterface(IID_IMFMediaTypeHandler,
        reinterpret_cast<void**>(ppHandler));
    }

    if (!SUCCEEDED(hr)) {
      RTC_LOG_F(LS_ERROR) << "Capture stream sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP VideoCaptureStreamSink::ProcessSample(IMFSample *pSample)
  {
    if (pSample == nullptr)
      return E_INVALIDARG;

    HRESULT hr = S_OK;

    rtc::CritScope lock(&_critSec);

    if (_isShutdown) {
      hr = MF_E_SHUTDOWN;
    }

    if (SUCCEEDED(hr)) {
      hr = ValidateOperation(OpProcessSample);
    }

    if (SUCCEEDED(hr)) {
      if (SUCCEEDED(hr)) {
        winrt::com_ptr<IMFSample> cpSample;
        cpSample.copy_from(pSample);
        _sampleQueue.push(cpSample);
      }

      // Unless we are paused, start an async operation to
      // dispatch the next sample.
      if (SUCCEEDED(hr)) {
        if (_state != State_Paused) {
          hr = QueueAsyncOperation(OpProcessSample);
        }
      }
    }

    if (!SUCCEEDED(hr)) {
      RTC_LOG_F(LS_ERROR) << "Capture stream sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP VideoCaptureStreamSink::PlaceMarker(
    MFSTREAMSINK_MARKER_TYPE eMarkerType,
    const PROPVARIANT *pvarMarkerValue,
    const PROPVARIANT *pvarContextValue) {

    rtc::CritScope lock(&_critSec);

    HRESULT hr = S_OK;
    winrt::com_ptr<IMarker> spMarker;

    if (_isShutdown) {
      hr = MF_E_SHUTDOWN;
    }

    if (SUCCEEDED(hr)) {
      hr = ValidateOperation(OpPlaceMarker);
    }

    if (SUCCEEDED(hr)) {
      hr = Marker::Create(eMarkerType, pvarMarkerValue, pvarContextValue, spMarker.put());
    }

    if (SUCCEEDED(hr)) {
      _sampleQueue.push(spMarker);
    }

    // Unless we are paused, start an async operation to
    // dispatch the next sample/marker.
    if (SUCCEEDED(hr)) {
      if (_state != State_Paused) {
        hr = QueueAsyncOperation(OpPlaceMarker);
      }
    }

    if (!SUCCEEDED(hr)) {
      RTC_LOG_F(LS_ERROR) << "Capture stream sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  // Discards all samples that were not processed yet.
  IFACEMETHODIMP VideoCaptureStreamSink::Flush() {
    rtc::CritScope lock(&_critSec);
    HRESULT hr = S_OK;
    try {
      if (_isShutdown) {
        hr = MF_E_SHUTDOWN;
      }
      ThrowIfError(hr);

      DropSamplesFromQueue();
    } catch (winrt::hresult_error const& exc) {
      hr = exc.code();
    }

    if (!SUCCEEDED(hr)) {
      RTC_LOG_F(LS_ERROR) << "Capture stream sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  /// IMFMediaTypeHandler methods
  // Check if a media type is supported.
  IFACEMETHODIMP VideoCaptureStreamSink::IsMediaTypeSupported(
    /* [in] */ IMFMediaType *pMediaType,
    /* [out] */ IMFMediaType **ppMediaType) {
    if (pMediaType == nullptr) {
      return E_INVALIDARG;
    }

    rtc::CritScope lock(&_critSec);

    GUID majorType = GUID_NULL;

    HRESULT hr = S_OK;
    if (_isShutdown) {
      hr = MF_E_SHUTDOWN;
    }

    if (SUCCEEDED(hr)) {
      hr = pMediaType->GetGUID(MF_MT_MAJOR_TYPE, &majorType);
    }

    // First make sure it's video or audio type.
    if (SUCCEEDED(hr)) {
      if (majorType != MFMediaType_Video) {
        hr = MF_E_INVALIDTYPE;
      }
    }

    if (SUCCEEDED(hr) && _spCurrentType != nullptr) {
      GUID guiNewSubtype;
      if (FAILED(pMediaType->GetGUID(MF_MT_SUBTYPE, &guiNewSubtype)) ||
        guiNewSubtype != _guiCurrentSubtype) {
        hr = MF_E_INVALIDTYPE;
      }
    }

    if (ppMediaType) {
      *ppMediaType = nullptr;
    }

    if (!SUCCEEDED(hr)) {
      RTC_LOG_F(LS_ERROR) << "Capture stream sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  // Return the number of preferred media types.
  IFACEMETHODIMP VideoCaptureStreamSink::GetMediaTypeCount(
    DWORD *pdwTypeCount) {
    if (pdwTypeCount == nullptr) {
      return E_INVALIDARG;
    }

    rtc::CritScope lock(&_critSec);

    HRESULT hr = S_OK;
    if (_isShutdown) {
      hr = MF_E_SHUTDOWN;
    }

    if (SUCCEEDED(hr)) {
      *pdwTypeCount = 1;
    } else {
      RTC_LOG_F(LS_ERROR) << "Capture stream sink error: " << hr;
    }

    return hr;
  }


  //-----------------------------------------------------------------------------
  // Return a preferred media type by index.
  IFACEMETHODIMP VideoCaptureStreamSink::GetMediaTypeByIndex(
    /* [in] */ DWORD dwIndex,
    /* [out] */ IMFMediaType **ppType) {
    if (ppType == nullptr) {
      return E_INVALIDARG;
    }

    rtc::CritScope lock(&_critSec);

    HRESULT hr = S_OK;
    if (_isShutdown) {
      hr = MF_E_SHUTDOWN;
    }

    if (dwIndex > 0) {
      hr = MF_E_NO_MORE_TYPES;
    } else {
      *ppType = _spCurrentType.get();
      if (*ppType != nullptr) {
        (*ppType)->AddRef();
      }
    }

    if (!SUCCEEDED(hr)) {
      RTC_LOG_F(LS_ERROR) << "Capture stream sink error: " << hr;
    }

    return hr;
  }


  //-----------------------------------------------------------------------------
  // Set the current media type.
  IFACEMETHODIMP VideoCaptureStreamSink::SetCurrentMediaType(
    IMFMediaType *pMediaType) {
    HRESULT hr = S_OK;
    try {
      if (pMediaType == nullptr) {
        Throw(E_INVALIDARG);
      }
      rtc::CritScope lock(&_critSec);

      if (_isShutdown) {
        hr = MF_E_SHUTDOWN;
      }
      ThrowIfError(hr);

      // We don't allow format changes after streaming starts.
      ThrowIfError(ValidateOperation(OpSetMediaType));

      // We set media type already
      if (_state >= State_Ready) {
        ThrowIfError(IsMediaTypeSupported(pMediaType, nullptr));
      }

      GUID guiMajorType;
      pMediaType->GetMajorType(&guiMajorType);

      _spCurrentType = nullptr;
      ThrowIfError(MFCreateMediaType(_spCurrentType.put()));
      ThrowIfError(pMediaType->CopyAllItems(_spCurrentType.get()));
      ThrowIfError(_spCurrentType->GetGUID(MF_MT_SUBTYPE, &_guiCurrentSubtype));
      if (_state < State_Ready) {
        _state = State_Ready;
      } else if (_state > State_Ready) {
        winrt::com_ptr<IMFMediaType> spType;
        ThrowIfError(MFCreateMediaType(spType.put()));
        ThrowIfError(pMediaType->CopyAllItems(spType.get()));
        ProcessFormatChange(spType.get());
      }
    } catch (winrt::hresult_error const& exc) {
      hr = exc.code();
    }

    if (!SUCCEEDED(hr)) {
      RTC_LOG_F(LS_ERROR) << "Capture stream sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  // Return the current media type, if any.
  IFACEMETHODIMP VideoCaptureStreamSink::GetCurrentMediaType(
    IMFMediaType **ppMediaType) {
    if (ppMediaType == nullptr) {
      return E_INVALIDARG;
    }

    rtc::CritScope lock(&_critSec);

    HRESULT hr = S_OK;
    if (_isShutdown) {
      hr = MF_E_SHUTDOWN;
    }

    if (SUCCEEDED(hr)) {
      if (_spCurrentType == nullptr) {
        hr = MF_E_NOT_INITIALIZED;
      }
    }

    if (SUCCEEDED(hr)) {
      *ppMediaType = _spCurrentType.get();
      (*ppMediaType)->AddRef();
    } else {
      RTC_LOG_F(LS_ERROR) << "Capture stream sink error: " << hr;
    }

    return hr;
  }


  //-----------------------------------------------------------------------------
  // Return the major type GUID.
  IFACEMETHODIMP VideoCaptureStreamSink::GetMajorType(GUID *pguidMajorType) {
    if (pguidMajorType == nullptr) {
      return E_INVALIDARG;
    }

    if (!_spCurrentType) {
      return MF_E_NOT_INITIALIZED;
    }

    *pguidMajorType = MFMediaType_Video;

    return S_OK;
  }


  //-----------------------------------------------------------------------------
  // private methods
  HRESULT VideoCaptureStreamSink::Initialize(
    VideoCaptureMediaSink *pParent,
    ISinkCallback *callback) {
    assert(pParent != nullptr);

    HRESULT hr = S_OK;

    // Create the event queue helper.
    _spEventQueue = nullptr;
    hr = MFCreateEventQueue(_spEventQueue.put());

    // Allocate a new work queue for async operations.
    if (SUCCEEDED(hr)) {
      hr = MFAllocateSerialWorkQueue(
        MFASYNC_CALLBACK_QUEUE_STANDARD, &_workQueueId);
    }

    if (SUCCEEDED(hr)) {
      _spSink.copy_from(pParent);
      _pParent = pParent;
      _callback = callback;
    } else {
      RTC_LOG_F(LS_ERROR) << "Capture stream sink error: " << hr;
    }

    return hr;
  }


  //-----------------------------------------------------------------------------
  // Called when the presentation clock starts.
  HRESULT VideoCaptureStreamSink::Start(MFTIME start) {
    rtc::CritScope lock(&_critSec);

    HRESULT hr = S_OK;

    hr = ValidateOperation(OpStart);

    if (SUCCEEDED(hr)) {
      if (start != PRESENTATION_CURRENT_POSITION) {
        _startTime = start;        // Cache the start time.
        _fGetStartTimeFromSample = false;
      } else {
        _fGetStartTimeFromSample = true;
      }
      _state = State_Started;
      hr = QueueAsyncOperation(OpStart);
    }

    if (!SUCCEEDED(hr)) {
      RTC_LOG_F(LS_ERROR) << "Capture stream sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  // Called when the presentation clock stops.
  HRESULT VideoCaptureStreamSink::Stop() {
    rtc::CritScope lock(&_critSec);

    HRESULT hr = S_OK;

    hr = ValidateOperation(OpStop);

    if (SUCCEEDED(hr)) {
      _state = State_Stopped;
      hr = QueueAsyncOperation(OpStop);
    }

    if (!SUCCEEDED(hr)) {
      RTC_LOG_F(LS_ERROR) << "Capture stream sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  // Called when the presentation clock pauses.
  HRESULT VideoCaptureStreamSink::Pause() {
    rtc::CritScope lock(&_critSec);

    HRESULT hr = S_OK;

    hr = ValidateOperation(OpPause);

    if (SUCCEEDED(hr)) {
      _state = State_Paused;
      hr = QueueAsyncOperation(OpPause);
    }

    if (!SUCCEEDED(hr)) {
      RTC_LOG_F(LS_ERROR) << "Capture stream sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  // Called when the presentation clock restarts.
  HRESULT VideoCaptureStreamSink::Restart() {
    rtc::CritScope lock(&_critSec);

    HRESULT hr = S_OK;

    hr = ValidateOperation(OpRestart);

    if (SUCCEEDED(hr)) {
      _state = State_Started;
      hr = QueueAsyncOperation(OpRestart);
    }

    if (!SUCCEEDED(hr)) {
      RTC_LOG_F(LS_ERROR) << "Capture stream sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  // Class-static matrix of operations vs states.
  // If an entry is TRUE, the operation is valid from that state.
  BOOL VideoCaptureStreamSink::ValidStateMatrix
    [VideoCaptureStreamSink::State_Count]
    [VideoCaptureStreamSink::Op_Count] = {
    // States:    Operations:
    //            SetType  Start  Restart  Pause  Stop  Sample Marker
    /* NotSet */  TRUE, FALSE, FALSE, FALSE, FALSE, FALSE, FALSE,

    /* Ready */   TRUE, TRUE, FALSE, TRUE, TRUE, FALSE, TRUE,

    /* Start */   TRUE, TRUE, FALSE, TRUE, TRUE, TRUE, TRUE,

    /* Pause */   TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE,

    /* Stop */    TRUE, TRUE, FALSE, FALSE, TRUE, FALSE, TRUE,
  };

  //-----------------------------------------------------------------------------
  // Checks if an operation is valid in the current state.
  HRESULT VideoCaptureStreamSink::ValidateOperation(StreamOperation op) {
    assert(!_isShutdown);

    if (ValidStateMatrix[_state][op]) {
      return S_OK;
    } else if (_state == State_TypeNotSet) {
      return MF_E_NOT_INITIALIZED;
    } else {
      return MF_E_INVALIDREQUEST;
    }
  }

  //-----------------------------------------------------------------------------
  // Shuts down the stream sink.
  HRESULT VideoCaptureStreamSink::Shutdown() {
    rtc::CritScope lock(&_critSec);

    if (!_isShutdown) {
      if (_spEventQueue) {
        _spEventQueue->Shutdown();
      }

      MFUnlockWorkQueue(_workQueueId);

      while (!_sampleQueue.empty()) {
        _sampleQueue.pop();
      }

      _spSink = nullptr;
      _spEventQueue = nullptr;
      _spByteStream = nullptr;
      _spCurrentType = nullptr;

      _isShutdown = true;
    }

    return S_OK;
  }

  //-----------------------------------------------------------------------------
  // Puts an async operation on the work queue.
  HRESULT VideoCaptureStreamSink::QueueAsyncOperation(StreamOperation op) {
    HRESULT hr = S_OK;
    winrt::com_ptr<AsyncOperation> spOp;
    spOp.attach(new AsyncOperation(op));  // Created with ref count = 1
    if (!spOp) {
      hr = E_OUTOFMEMORY;
    }

    if (SUCCEEDED(hr)) {
      hr = MFPutWorkItem2(_workQueueId, 0, &_workQueueCB, spOp.get());
    }

    if (!SUCCEEDED(hr)) {
      RTC_LOG_F(LS_ERROR) << "Capture stream sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  HRESULT VideoCaptureStreamSink::OnDispatchWorkItem(
    IMFAsyncResult *pAsyncResult) {
    try {
      winrt::com_ptr<IUnknown> spState;

      ThrowIfError(pAsyncResult->GetState(spState.put()));

      // The state object is a AsyncOperation object.
      AsyncOperation *pOp = static_cast<AsyncOperation *>(spState.get());
      StreamOperation op = pOp->_op;

      switch (op) {
      case OpStart:
      case OpRestart:
        // Send MEStreamSinkStarted.
        ThrowIfError(QueueEvent(MEStreamSinkStarted, GUID_NULL, S_OK, nullptr));

        // There might be samples queue from earlier (ie, while paused).
        bool fRequestMoreSamples;
        fRequestMoreSamples = DropSamplesFromQueue();
        if (fRequestMoreSamples && !_isShutdown) {
          // If false there is no samples in the queue now so request one
          ThrowIfError(
            QueueEvent(MEStreamSinkRequestSample, GUID_NULL, S_OK, nullptr));
        }
        break;

      case OpStop:
        // Drop samples from queue.
        DropSamplesFromQueue();

        // Send the event even if the previous call failed.
        ThrowIfError(QueueEvent(MEStreamSinkStopped, GUID_NULL, S_OK, nullptr));
        break;

      case OpPause:
        ThrowIfError(QueueEvent(MEStreamSinkPaused, GUID_NULL, S_OK, nullptr));
        break;

      case OpProcessSample:
      case OpPlaceMarker:
      case OpSetMediaType:
        DispatchProcessSample(pOp);
        break;
      }
    } catch (winrt::hresult_error const& exc) {
      HandleError(exc.code());
    }
    return S_OK;
  }

  // Complete a ProcessSample request.
  void VideoCaptureStreamSink::DispatchProcessSample(AsyncOperation *pOp) {
    assert(pOp != nullptr);
    bool fRequestMoreSamples = SendSampleFromQueue();

    // Ask for another sample
    if (fRequestMoreSamples && !_isShutdown) {
      if (pOp->_op == OpProcessSample) {
        ThrowIfError(
          QueueEvent(MEStreamSinkRequestSample, GUID_NULL, S_OK, nullptr));
      }
    }
  }

  //-----------------------------------------------------------------------------
  // Drop samples in the queue
  bool VideoCaptureStreamSink::DropSamplesFromQueue() {
    ProcessSamplesFromQueue(true);
    return true;
  }

  //-----------------------------------------------------------------------------
  // Send sample from the queue
  bool VideoCaptureStreamSink::SendSampleFromQueue() {
    return ProcessSamplesFromQueue(false);
  }

  //-----------------------------------------------------------------------------
  bool VideoCaptureStreamSink::ProcessSamplesFromQueue(bool fFlush) {
    bool fNeedMoreSamples = false;

    winrt::com_ptr<IUnknown> spunkSample;

    bool fSendSamples = true;

    {
      rtc::CritScope lock(&_critSec);

      if (_sampleQueue.size() == 0) {
        fNeedMoreSamples = true;
        fSendSamples = false;
      } else {
        spunkSample = _sampleQueue.front();
        _sampleQueue.pop();
      }
    }

    while (fSendSamples) {
      winrt::com_ptr<IMFSample> spSample;
      bool fProcessingSample = false;
      assert(spunkSample);

      if (spunkSample.try_as(spSample)) {
        assert(spSample);
        winrt::com_ptr<IMFMediaBuffer> spMediaBuffer;
        HRESULT hr = spSample->GetBufferByIndex(0, spMediaBuffer.put());
        if (FAILED(hr)) {
          break;
        }

        _callback->OnSample(spSample);

        if (!fFlush) {
          fProcessingSample = true;
        }
      } else {
        winrt::com_ptr<IMarker> spMarker;
        if (spunkSample.try_as(spMarker)) {
          MFSTREAMSINK_MARKER_TYPE markerType;
          PROPVARIANT var;
          PropVariantInit(&var);
          ThrowIfError(spMarker->GetMarkerType(&markerType));
          ThrowIfError(spMarker->GetContext(&var));

          HRESULT hr = QueueEvent(MEStreamSinkMarker, GUID_NULL, S_OK, &var);

          PropVariantClear(&var);

          ThrowIfError(hr);
        }
      }

      {
        rtc::CritScope lock(&_critSec);

        if (_state == State_Started && fProcessingSample && !_isShutdown) {
          // If we are still in started state request another sample
          ThrowIfError(QueueEvent(MEStreamSinkRequestSample,
            GUID_NULL, S_OK, nullptr));
        }

        if (_sampleQueue.size() == 0) {
          fNeedMoreSamples = true;
          fSendSamples = false;
        } else {
          spunkSample = _sampleQueue.front();
          _sampleQueue.pop();
        }
      }
    }

    return fNeedMoreSamples;
  }

  //-----------------------------------------------------------------------------
  // Processing format change
  void VideoCaptureStreamSink::ProcessFormatChange(
    IMFMediaType *pMediaType) {
    assert(pMediaType != nullptr);

    // Add the media type to the sample queue.
    winrt::com_ptr<IMFMediaType> cpMediaType;
    cpMediaType.copy_from(pMediaType);
    _sampleQueue.push(cpMediaType);

    // Unless we are paused, start an async operation to dispatch the next sample.
    // Queue the operation.
    ThrowIfError(QueueAsyncOperation(OpSetMediaType));
  }

  //-----------------------------------------------------------------------------
  VideoCaptureStreamSink::AsyncOperation::AsyncOperation(StreamOperation op)
    : _cRef(1),
    _op(op) {
  }

  //-----------------------------------------------------------------------------
  VideoCaptureStreamSink::AsyncOperation::~AsyncOperation() {
    assert(_cRef == 0);
  }

  //-----------------------------------------------------------------------------
  ULONG VideoCaptureStreamSink::AsyncOperation::AddRef() {
    return InterlockedIncrement(&_cRef);
  }

  //-----------------------------------------------------------------------------
  ULONG VideoCaptureStreamSink::AsyncOperation::Release() {
    ULONG cRef = InterlockedDecrement(&_cRef);
    if (cRef == 0) {
      delete this;
    }

    return cRef;
  }

  //-----------------------------------------------------------------------------
  HRESULT VideoCaptureStreamSink::AsyncOperation::QueryInterface(
    REFIID iid,
    void **ppv) {
    if (!ppv) {
      return E_POINTER;
    }
    if (iid == IID_IUnknown) {
      *ppv = static_cast<IUnknown*>(this);
    } else {
      *ppv = nullptr;
      return E_NOINTERFACE;
    }
    AddRef();
    return S_OK;
  }

  //-----------------------------------------------------------------------------
  VideoCaptureStreamSink::Marker::Marker(
    MFSTREAMSINK_MARKER_TYPE eMarkerType)
    : _cRef(1),
    _eMarkerType(eMarkerType) {
    ZeroMemory(&_varMarkerValue, sizeof(_varMarkerValue));
    ZeroMemory(&_varContextValue, sizeof(_varContextValue));
  }

  //-----------------------------------------------------------------------------
  VideoCaptureStreamSink::Marker::~Marker() {
    assert(_cRef == 0);

    PropVariantClear(&_varMarkerValue);
    PropVariantClear(&_varContextValue);
  }

  //-----------------------------------------------------------------------------
  /* static */
  HRESULT VideoCaptureStreamSink::Marker::Create(
    MFSTREAMSINK_MARKER_TYPE eMarkerType,
    const PROPVARIANT *pvarMarkerValue,
    const PROPVARIANT *pvarContextValue,
    IMarker **ppMarker) {

    if (ppMarker == nullptr) {
      return E_POINTER;
    }

    HRESULT hr = S_OK;
    winrt::com_ptr<Marker> spMarker;

    spMarker.attach(new (std::nothrow) Marker(eMarkerType));

    if (spMarker == nullptr) {
      hr = E_OUTOFMEMORY;
    }

    if (SUCCEEDED(hr)) {
      if (pvarMarkerValue) {
        hr = PropVariantCopy(&spMarker->_varMarkerValue, pvarMarkerValue);
      }
    }

    if (SUCCEEDED(hr)) {
      if (pvarContextValue) {
        hr = PropVariantCopy(&spMarker->_varContextValue, pvarContextValue);
      }
    }

    if (SUCCEEDED(hr)) {
      *ppMarker = spMarker.detach();
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  // IUnknown methods.
  IFACEMETHODIMP_(ULONG) VideoCaptureStreamSink::Marker::AddRef() {
    return InterlockedIncrement(&_cRef);
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP_(ULONG) VideoCaptureStreamSink::Marker::Release() {

    ULONG cRef = InterlockedDecrement(&_cRef);
    if (cRef == 0) {
      delete this;
    }

    return cRef;
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP VideoCaptureStreamSink::Marker::QueryInterface(
    REFIID riid, void **ppv) {

    if (ppv == nullptr) {
      return E_POINTER;
    }
    (*ppv) = nullptr;

    HRESULT hr = S_OK;
    if (riid == IID_IUnknown || riid == __uuidof(IMarker)) {
      (*ppv) = static_cast<IMarker*>(this);
      AddRef();
    } else {
      hr = E_NOINTERFACE;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  // IMarker methods
  IFACEMETHODIMP VideoCaptureStreamSink::Marker::GetMarkerType(
    MFSTREAMSINK_MARKER_TYPE *pType) {

    if (pType == NULL) {
      return E_POINTER;
    }

    *pType = _eMarkerType;
    return S_OK;
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP VideoCaptureStreamSink::Marker::GetMarkerValue(
    PROPVARIANT *pvar) {
    if (pvar == NULL) {
      return E_POINTER;
    }
    return PropVariantCopy(pvar, &_varMarkerValue);
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP VideoCaptureStreamSink::Marker::GetContext(
    PROPVARIANT *pvar) {
    if (pvar == NULL) {
      return E_POINTER;
    }
    return PropVariantCopy(pvar, &_varContextValue);
  }

  //-----------------------------------------------------------------------------
  void VideoCaptureStreamSink::HandleError(HRESULT hr) {
    if (!_isShutdown) {
      QueueEvent(MEError, GUID_NULL, hr, nullptr);
    }
  }

  //-----------------------------------------------------------------------------
  void VideoCaptureMediaSink::init(const CreationProperties &props) noexcept
  {
    id_ = String(props.id_);

    if (props.delegate_) {
      defaultSubscription_ = subscriptions_.subscribe(props.delegate_, zsLib::IMessageQueueThread::singletonUsingCurrentGUIThreadsMessageQueue());
    }

    try {
      _callback = props.callback_;
      const unsigned int streamId = GetStreamId();
      RemoveStreamSink(streamId);
      if (props.encodingProperties_ != nullptr) {
        winrt::com_ptr<IMFStreamSink> spStreamSink;
        winrt::com_ptr<IMFMediaType> spMediaType;
        ConvertPropertiesToMediaType(props.encodingProperties_, spMediaType.put());
        ThrowIfError(AddStreamSink(streamId, spMediaType.get(),
          spStreamSink.put()));
      }
    } catch (winrt::hresult_error const& exc) {
      _callback = nullptr;
      winrt::throw_hresult(exc.code());
    }
  }

  //-----------------------------------------------------------------------------
  VideoCaptureMediaSink::VideoCaptureMediaSink() :
    subscriptions_(decltype(subscriptions_)::create()),
    _cRef(1),
    _isShutdown(false),
    _isConnected(false),
    _llStartTime(0)
  {
  }

  //-----------------------------------------------------------------------------
  VideoCaptureMediaSink::~VideoCaptureMediaSink()
  {
    assert(_isShutdown);
  }

  //-----------------------------------------------------------------------------
  IMediaExtension VideoCaptureMediaSink::create(const CreationProperties &info) noexcept
  {
    IMediaExtension result = winrt::make<VideoCaptureMediaSink>();
    result.as<VideoCaptureMediaSink>()->init(info);
    return result;
  }

  //-----------------------------------------------------------------------------
  IVideoCaptureMediaSinkSubscriptionPtr VideoCaptureMediaSink::subscribe(IVideoCaptureMediaSinkDelegatePtr originalDelegate)
  {
    AutoRecursiveLock lock(lock_);
    if (!originalDelegate) return defaultSubscription_;

    auto subscription = subscriptions_.subscribe(originalDelegate, zsLib::IMessageQueueThread::singletonUsingCurrentGUIThreadsMessageQueue());

    auto delegate = subscriptions_.delegate(subscription, true);

    if (delegate) {
    }

    return subscription;
  }

  //-----------------------------------------------------------------------------
  ///  IMFMediaSink
  IFACEMETHODIMP VideoCaptureMediaSink::GetCharacteristics(
    DWORD *pdwCharacteristics) {
    if (pdwCharacteristics == NULL) {
      return E_INVALIDARG;
    }
    rtc::CritScope lock(&_critSec);

    HRESULT hr;
    if (_isShutdown) {
      hr = MF_E_SHUTDOWN;
    } else {
      hr = S_OK;
    }

    if (SUCCEEDED(hr)) {
      // Rateless sink.
      *pdwCharacteristics = MEDIASINK_RATELESS;
    } else {
      RTC_LOG_F(LS_ERROR) << "Capture media sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP VideoCaptureMediaSink::AddStreamSink(
    DWORD dwStreamSinkIdentifier,
    IMFMediaType *pMediaType,
    IMFStreamSink **ppStreamSink) {
    VideoCaptureStreamSink *pStream = nullptr;
    winrt::com_ptr<IMFStreamSink> spMFStream;
    rtc::CritScope lock(&_critSec);
    HRESULT hr = S_OK;
    if (_isShutdown) {
      hr = MF_E_SHUTDOWN;
    }

    if (SUCCEEDED(hr) && dwStreamSinkIdentifier != GetStreamId()) {
      hr = MF_E_INVALIDSTREAMNUMBER;
    }

    if (SUCCEEDED(hr)) {
      hr = GetStreamSinkById(dwStreamSinkIdentifier, spMFStream.put());
    }

    if (SUCCEEDED(hr)) {
      hr = MF_E_STREAMSINK_EXISTS;
    } else {
      hr = S_OK;
    }

    if (SUCCEEDED(hr)) {
      pStream = new VideoCaptureStreamSink(dwStreamSinkIdentifier);
      if (pStream == nullptr) {
        hr = E_OUTOFMEMORY;
      }
      spMFStream.attach(pStream);
    }

    // Initialize the stream.
    if (SUCCEEDED(hr)) {
      hr = pStream->Initialize(this, _callback);
    }

    if (SUCCEEDED(hr) && pMediaType != nullptr) {
      hr = pStream->SetCurrentMediaType(pMediaType);
    }

    if (SUCCEEDED(hr)) {
      _spStreamSink = spMFStream;
      *ppStreamSink = spMFStream.detach();
    } else {
      RTC_LOG_F(LS_ERROR) << "Capture media sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP VideoCaptureMediaSink::RemoveStreamSink(
    DWORD dwStreamSinkIdentifier) {
    rtc::CritScope lock(&_critSec);
    HRESULT hr = S_OK;
    if (_isShutdown) {
      hr = MF_E_SHUTDOWN;
    }

    if (SUCCEEDED(hr) && dwStreamSinkIdentifier != GetStreamId()) {
      hr = MF_E_INVALIDSTREAMNUMBER;
    }

    if (SUCCEEDED(hr) && _spStreamSink) {
      winrt::com_ptr<IMFStreamSink> spStream = _spStreamSink;
      static_cast<VideoCaptureStreamSink *>(spStream.get())->Shutdown();
    }

    if (!SUCCEEDED(hr)) {
      RTC_LOG_F(LS_ERROR) << "Capture media sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP VideoCaptureMediaSink::GetStreamSinkCount(
    _Out_ DWORD *pcStreamSinkCount) {
    if (pcStreamSinkCount == NULL) {
      return E_INVALIDARG;
    }

    rtc::CritScope lock(&_critSec);

    HRESULT hr = S_OK;
    if (_isShutdown) {
      hr = MF_E_SHUTDOWN;
    }

    if (SUCCEEDED(hr)) {
      *pcStreamSinkCount = 1;
    } else {
      RTC_LOG_F(LS_ERROR) << "Capture media sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP VideoCaptureMediaSink::GetStreamSinkByIndex(
    DWORD dwIndex,
    _Outptr_ IMFStreamSink **ppStreamSink) {
    if (ppStreamSink == NULL) {
      return E_INVALIDARG;
    }

    rtc::CritScope lock(&_critSec);

    if (dwIndex >= 1) {
      return MF_E_INVALIDINDEX;
    }

    HRESULT hr = S_OK;
    if (_isShutdown) {
      hr = MF_E_SHUTDOWN;
    }

    if (SUCCEEDED(hr)) {
      assert(_spStreamSink);
      winrt::com_ptr<IMFStreamSink> spResult = _spStreamSink;
      *ppStreamSink = spResult.detach();
    } else {
      RTC_LOG_F(LS_ERROR) << "Capture media sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP VideoCaptureMediaSink::GetStreamSinkById(
    DWORD dwStreamSinkIdentifier,
    IMFStreamSink **ppStreamSink) {
    if (ppStreamSink == NULL) {
      return E_INVALIDARG;
    }

    rtc::CritScope lock(&_critSec);
    HRESULT hr = S_OK;
    if (_isShutdown) {
      hr = MF_E_SHUTDOWN;
    }

    if (dwStreamSinkIdentifier != GetStreamId() || _spStreamSink == nullptr) {
      hr = MF_E_INVALIDSTREAMNUMBER;
    }

    if (SUCCEEDED(hr)) {
      assert(_spStreamSink);
      winrt::com_ptr<IMFStreamSink> spResult = _spStreamSink;
      *ppStreamSink = spResult.detach();
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP VideoCaptureMediaSink::SetPresentationClock(
    IMFPresentationClock *pPresentationClock) {
    rtc::CritScope lock(&_critSec);

    HRESULT hr = S_OK;
    if (_isShutdown) {
      hr = MF_E_SHUTDOWN;
    }

    // If we already have a clock, remove ourselves from that clock's
    // state notifications.
    if (SUCCEEDED(hr)) {
      if (_spClock) {
        hr = _spClock->RemoveClockStateSink(this);
      }
    }

    // Register ourselves to get state notifications from the new clock.
    if (SUCCEEDED(hr)) {
      if (pPresentationClock) {
        hr = pPresentationClock->AddClockStateSink(this);
      }
    }

    if (SUCCEEDED(hr)) {
      // Release the pointer to the old clock.
      // Store the pointer to the new clock.
      _spClock.copy_from(pPresentationClock);
    } else {
      RTC_LOG_F(LS_ERROR) << "Capture media sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP VideoCaptureMediaSink::GetPresentationClock(
    IMFPresentationClock **ppPresentationClock) {
    if (ppPresentationClock == NULL) {
      return E_INVALIDARG;
    }

    rtc::CritScope lock(&_critSec);

    HRESULT hr = S_OK;
    if (_isShutdown) {
      hr = MF_E_SHUTDOWN;
    }

    if (SUCCEEDED(hr)) {
      if (_spClock == NULL) {
        hr = MF_E_NO_CLOCK;  // There is no presentation clock.
      } else {
        // Return the pointer to the caller.
        *ppPresentationClock = _spClock.get();
        (*ppPresentationClock)->AddRef();
      }
    }

    if (!SUCCEEDED(hr)) {
      RTC_LOG_F(LS_ERROR) << "Capture media sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP VideoCaptureMediaSink::Shutdown() {
    ISinkCallback *callback = nullptr;
    {
      rtc::CritScope lock(&_critSec);
      HRESULT hr = S_OK;
      if (_isShutdown) {
        hr = MF_E_SHUTDOWN;
      }

      if (SUCCEEDED(hr)) {
        winrt::com_ptr<IMFStreamSink> spMFStream = _spStreamSink;
        _spClock = nullptr;
        static_cast<VideoCaptureStreamSink *>(spMFStream.get())->Shutdown();
        _isShutdown = true;
        callback = _callback;
      }
    }

    if (callback != nullptr) {
      callback->OnShutdown();
    }

    return S_OK;
  }

  //-----------------------------------------------------------------------------
  // IMFClockStateSink
  IFACEMETHODIMP VideoCaptureMediaSink::OnClockStart(
    MFTIME /*hnsSystemTime*/,
    LONGLONG llClockStartOffset) {
    rtc::CritScope lock(&_critSec);

    HRESULT hr = S_OK;
    if (_isShutdown) {
      hr = MF_E_SHUTDOWN;
    }

    if (SUCCEEDED(hr)) {
      _llStartTime = llClockStartOffset;
      static_cast<VideoCaptureStreamSink *>(_spStreamSink.get())->Start(
        _llStartTime);
    } else {
      RTC_LOG_F(LS_ERROR) << "Capture media sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP VideoCaptureMediaSink::OnClockStop(
    MFTIME /*hnsSystemTime*/) {
    rtc::CritScope lock(&_critSec);

    HRESULT hr = S_OK;
    if (_isShutdown) {
      hr = MF_E_SHUTDOWN;
    }

    if (SUCCEEDED(hr)) {
      static_cast<VideoCaptureStreamSink *>(_spStreamSink.get())->Stop();
    } else {
      RTC_LOG_F(LS_ERROR) << "Capture media sink error: " << hr;
    }

    return hr;
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP VideoCaptureMediaSink::OnClockPause(
    MFTIME /*hnsSystemTime*/) {
    return MF_E_INVALID_STATE_TRANSITION;
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP VideoCaptureMediaSink::OnClockRestart(
    MFTIME /*hnsSystemTime*/) {
    return MF_E_INVALID_STATE_TRANSITION;
  }

  //-----------------------------------------------------------------------------
  IFACEMETHODIMP VideoCaptureMediaSink::OnClockSetRate(
    /* [in] */ MFTIME /*hnsSystemTime*/,
    /* [in] */ float /*flRate*/) {
    return S_OK;
  }

  //-----------------------------------------------------------------------------
  IMediaExtension IVideoCaptureMediaSink::create(const CreationProperties &info) noexcept
  {
    return VideoCaptureMediaSink::create(info);
  }
}
#endif //CPPWINRT_VERSION
#endif //WINUWP
