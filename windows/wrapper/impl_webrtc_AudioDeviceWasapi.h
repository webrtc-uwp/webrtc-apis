#pragma once

#include <unknwn.h>

#include "impl_webrtc_IAudioDeviceWasapi.h"

#ifdef WINUWP
#ifdef CPPWINRT_VERSION

#include <wrapper/impl_org_webRtc_pre_include.h>
#include "rtc_base/criticalsection.h"
#include "rtc_base/scoped_ref_ptr.h"
#include "system_wrappers/include/event_wrapper.h"
#include "modules/audio_device/audio_device_buffer.h"
#include <wrapper/impl_org_webRtc_post_include.h>

#include <zsLib/types.h>
#include <zsLib/Proxy.h>
#include <zsLib/ProxySubscriptions.h>

#include <atomic>
#include <mfidl.h>

#include <functional>
#include <vector>
#include <queue>

#if (_MSC_VER >= 1400) && defined(WINUWP)  // only include for VS 2005 and higher

#include <wmcodecdsp.h>      // CLSID_CWMAudioAEC
                             // (must be before audioclient.h)
#include <Audioclient.h>     // WASAPI
#include <Audiopolicy.h>
#include <wrl\implements.h>
#include <Mmdeviceapi.h>     // MMDevice
#include <avrt.h>            // Avrt
#include <endpointvolume.h>
#include <mediaobj.h>        // IMediaObject
#include <mfapi.h>
#include <ppltasks.h>

using winrt::Windows::Devices::Enumeration::DeviceClass;
using winrt::Windows::Devices::Enumeration::DeviceInformation;
using winrt::Windows::Devices::Enumeration::DeviceInformationCollection;
using winrt::Windows::Media::Devices::DefaultAudioRenderDeviceChangedEventArgs;
using winrt::Windows::Media::Devices::DefaultAudioCaptureDeviceChangedEventArgs;
using winrt::Windows::Media::Devices::AudioDeviceRole;
using winrt::Windows::Media::Devices::MediaDevice;

// Use Multimedia Class Scheduler Service (MMCSS) to boost the thread priority
#pragma comment(lib, "avrt.lib")
#define WEBRTC_TRACE {}
enum TraceModule {
  kTraceUndefined = 0,
  // not a module, triggered from the engine code
  kTraceVoice = 0x0001,
  // not a module, triggered from the engine code
  kTraceVideo = 0x0002,
  // not a module, triggered from the utility code
  kTraceUtility = 0x0003,
  kTraceRtpRtcp = 0x0004,
  kTraceTransport = 0x0005,
  kTraceSrtp = 0x0006,
  kTraceAudioCoding = 0x0007,
  kTraceAudioMixerServer = 0x0008,
  kTraceAudioMixerClient = 0x0009,
  kTraceFile = 0x000a,
  kTraceAudioProcessing = 0x000b,
  kTraceVideoCoding = 0x0010,
  kTraceVideoMixer = 0x0011,
  kTraceAudioDevice = 0x0012,
  kTraceVideoRenderer = 0x0014,
  kTraceVideoCapture = 0x0015,
  kTraceRemoteBitrateEstimator = 0x0017,
};

enum TraceLevel {
  kTraceNone = 0x0000,  // no trace
  kTraceStateInfo = 0x0001,
  kTraceWarning = 0x0002,
  kTraceError = 0x0004,
  kTraceCritical = 0x0008,
  kTraceApiCall = 0x0010,
  kTraceDefault = 0x00ff,

  kTraceModuleCall = 0x0020,
  kTraceMemory = 0x0100,  // memory info
  kTraceTimer = 0x0200,   // timing info
  kTraceStream = 0x0400,  // "continuous" stream of data

  // used for debug purposes
  kTraceDebug = 0x0800,  // debug
  kTraceInfo = 0x1000,   // debug info

  // Non-verbose level used by LS_INFO of logging.h. Do not use directly.
  kTraceTerseInfo = 0x2000,

  kTraceAll = 0xffff
};

namespace webrtc {

