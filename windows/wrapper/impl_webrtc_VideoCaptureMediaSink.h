
#pragma once

#include "impl_webrtc_IVideoCaptureMediaSink.h"

#ifdef WINUWP
#ifdef CPPWINRT_VERSION

#include <wrapper/impl_org_webRtc_pre_include.h>
#include "rtc_base/criticalsection.h"
#include <wrapper/impl_org_webRtc_post_include.h>

#include <assert.h>
#include <queue>

#include <zsLib/types.h>
#include <zsLib/Proxy.h>
#include <zsLib/ProxySubscriptions.h>

#include <atomic>
#include <mfidl.h>

#include <ppltasks.h>


namespace webrtc
{
  class VideoCaptureMediaSink;

  class MediaSampleEventArgs {
  public:
    MediaSampleEventArgs(winrt::com_ptr<IMFSample> spMediaSample) :
      _spMediaSample(spMediaSample) { }

    winrt::com_ptr<IMFSample> GetMediaSample() {
      return _spMediaSample;
    }

  private:
    winrt::com_ptr<IMFSample> _spMediaSample;
  };

  class ISinkCallback {
  public:
    void OnSample(std::shared_ptr<MediaSampleEventArgs> args);
    void OnShutdown();
  };

  interface DECLSPEC_UUID("3AC82233-933C-43a9-AF3D-ADC94EABF406") DECLSPEC_NOVTABLE IMarker : public IUnknown
  {
    IFACEMETHOD(GetMarkerType) (MFSTREAMSINK_MARKER_TYPE *pType) = 0;
    IFACEMETHOD(GetMarkerValue) (PROPVARIANT *pvar) = 0;
    IFACEMETHOD(GetContext) (PROPVARIANT *pvar) = 0;
  };

