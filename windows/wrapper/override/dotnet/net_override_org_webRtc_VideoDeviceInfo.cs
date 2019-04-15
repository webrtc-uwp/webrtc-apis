
using org_webRtc_VideoDeviceInfo_t = System.IntPtr;
using instance_id_t = System.IntPtr;
using zs_Any_t = System.IntPtr;

namespace Org
{
    namespace WebRtc
    {

        public interface IVideoDeviceInfo
        {
            string Id { get; }
            string Name { get; }
            bool IsDefault { get; }
            bool IsEnabled { get; }

        }

        public sealed class VideoDeviceInfo : System.IDisposable,
                                              Org.WebRtc.IVideoDeviceInfo
        {

            #region To / From C routines

            //------------------------------------------------------------------
            //------------------------------------------------------------------
            // To / From C routines
            //------------------------------------------------------------------
            //------------------------------------------------------------------

            private class WrapperMakePrivate {}
            private org_webRtc_VideoDeviceInfo_t native_ = System.IntPtr.Zero;

            private VideoDeviceInfo(WrapperMakePrivate ignored, org_webRtc_VideoDeviceInfo_t handle)
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
                Wrapper.Org_WebRtc.OverrideApi.org_webRtc_VideoDeviceInfo_wrapperDestroy(this.native_);
                this.native_ = System.IntPtr.Zero;
                if (disposing) System.GC.SuppressFinalize(this);
            }

            ~VideoDeviceInfo()
            {
                Dispose(false);
            }

            internal static VideoDeviceInfo org_webRtc_VideoDeviceInfo_FromC(org_webRtc_VideoDeviceInfo_t handle)
            {
                if (System.IntPtr.Zero == handle) return null;
                return new VideoDeviceInfo((WrapperMakePrivate)null, Wrapper.Org_WebRtc.OverrideApi.org_webRtc_VideoDeviceInfo_wrapperClone(handle));
            }

            internal static VideoDeviceInfo org_webRtc_VideoDeviceInfo_AdoptFromC(org_webRtc_VideoDeviceInfo_t handle)
            {
                if (System.IntPtr.Zero == handle) return null;
                return new VideoDeviceInfo((WrapperMakePrivate)null, handle);
            }

            internal static org_webRtc_VideoDeviceInfo_t org_webRtc_VideoDeviceInfo_ToC(VideoDeviceInfo value)
            {
                if (null == value) return System.IntPtr.Zero;
                return Wrapper.Org_WebRtc.OverrideApi.org_webRtc_VideoDeviceInfo_wrapperClone(value.native_);
            }

            #endregion // To / From C routines


            #region Org.WebRtc.VideoDeviceInfo

            //------------------------------------------------------------------
            //------------------------------------------------------------------
            // Org.WebRtc.VideoDeviceInfo
            //------------------------------------------------------------------
            //------------------------------------------------------------------

            public string Id
            {
                get
                {
                    var result = Wrapper.Org_WebRtc.OverrideApi.org_webRtc_VideoDeviceInfo_get_id(this.native_);
                    return Wrapper.Org_WebRtc.Helpers.string_t_AdoptFromC(result);
                }
            }

            public string Name
            {
                get
                {
                    var result = Wrapper.Org_WebRtc.OverrideApi.org_webRtc_VideoDeviceInfo_get_name(this.native_);
                    return Wrapper.Org_WebRtc.Helpers.string_t_AdoptFromC(result);
                }
            }

            public bool IsDefault
            {
                get
                {
                    var result = Wrapper.Org_WebRtc.OverrideApi.org_webRtc_VideoDeviceInfo_get_isDefault(this.native_);
                    return (result);
                }
            }

            public bool IsEnabled
            {
                get
                {
                    var result = Wrapper.Org_WebRtc.OverrideApi.org_webRtc_VideoDeviceInfo_get_isEnabled(this.native_);
                    return (result);
                }
            }

            #endregion // Org.WebRtc.VideoDeviceInfo


        }

    } //WebRtc
} //Org
