
using org_webRtc_MediaSource_t = System.IntPtr;
using instance_id_t = System.IntPtr;
using zs_Any_t = System.IntPtr;

namespace Org
{
    namespace WebRtc
    {

        /// <summary>
        /// MediaSource represents an object holder for a platform specific
        /// media source.
        /// </summary>
        public interface IMediaSource
        {
        }

        /// <summary>
        /// MediaSource represents an object holder for a platform specific
        /// media source.
        /// </summary>
        public sealed class MediaSource : System.IDisposable,
                                          Org.WebRtc.IMediaSource
        {

            #region To / From C routines

            //------------------------------------------------------------------
            //------------------------------------------------------------------
            // To / From C routines
            //------------------------------------------------------------------
            //------------------------------------------------------------------

            private class WrapperMakePrivate {}
            private org_webRtc_MediaSource_t native_ = System.IntPtr.Zero;

            private MediaSource(WrapperMakePrivate ignored, org_webRtc_MediaSource_t handle)
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
                Wrapper.Org_WebRtc.OverrideApi.org_webRtc_MediaSource_wrapperDestroy(this.native_);
                this.native_ = System.IntPtr.Zero;
                if (disposing) System.GC.SuppressFinalize(this);
            }

            ~MediaSource()
            {
                Dispose(false);
            }

            internal static MediaSource org_webRtc_MediaSource_FromC(org_webRtc_MediaSource_t handle)
            {
                if (System.IntPtr.Zero == handle) return null;
                return new MediaSource((WrapperMakePrivate)null, Wrapper.Org_WebRtc.OverrideApi.org_webRtc_MediaSource_wrapperClone(handle));
            }

            internal static MediaSource org_webRtc_MediaSource_AdoptFromC(org_webRtc_MediaSource_t handle)
            {
                if (System.IntPtr.Zero == handle) return null;
                return new MediaSource((WrapperMakePrivate)null, handle);
            }

            internal static org_webRtc_MediaSource_t org_webRtc_MediaSource_ToC(MediaSource value)
            {
                if (null == value) return System.IntPtr.Zero;
                return Wrapper.Org_WebRtc.OverrideApi.org_webRtc_MediaSource_wrapperClone(value.native_);
            }

            #endregion // To / From C routines


            #region Org.WebRtc.MediaSource

            //------------------------------------------------------------------
            //------------------------------------------------------------------
            // Org.WebRtc.MediaSource
            //------------------------------------------------------------------
            //------------------------------------------------------------------


            #endregion // Org.WebRtc.MediaSource


        }

    } //WebRtc
} //Org

