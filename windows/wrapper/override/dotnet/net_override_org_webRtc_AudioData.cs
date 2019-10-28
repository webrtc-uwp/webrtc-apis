
using org_webRtc_AudioData_t = System.IntPtr;
using instance_id_t = System.IntPtr;
using bool_t = System.Boolean;
using box_bool_t = System.IntPtr;
using std_list_int16_t_t = System.IntPtr;

namespace Org
{
    namespace WebRtc
    {

        public interface IAudioData
        {
            /// <summary>
            /// Gets if the data is read-only.
            /// </summary>
            bool ReadOnly { get; }

            /// <summary>
            /// Gets the buffer data size.
            /// </summary>
            System.UInt64 Size { get; }

            /// <summary>
            /// Gets the audio samples data.
            /// </summary>
            System.Int16[] GetData();

            /// <summary>
            /// Sets the audio samples data.
            /// </summary>
            void SetData(System.Int16[] buffer);
        }

        public sealed class AudioData : System.IDisposable,
                                        Org.WebRtc.IAudioData
        {

            #region To / From C routines

            //------------------------------------------------------------------
            //------------------------------------------------------------------
            // To / From C routines
            //------------------------------------------------------------------
            //------------------------------------------------------------------

            private class WrapperMakePrivate {}
            private org_webRtc_AudioData_t native_ = System.IntPtr.Zero;

            private AudioData(WrapperMakePrivate ignored, org_webRtc_AudioData_t handle)
            {
                this.native_ = handle;
            }


            public void Dispose()
            {
                Dispose(true);
            }

            private void Dispose(bool disposing)
            {
                if (System.IntPtr.Zero == this.native_) return;
                Wrapper.Org_WebRtc.OverrideApi.org_webRtc_AudioData_wrapperDispose(this.native_);
                Wrapper.Org_WebRtc.OverrideApi.org_webRtc_AudioData_wrapperDestroy(this.native_);
                this.native_ = System.IntPtr.Zero;
                if (disposing) System.GC.SuppressFinalize(this);
            }

            ~AudioData()
            {
                Dispose(false);
            }

            internal static AudioData org_webRtc_AudioData_FromC(org_webRtc_AudioData_t handle)
            {
                if (System.IntPtr.Zero == handle) return null;
                return new AudioData((WrapperMakePrivate)null, Wrapper.Org_WebRtc.OverrideApi.org_webRtc_AudioData_wrapperClone(handle));
            }

            internal static AudioData org_webRtc_AudioData_AdoptFromC(org_webRtc_AudioData_t handle)
            {
                if (System.IntPtr.Zero == handle) return null;
                return new AudioData((WrapperMakePrivate)null, handle);
            }

            internal static org_webRtc_AudioData_t org_webRtc_AudioData_ToC(AudioData value)
            {
                if (null == value) return System.IntPtr.Zero;
                return Wrapper.Org_WebRtc.OverrideApi.org_webRtc_AudioData_wrapperClone(value.native_);
            }

            #endregion // To / From C routines


            #region Org.WebRtc.AudioData

            //------------------------------------------------------------------
            //------------------------------------------------------------------
            // Org.WebRtc.AudioData
            //------------------------------------------------------------------
            //------------------------------------------------------------------


            /// <summary>
            /// Constructs a new audio data object.
            /// </summary>
            public AudioData()
            {
                this.native_ = Wrapper.Org_WebRtc.OverrideApi.org_webRtc_AudioData_wrapperCreate_AudioData();
            }
            /// <summary>
            /// Constructs a new audio data object with a size.
            /// </summary>
            public AudioData(System.UInt64 size)
            {
                this.native_ = Wrapper.Org_WebRtc.OverrideApi.org_webRtc_AudioData_wrapperCreate_AudioDataWithSize(size);
            }
            /// <summary>
            /// Gets if the data is read-only.
            /// </summary>
            public bool ReadOnly
            {
                get
                {
                    var result = Wrapper.Org_WebRtc.OverrideApi.org_webRtc_AudioData_get_readOnly(this.native_);
                    return (result);
                }
            }

            /// <summary>
            /// Gets the buffer data size.
            /// </summary>
            public System.UInt64 Size
            {
                get
                {
                    var result = Wrapper.Org_WebRtc.OverrideApi.org_webRtc_AudioData_size(this.native_);
                    return (result);
                }
            }

            /// <summary>
            /// Gets audio samples data.
            /// </summary>
            public System.Int16[] GetData()
            {
                var size = Wrapper.Org_WebRtc.OverrideApi.org_webRtc_AudioData_size(this.native_);
                if (size < 1)
                    return null;

                System.Int16[] buffer = new System.Int16[size];

                Wrapper.Org_WebRtc.OverrideApi.org_webRtc_AudioData_get_data(this.native_, buffer, size);

                return buffer;
            }

            /// <summary>
            /// Sets the audio samples data.
            /// </summary>
            public void SetData(System.Int16[] buffer)
            {
                Wrapper.Org_WebRtc.OverrideApi.org_webRtc_AudioData_set_data(this.native_, buffer, (System.UInt64)(buffer.Length));
            }

            #endregion // Org.WebRtc.AudioData

        }

    } //WebRtc
} //Org