  const float MAX_CORE_SPEAKER_VOLUME = 255.0f;
  const float MIN_CORE_SPEAKER_VOLUME = 0.0f;
  const float MAX_CORE_MICROPHONE_VOLUME = 255.0f;
  const float MIN_CORE_MICROPHONE_VOLUME = 0.0f;
  const uint16_t CORE_SPEAKER_VOLUME_STEP_SIZE = 1;
  const uint16_t CORE_MICROPHONE_VOLUME_STEP_SIZE = 1;

  class AudioDeviceWasapi;
  class DefaultAudioDeviceWatcher;

  // Utility class which initializes COM in the constructor (STA or MTA),
  // and uninitializes COM in the destructor.
  class ScopedCOMInitializer {
   public:
    // Enum value provided to initialize the thread as an MTA instead of STA.
    enum SelectMTA { kMTA };

    // Constructor for STA initialization.
    ScopedCOMInitializer() {
      Initialize(COINIT_APARTMENTTHREADED);
    }

    // Constructor for MTA initialization.
    explicit ScopedCOMInitializer(SelectMTA /* mta */) {
      Initialize(COINIT_MULTITHREADED);
    }

    ScopedCOMInitializer::~ScopedCOMInitializer() {
      if (SUCCEEDED(hr_))
        CoUninitialize();
    }

    bool succeeded() const { return SUCCEEDED(hr_); }

   private:
    void Initialize(COINIT init) {
      hr_ = CoInitializeEx(NULL, init);
    }

    HRESULT hr_;

    ScopedCOMInitializer(const ScopedCOMInitializer&);
    void operator=(const ScopedCOMInitializer&);
  };

  class AudioInterfaceActivator : public winrt::implements<AudioInterfaceActivator,
    IActivateAudioInterfaceCompletionHandler> {
  public:
    enum ActivatorDeviceType {
      eNone = 0,
      eInputDevice,
      eOutputDevice
    };

    static ActivatorDeviceType m_DeviceType;
    static AudioDeviceWasapi* m_AudioDevice;
		static HANDLE m_activateCompletedHandle;
    static HRESULT m_activateResult;

  public:
    STDMETHODIMP ActivateCompleted(
      IActivateAudioInterfaceAsyncOperation *pAsyncOp);
		static winrt::Windows::Foundation::IAsyncAction
      AudioInterfaceActivator::ActivateAudioClientAsync(LPCWCHAR deviceId,
        ActivatorDeviceType deviceType, winrt::com_ptr<AudioInterfaceActivator> pActivator,
        winrt::com_ptr<IActivateAudioInterfaceAsyncOperation> pAsyncOp);
    static void SetAudioDevice(AudioDeviceWasapi* device);

  private:
    concurrency::task_completion_event<HRESULT> m_ActivateCompleted;
  };

  class AudioDeviceWasapi : public IAudioDeviceWasapi, AudioDeviceModule {

  private:
    struct make_private {};

    void init(const CreationProperties &props) noexcept;

  public:
      AudioDeviceWasapi(const make_private &);

  protected:
      ~AudioDeviceWasapi();
  
  public:
      static rtc::scoped_refptr<AudioDeviceModule> create(const CreationProperties &info) noexcept;

      IAudioDeviceWasapiSubscriptionPtr subscribe(IAudioDeviceWasapiDelegatePtr delegate) override;

      std::string id() const noexcept override { return id_; }

      friend class AudioInterfaceActivator;
      friend class DefaultAudioDeviceWatcher;

      // Retrieve the currently utilized audio layer
      virtual int32_t ActiveAudioLayer(AudioLayer* audioLayer) const override;

      // Full-duplex transportation of PCM audio
      virtual int32_t RegisterAudioCallback(AudioTransport* audioCallback) override;

      // Main initializaton and termination
      virtual int32_t Init() override;
      virtual int32_t Terminate() override;
      virtual bool Initialized() const override;

      // Device enumeration
      virtual int16_t PlayoutDevices() override;
      virtual int16_t RecordingDevices() override;
      virtual int32_t PlayoutDeviceName(
          uint16_t index,
          char name[kAdmMaxDeviceNameSize],
          char guid[kAdmMaxGuidSize]) override;
      virtual int32_t RecordingDeviceName(
          uint16_t index,
          char name[kAdmMaxDeviceNameSize],
          char guid[kAdmMaxGuidSize]) override;