  class VideoCaptureStreamSink :
    public IMFStreamSink,
    public IMFMediaTypeHandler {
    // State enum: Defines the current state of the stream.
    enum State {
      State_TypeNotSet = 0,
      State_Ready,
      State_Started,
      State_Stopped,
      State_Paused,
      State_Count
    };

    // StreamOperation: Defines various operations that can
    // be performed on the stream.
    enum StreamOperation {
      OpSetMediaType = 0,
      OpStart,
      OpRestart,
      OpPause,
      OpStop,
      OpProcessSample,
      OpPlaceMarker,
      Op_Count
    };

    template<class T>
    class AsyncCallback : public IMFAsyncCallback {
    public:
      typedef HRESULT(T::*InvokeFn)(IMFAsyncResult *pAsyncResult);

      AsyncCallback(T *pParent, InvokeFn fn) : _pParent(pParent), _pInvokeFn(fn) {
      }

      // IUnknown
      STDMETHODIMP_(ULONG) AddRef() {
        // Delegate to parent class.
        return _pParent->AddRef();
      }
      STDMETHODIMP_(ULONG) Release() {
        // Delegate to parent class.
        return _pParent->Release();
      }
      STDMETHODIMP QueryInterface(REFIID iid, void** ppv) {
        if (!ppv) {
          return E_POINTER;
        }
        if (iid == __uuidof(IUnknown)) {
          *ppv = static_cast<IUnknown*>(static_cast<IMFAsyncCallback*>(this));
        } else if (iid == __uuidof(IMFAsyncCallback)) {
          *ppv = static_cast<IMFAsyncCallback*>(this);
        } else {
          *ppv = NULL;
          return E_NOINTERFACE;
        }
        AddRef();
        return S_OK;
      }

      // IMFAsyncCallback methods
      STDMETHODIMP GetParameters(DWORD*, DWORD*) {
        return E_NOTIMPL;
      }

      STDMETHODIMP Invoke(IMFAsyncResult* pAsyncResult) {
        return (_pParent->*_pInvokeFn)(pAsyncResult);
      }

      T *_pParent;
      InvokeFn _pInvokeFn;
    };

    // AsyncOperation:
    // Used to queue asynchronous operations. When we call MFPutWorkItem,
    // we use this object for the callback state (pState). Then, when the
    // callback is invoked, we can use the object to determine which
    // asynchronous operation to perform.
    class AsyncOperation : public IUnknown {
    public:
      explicit AsyncOperation(StreamOperation op);

      StreamOperation _op;

      // IUnknown methods.
      STDMETHODIMP QueryInterface(REFIID iid, void **ppv);
      STDMETHODIMP_(ULONG) AddRef();
      STDMETHODIMP_(ULONG) Release();

    private:
      ULONG _cRef;
      virtual ~AsyncOperation();
    };

    class Marker : public IMarker
    {
    public:
      static HRESULT Create(
        MFSTREAMSINK_MARKER_TYPE eMarkerType,
        const PROPVARIANT *pvarMarkerValue,
        const PROPVARIANT *pvarContextValue,
        IMarker **ppMarker
      );

      // IUnknown methods.
      IFACEMETHOD(QueryInterface) (REFIID riid, void **ppv);
      IFACEMETHOD_(ULONG, AddRef) ();
      IFACEMETHOD_(ULONG, Release) ();

      IFACEMETHOD(GetMarkerType) (MFSTREAMSINK_MARKER_TYPE *pType);
      IFACEMETHOD(GetMarkerValue) (PROPVARIANT *pvar);
      IFACEMETHOD(GetContext) (PROPVARIANT *pvar);

    protected:
      MFSTREAMSINK_MARKER_TYPE _eMarkerType;
      PROPVARIANT _varMarkerValue;
      PROPVARIANT _varContextValue;

    private:
      long _cRef;
      Marker(MFSTREAMSINK_MARKER_TYPE eMarkerType);
      virtual ~Marker();
    };

  public:
    // IUnknown
    IFACEMETHOD(QueryInterface) (REFIID riid, void **ppv);
    IFACEMETHOD_(ULONG, AddRef) ();
    IFACEMETHOD_(ULONG, Release) ();

    // IMFMediaEventGenerator
    IFACEMETHOD(BeginGetEvent)(IMFAsyncCallback *pCallback, IUnknown *punkState);
    IFACEMETHOD(EndGetEvent) (IMFAsyncResult *pResult, IMFMediaEvent **ppEvent);
    IFACEMETHOD(GetEvent) (DWORD dwFlags, IMFMediaEvent **ppEvent);
    IFACEMETHOD(QueueEvent) (
      MediaEventType met,
      REFGUID guidExtendedType,
      HRESULT hrStatus,
      PROPVARIANT const *pvValue);

    // IMFStreamSink
    IFACEMETHOD(GetMediaSink) (IMFMediaSink **ppMediaSink);
    IFACEMETHOD(GetIdentifier) (DWORD *pdwIdentifier);
    IFACEMETHOD(GetMediaTypeHandler) (IMFMediaTypeHandler **ppHandler);
    IFACEMETHOD(ProcessSample) (IMFSample *pSample);

    IFACEMETHOD(PlaceMarker) (
      /* [in] */ MFSTREAMSINK_MARKER_TYPE eMarkerType,
      /* [in] */ PROPVARIANT const *pvarMarkerValue,
      /* [in] */ PROPVARIANT const *pvarContextValue);

    IFACEMETHOD(Flush)();

    // IMFMediaTypeHandler
    IFACEMETHOD(IsMediaTypeSupported) (
      IMFMediaType *pMediaType,
      IMFMediaType **ppMediaType);
    IFACEMETHOD(GetMediaTypeCount) (DWORD *pdwTypeCount);
    IFACEMETHOD(GetMediaTypeByIndex) (DWORD dwIndex, IMFMediaType **ppType);
    IFACEMETHOD(SetCurrentMediaType) (IMFMediaType *pMediaType);
    IFACEMETHOD(GetCurrentMediaType) (IMFMediaType **ppMediaType);
    IFACEMETHOD(GetMajorType) (GUID *pguidMajorType);

    // ValidStateMatrix: Defines a look-up table that says which operations
    // are valid from which states.
    static BOOL ValidStateMatrix[State_Count][Op_Count];

    explicit VideoCaptureStreamSink(DWORD dwIdentifier);
    virtual ~VideoCaptureStreamSink();

    HRESULT Initialize(VideoCaptureMediaSink *pParent,
      std::shared_ptr<ISinkCallback> callback);

    HRESULT Start(MFTIME start);
    HRESULT Restart();
    HRESULT Stop();
    HRESULT Pause();
    HRESULT Shutdown();

  private:
    HRESULT ValidateOperation(StreamOperation op);

    HRESULT QueueAsyncOperation(StreamOperation op);

    HRESULT OnDispatchWorkItem(IMFAsyncResult *pAsyncResult);
    void DispatchProcessSample(AsyncOperation *pOp);

    bool DropSamplesFromQueue();
    bool SendSampleFromQueue();
    bool ProcessSamplesFromQueue(bool fFlush);
    void ProcessFormatChange(IMFMediaType *pMediaType);

    void HandleError(HRESULT hr);

  private:
    ULONG _cRef;
    rtc::CriticalSection _critSec;

    DWORD _dwIdentifier;
    State _state;
    bool _isShutdown;
    bool _fGetStartTimeFromSample;
    GUID _guiCurrentSubtype;

    DWORD _workQueueId;
    MFTIME _startTime;

    winrt::com_ptr<IMFMediaSink> _spSink;
    VideoCaptureMediaSink* _pParent;

    winrt::com_ptr<IMFMediaEventQueue> _spEventQueue;
    winrt::com_ptr<IMFByteStream> _spByteStream;
    winrt::com_ptr<IMFMediaType> _spCurrentType;

    std::queue<winrt::com_ptr<IUnknown> > _sampleQueue;

    std::shared_ptr<ISinkCallback> _callback;
    AsyncCallback<VideoCaptureStreamSink> _workQueueCB;
  };


