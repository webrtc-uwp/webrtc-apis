
using org_webRtc_MediaSample_t = System.IntPtr;
using instance_id_t = System.IntPtr;
using std_list_float_t_t = System.IntPtr;

namespace Org
{
    namespace WebRtc
    {

        /// <summary>
        /// MediaSample represents an object holder for a platform specific
        /// media sample.
        /// </summary>
        public interface IMediaSample
        {
            /*
            /// <summary>
            /// Returns camera view transform which maps from the coordinate
            /// system to the camera.
            /// </summary>
            System.Collections.Generic.IReadOnlyList<float> GetCameraViewTransform();

            /// <summary>
            /// Returns camera projection transform which maps from the camera
            /// to pixels in the image.
            /// </summary>
            System.Collections.Generic.IReadOnlyList<float> GetCameraProjectionTransform();
            */
        }

        /// <summary>
        /// MediaSample represents an object holder for a platform specific
        /// media sample.
        /// </summary>
        public sealed class MediaSample : System.IDisposable,
                                          Org.WebRtc.IMediaSample
        {

            #region To / From C routines

            //------------------------------------------------------------------
            //------------------------------------------------------------------
            // To / From C routines
            //------------------------------------------------------------------
            //------------------------------------------------------------------

            private class WrapperMakePrivate {}
            private org_webRtc_MediaSample_t native_ = System.IntPtr.Zero;

            private MediaSample(WrapperMakePrivate ignored, org_webRtc_MediaSample_t handle)
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
                Wrapper.Org_WebRtc.OverrideApi.org_webRtc_MediaSample_wrapperDestroy(this.native_);
                this.native_ = System.IntPtr.Zero;
                if (disposing) System.GC.SuppressFinalize(this);
            }

            ~MediaSample()
            {
                Dispose(false);
            }

            internal static MediaSample org_webRtc_MediaSample_FromC(org_webRtc_MediaSample_t handle)
            {
                if (System.IntPtr.Zero == handle) return null;
                return new MediaSample((WrapperMakePrivate)null, Wrapper.Org_WebRtc.OverrideApi.org_webRtc_MediaSample_wrapperClone(handle));
            }

            internal static MediaSample org_webRtc_MediaSample_AdoptFromC(org_webRtc_MediaSample_t handle)
            {
                if (System.IntPtr.Zero == handle) return null;
                return new MediaSample((WrapperMakePrivate)null, handle);
            }

            internal static org_webRtc_MediaSample_t org_webRtc_MediaSample_ToC(MediaSample value)
            {
                if (null == value) return System.IntPtr.Zero;
                return Wrapper.Org_WebRtc.OverrideApi.org_webRtc_MediaSample_wrapperClone(value.native_);
            }

            #endregion // To / From C routines


            #region Org.WebRtc.MediaSample

            //------------------------------------------------------------------
            //------------------------------------------------------------------
            // Org.WebRtc.MediaSample
            //------------------------------------------------------------------
            //------------------------------------------------------------------


                /*
            /// <summary>
            /// Returns camera view transform which maps from the coordinate
            /// system to the camera.
            /// </summary>
            public System.Collections.Generic.IReadOnlyList<float> GetCameraViewTransform()
            {
                std_list_float_t_t wrapper_c_wrapper_result = Wrapper.Org_WebRtc.Api.org_webRtc_MediaSample_getCameraViewTransform(this.native_);
                return Wrapper.Org_WebRtc.Helpers.std_list_float_t_AdoptFromC(wrapper_c_wrapper_result);
            }

            /// <summary>
            /// Returns camera projection transform which maps from the camera
            /// to pixels in the image.
            /// </summary>
            public System.Collections.Generic.IReadOnlyList<float> GetCameraProjectionTransform()
            {
                std_list_float_t_t wrapper_c_wrapper_result = Wrapper.Org_WebRtc.Api.org_webRtc_MediaSample_getCameraProjectionTransform(this.native_);
                return Wrapper.Org_WebRtc.Helpers.std_list_float_t_AdoptFromC(wrapper_c_wrapper_result);
            }
            */

            #endregion // Org.WebRtc.MediaSample


        }

    } //WebRtc
} //Org