      // Device selection
      virtual int32_t SetPlayoutDevice(uint16_t index) override;
      virtual int32_t SetPlayoutDevice(
        AudioDeviceModule::WindowsDeviceType device) override;
      virtual int32_t SetRecordingDevice(uint16_t index) override;
      virtual int32_t SetRecordingDevice(
        AudioDeviceModule::WindowsDeviceType device) override;

      // Audio transport initialization
      virtual int32_t PlayoutIsAvailable(bool* available) override;
      virtual int32_t InitPlayout() override;
      virtual bool PlayoutIsInitialized() const override;
      virtual int32_t RecordingIsAvailable(bool* available) override;
      virtual int32_t InitRecording() override;
      virtual bool RecordingIsInitialized() const override;

      // Audio transport control
      virtual int32_t StartPlayout() override;
      virtual int32_t StopPlayout() override;
      virtual bool Playing() const override;
      virtual int32_t StartRecording() override;
      virtual int32_t StopRecording() override;
      virtual bool Recording() const override;

      // Audio mixer initialization
      virtual int32_t InitSpeaker() override;
      virtual bool SpeakerIsInitialized() const override;
      virtual int32_t InitMicrophone() override;
      virtual bool MicrophoneIsInitialized() const override;

      // Speaker volume controls
      virtual int32_t SpeakerVolumeIsAvailable(bool* available) override;
      virtual int32_t SetSpeakerVolume(uint32_t volume) override;
      virtual int32_t SpeakerVolume(uint32_t* volume) const override;
      virtual int32_t MaxSpeakerVolume(uint32_t* maxVolume) const override;
      virtual int32_t MinSpeakerVolume(uint32_t* minVolume) const override;

      // Microphone volume controls
      virtual int32_t MicrophoneVolumeIsAvailable(bool* available) override;
      virtual int32_t SetMicrophoneVolume(uint32_t volume) override;
      virtual int32_t MicrophoneVolume(uint32_t* volume) const override;
      virtual int32_t MaxMicrophoneVolume(uint32_t* maxVolume) const override;
      virtual int32_t MinMicrophoneVolume(uint32_t* minVolume) const override;

      // Speaker mute control
      virtual int32_t SpeakerMuteIsAvailable(bool* available) override;
      virtual int32_t SetSpeakerMute(bool enable) override;
      virtual int32_t SpeakerMute(bool* enabled) const override;

      // Microphone mute control
      virtual int32_t MicrophoneMuteIsAvailable(bool* available) override;
      virtual int32_t SetMicrophoneMute(bool enable) override;
      virtual int32_t MicrophoneMute(bool* enabled) const override;

      // Stereo support
      virtual int32_t StereoPlayoutIsAvailable(bool* available) const override;
      virtual int32_t SetStereoPlayout(bool enable) override;
      virtual int32_t StereoPlayout(bool* enabled) const override;
      virtual int32_t StereoRecordingIsAvailable(bool* available) const override;
      virtual int32_t SetStereoRecording(bool enable) override;
      virtual int32_t StereoRecording(bool* enabled) const override;

      // Delay information and control
      virtual int32_t PlayoutDelay(uint16_t* delayMS) const override;

      // CPU load
      virtual int32_t CPULoad(uint16_t* load) const;

      virtual bool BuiltInAECIsAvailable() const override;
      virtual bool BuiltInAGCIsAvailable() const override;
      virtual bool BuiltInNSIsAvailable() const override;

      virtual int32_t EnableBuiltInAEC(bool enable) override;
      virtual int32_t EnableBuiltInAGC(bool enable) override;
      virtual int32_t EnableBuiltInNS(bool enable) override;


   public:
      virtual bool PlayoutWarning() const;
      virtual bool PlayoutError() const;
      virtual bool RecordingWarning() const;
      virtual bool RecordingError() const;
      virtual void ClearPlayoutWarning();
      virtual void ClearPlayoutError();
      virtual void ClearRecordingWarning();
      virtual void ClearRecordingError();

   private:
      bool KeyPressed() const;

   private:  // thread functions
      DWORD InitCaptureThreadPriority();
      void RevertCaptureThreadPriority();
      static DWORD WINAPI WSAPICaptureThread(LPVOID context);
      DWORD DoCaptureThread();