  class VideoCaptureMediaSink : public IVideoCaptureMediaSink,
    public winrt::implements<VideoCaptureMediaSink, 
      winrt::Windows::Media::IMediaExtension,
      IMFMediaSink, IMFClockStateSink>
  {
  private:
    struct make_private {};

  private:
    void init(const CreationProperties &props) noexcept;

  public:
    VideoCaptureMediaSink();
    ~VideoCaptureMediaSink();

    static winrt::Windows::Media::IMediaExtension create(const CreationProperties &info) noexcept;

    IVideoCaptureMediaSinkSubscriptionPtr subscribe(IVideoCaptureMediaSinkDelegatePtr delegate) override;

    std::string id() const noexcept override { return id_; }

    // IMediaExtension
    void SetProperties(winrt::Windows::Foundation::Collections::IPropertySet configuration) {
    }

    // IMFMediaSink methods
    IFACEMETHOD(GetCharacteristics) (DWORD *pdwCharacteristics);

    IFACEMETHOD(AddStreamSink)(
      /* [in] */ DWORD dwStreamSinkIdentifier,
      /* [in] */ IMFMediaType *pMediaType,
      /* [out] */ IMFStreamSink **ppStreamSink);

    IFACEMETHOD(RemoveStreamSink) (DWORD dwStreamSinkIdentifier);
    IFACEMETHOD(GetStreamSinkCount) (_Out_ DWORD *pcStreamSinkCount);
    IFACEMETHOD(GetStreamSinkByIndex) (
      DWORD dwIndex,
      _Outptr_ IMFStreamSink **ppStreamSink);
    IFACEMETHOD(GetStreamSinkById) (
      DWORD dwIdentifier,
      IMFStreamSink **ppStreamSink);
    IFACEMETHOD(SetPresentationClock) (
      IMFPresentationClock *pPresentationClock);
    IFACEMETHOD(GetPresentationClock) (
      IMFPresentationClock **ppPresentationClock);
    IFACEMETHOD(Shutdown) ();

    // IMFClockStateSink methods
    IFACEMETHOD(OnClockStart) (MFTIME hnsSystemTime, LONGLONG llClockStartOffset);
    IFACEMETHOD(OnClockStop) (MFTIME hnsSystemTime);
    IFACEMETHOD(OnClockPause) (MFTIME hnsSystemTime);
    IFACEMETHOD(OnClockRestart) (MFTIME hnsSystemTime);
    IFACEMETHOD(OnClockSetRate) (MFTIME hnsSystemTime, float flRate);

  private:
    mutable zsLib::RecursiveLock lock_;

    IVideoCaptureMediaSinkDelegateSubscriptions subscriptions_;
    IVideoCaptureMediaSinkSubscriptionPtr defaultSubscription_;

    std::string id_;

    ULONG _cRef;
    rtc::CriticalSection _critSec;
    bool _isShutdown;
    bool _isConnected;
    LONGLONG _llStartTime;

    std::shared_ptr<ISinkCallback> _callback;

    winrt::com_ptr<IMFStreamSink> _spStreamSink;
    winrt::com_ptr<IMFPresentationClock> _spClock;
  };

  class VideoCaptureMediaSinkProxyListener {
  public:
    virtual void OnMediaSampleEvent(std::shared_ptr<MediaSampleEventArgs> args) = 0;
  };

  class VideoCaptureMediaSinkProxy {
  public:
    VideoCaptureMediaSinkProxy(std::shared_ptr<VideoCaptureMediaSinkProxyListener> listener);
    virtual ~VideoCaptureMediaSinkProxy();

    winrt::Windows::Media::IMediaExtension GetMFExtension();

    concurrency::task<winrt::Windows::Media::IMediaExtension>
      InitializeAsync(winrt::Windows::Media::MediaProperties::IMediaEncodingProperties
        const& encodingProperties);

  private:
    class VideoCaptureSinkCallback : public ISinkCallback {
    public:
      virtual void OnSample(std::shared_ptr<MediaSampleEventArgs> args) {
        _parent.lock()->OnSample(args);
      }

      virtual void OnShutdown() {
        _parent.lock()->OnShutdown();
      }

      VideoCaptureSinkCallback(std::shared_ptr<VideoCaptureMediaSinkProxy> parent)
        : _parent(parent) {
      }

    private:
      std::weak_ptr<VideoCaptureMediaSinkProxy> _parent;
    };

    void OnSample(std::shared_ptr<MediaSampleEventArgs> args);

    void OnShutdown();

    void CheckShutdown();

  private:
    rtc::CriticalSection _critSec;
    std::shared_ptr<VideoCaptureMediaSinkProxyListener> listener_;
    winrt::com_ptr<IMFMediaSink> _mediaSink;
    bool _shutdown;
  };
}

#endif //CPPWINRT_VERSION
#endif //WINUWP