      static DWORD WINAPI WSAPIRenderThread(LPVOID context);
      DWORD DoRenderThread();

      static DWORD WINAPI GetCaptureVolumeThread(LPVOID context);
      DWORD DoGetCaptureVolumeThread();

      static DWORD WINAPI SetCaptureVolumeThread(LPVOID context);
      DWORD DoSetCaptureVolumeThread();

      int32_t StartObserverThread();
      int32_t StopObserverThread();
      static DWORD WINAPI WSAPIObserverThread(LPVOID context);
      DWORD DoObserverThread();

      bool CheckBuiltInCaptureCapability(winrt::Windows::Media::Effects::AudioEffectType) const;
      bool CheckBuiltInRenderCapability(winrt::Windows::Media::Effects::AudioEffectType) const;

      void _SetThreadName(DWORD dwThreadID, LPCSTR szThreadName);
      void _Lock() { _critSect.Enter(); }
      void _UnLock() { _critSect.Leave(); }

   private:
      int32_t InitRecordingInternal();
      int32_t StartRecordingInternal();
      int32_t StopRecordingInternal();

      int32_t InitPlayoutInternal();
      int32_t StartPlayoutInternal();
      int32_t StopPlayoutInternal();

      int SetBoolProperty(IPropertyStore* ptrPS,
                          REFPROPERTYKEY key,
                          VARIANT_BOOL value);

      int SetVtI4Property(IPropertyStore* ptrPS,
                          REFPROPERTYKEY key,
                          LONG value);

      int32_t _EnumerateEndpointDevicesAll();
      void _TraceCOMError(HRESULT hr) const;
      void _Get44kHzDrift();

      int32_t _RefreshDeviceList(DeviceClass cls);
      int16_t _DeviceListCount(DeviceClass cls);

      winrt::hstring  _GetDefaultDeviceName(DeviceClass cls);
      winrt::hstring  _GetListDeviceName(DeviceClass cls, int index);
      winrt::hstring  _GetDeviceName(DeviceInformation const &device);

      winrt::hstring  _GetListDeviceID(DeviceClass cls, int index);
      winrt::hstring  _GetDefaultDeviceID(DeviceClass cls);
      winrt::hstring  _GetDeviceID(DeviceInformation const &device);

      DeviceInformation _GetDefaultDevice(DeviceClass cls, AudioDeviceRole role);
      DeviceInformation _GetListDevice(DeviceClass cls, int index);
      DeviceInformation _GetListDevice(DeviceClass cls, winrt::hstring const &deviceId);

      void _InitializeAudioDeviceIn(winrt::hstring const &deviceId);
      void _InitializeAudioDeviceOut(winrt::hstring const &deviceId);

      // Surround system support
      bool ShouldUpmix();
      WAVEFORMATEX* GenerateMixFormatForMediaEngine(
        WAVEFORMATEX* actualMixFormat);
      WAVEFORMATPCMEX* GeneratePCMMixFormat(WAVEFORMATEX* actualMixFormat);
      void Upmix(int16_t *inSamples, uint32_t numberOfFrames,
        int16_t *outSamples, uint32_t inChannels, uint32_t outChannels);
      void UpmixAndConvert(int16_t *inSamples, uint32_t numberOfFrames,
        float *outSamples, uint32_t inChannels, uint32_t outChannels);

   private:
      void DefaultAudioCaptureDeviceChanged(
        DefaultAudioCaptureDeviceChangedEventArgs const &args);
      void DefaultAudioRenderDeviceChanged(
        DefaultAudioRenderDeviceChangedEventArgs const &args);

   private:
     AudioDeviceWasapiWeakPtr thisWeak_;
     mutable zsLib::RecursiveLock lock_;

     IAudioDeviceWasapiDelegateSubscriptions subscriptions_;
     IAudioDeviceWasapiSubscriptionPtr defaultSubscription_;

     std::string id_;

   private:
      ScopedCOMInitializer                    _comInit;
      AudioDeviceBuffer*                      _ptrAudioBuffer;
      rtc::CriticalSection                    _critSect;
      rtc::CriticalSection                    _volumeMutex;
      rtc::CriticalSection                    _recordingControlMutex;
      rtc::CriticalSection                    _playoutControlMutex;
      int32_t                                 _id;

   private:  // MMDevice
      winrt::hstring      _deviceIdStringIn;
      winrt::hstring      _deviceIdStringOut;
      DeviceInformation   _captureDevice;
      DeviceInformation   _renderDevice;

      WAVEFORMATPCMEX*       _mixFormatSurroundOut;
      bool                   _enableUpmix;

      DeviceInformationCollection  _ptrCaptureCollection;
      DeviceInformationCollection  _ptrRenderCollection;
      DeviceInformationCollection  _ptrCollection;

   private:  // WASAPI
      IAudioClient*                           _ptrClientOut;
      IAudioClient*                           _ptrClientIn;
      IAudioRenderClient*                     _ptrRenderClient;
      IAudioCaptureClient*                    _ptrCaptureClient;
      ISimpleAudioVolume*                     _ptrCaptureVolume;
      ISimpleAudioVolume*                     _ptrRenderSimpleVolume;

      bool                                    _builtInAecEnabled;
      bool                                    _builtInNSEnabled;
      bool                                    _builtInAGCEnabled;

      HANDLE                                  _hRenderSamplesReadyEvent;
      HANDLE                                  _hPlayThread;
      HANDLE                                  _hRenderStartedEvent;
      HANDLE                                  _hShutdownRenderEvent;
      HANDLE                                  _hRestartRenderEvent;

      HANDLE                                  _hCaptureSamplesReadyEvent;
      HANDLE                                  _hRecThread;
      HANDLE                                  _hCaptureStartedEvent;
      HANDLE                                  _hShutdownCaptureEvent;
      HANDLE                                  _hRestartCaptureEvent;

      HANDLE                                  _hObserverThread;
      HANDLE                                  _hObserverStartedEvent;
      HANDLE                                  _hObserverShutdownEvent;

      HANDLE                                  _hGetCaptureVolumeThread;
      HANDLE                                  _hSetCaptureVolumeThread;
      HANDLE                                  _hSetCaptureVolumeEvent;

      HANDLE                                  _hMmTask;

      UINT                                    _playAudioFrameSize;
      uint32_t                                _playSampleRate;
      uint32_t                                _devicePlaySampleRate;
      uint32_t                                _playBlockSize;
      uint32_t                                _devicePlayBlockSize;
      uint32_t                                _playChannels;
      uint32_t                                _sndCardPlayDelay;

      float                                   _sampleDriftAt48kHz;
      float                                   _driftAccumulator;

      UINT64                                  _writtenSamples;
      LONGLONG                                _playAcc;

      UINT                                    _recAudioFrameSize;
      uint32_t                                _recSampleRate;
      uint32_t                                _recBlockSize;
      uint32_t                                _recChannels;
      UINT64                                  _readSamples;
      uint32_t                                _sndCardRecDelay;

      uint16_t                                _recChannelsPrioList[2];
      uint16_t                                _playChannelsPrioList[2];

      LARGE_INTEGER                           _perfCounterFreq;
      double                                  _perfCounterFactor;
      float                                   _avgCPULoad;

   private:
      bool                                    _initialized;
      bool                                    _recording;
      bool                                    _playing;
      bool                                    _recIsInitialized;
      bool                                    _playIsInitialized;
      bool                                    _speakerIsInitialized;
      bool                                    _microphoneIsInitialized;

      bool                                    _usingInputDeviceIndex;
      bool                                    _usingOutputDeviceIndex;
      AudioDeviceRole                         _outputDeviceRole;
      AudioDeviceRole                         _inputDeviceRole;
      uint16_t                                _inputDeviceIndex;
      uint16_t                                _outputDeviceIndex;

      uint16_t                                _playWarning;
      uint16_t                                _playError;
      bool                                    _playIsRecovering;
      uint16_t                                _recWarning;
      uint16_t                                _recError;
      bool                                    _recIsRecovering;

      uint16_t                                _playBufDelay;
      uint16_t                                _playBufDelayFixed;

      uint16_t                                _newMicLevel;

      std::unique_ptr<DefaultAudioDeviceWatcher> _defaultDeviceWatcher;
  };

#endif    // #if (_MSC_VER >= 1400)

}  // namespace webrtc

#endif //CPPWINRT_VERSION
#endif //WINUWP
