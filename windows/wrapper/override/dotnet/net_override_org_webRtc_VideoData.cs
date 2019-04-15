
using org_webRtc_VideoData_t = System.IntPtr;
using instance_id_t = System.IntPtr;
using bool_t = System.Boolean;
using box_bool_t = System.IntPtr;
using std_list_uint8_t_t = System.IntPtr;
using std_list_uint16_t_t = System.IntPtr;

namespace Org
{
    namespace WebRtc
    {

        public interface IVideoData
        {
            bool Is8BitColorSpace { get; }
            bool Is16BitColorSpace { get; }

            /// <summary>
            /// Gets the buffer data size.
            /// </summary>
            System.UInt64 Size { get; }

            /// <summary>
            /// Gets the video 8 bit color space data. <summary>
            /// </summary>
            byte[] GetData8Bit();

            /// <summary>
            /// Gets the video 8 bit color space data. <summary>
            /// </summary>
            System.UInt16[] GetData16Bit();

        }

        public sealed class VideoData : System.IDisposable,
                                        Org.WebRtc.IVideoData
        {

            #region To / From C routines

            //------------------------------------------------------------------
            //------------------------------------------------------------------
            // To / From C routines
            //------------------------------------------------------------------
            //------------------------------------------------------------------

            private class WrapperMakePrivate {}
            private org_webRtc_VideoData_t native_ = System.IntPtr.Zero;

            private VideoData(WrapperMakePrivate ignored, org_webRtc_VideoData_t handle)
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
                Wrapper.Org_WebRtc.OverrideApi.org_webRtc_VideoData_wrapperDispose(this.native_);
                Wrapper.Org_WebRtc.OverrideApi.org_webRtc_VideoData_wrapperDestroy(this.native_);
                this.native_ = System.IntPtr.Zero;
                if (disposing) System.GC.SuppressFinalize(this);
            }

            ~VideoData()
            {
                Dispose(false);
            }

            internal static VideoData org_webRtc_VideoData_FromC(org_webRtc_VideoData_t handle)
            {
                if (System.IntPtr.Zero == handle) return null;
                return new VideoData((WrapperMakePrivate)null, Wrapper.Org_WebRtc.OverrideApi.org_webRtc_VideoData_wrapperClone(handle));
            }

            internal static VideoData org_webRtc_VideoData_AdoptFromC(org_webRtc_VideoData_t handle)
            {
                if (System.IntPtr.Zero == handle) return null;
                return new VideoData((WrapperMakePrivate)null, handle);
            }

            internal static org_webRtc_VideoData_t org_webRtc_VideoData_ToC(VideoData value)
            {
                if (null == value) return System.IntPtr.Zero;
                return Wrapper.Org_WebRtc.OverrideApi.org_webRtc_VideoData_wrapperClone(value.native_);
            }

            #endregion // To / From C routines


            #region Org.WebRtc.VideoData

            //------------------------------------------------------------------
            //------------------------------------------------------------------
            // Org.WebRtc.VideoData
            //------------------------------------------------------------------
            //------------------------------------------------------------------

            public bool Is8BitColorSpace
            {
                get
                {
                    var result = Wrapper.Org_WebRtc.OverrideApi.org_webRtc_VideoData_get_is8BitColorSpace(this.native_);
                    return (result);
                }
            }
            public bool Is16BitColorSpace
            {
                get
                {
                    var result = Wrapper.Org_WebRtc.OverrideApi.org_webRtc_VideoData_get_is16BitColorSpace(this.native_);
                    return (result);
                }
            }

            /// <summary>
            /// Gets the video buffer data size.
            /// </summary>
            public System.UInt64 Size
            {
                get
                {
                    var result = Wrapper.Org_WebRtc.OverrideApi.org_webRtc_VideoData_size(this.native_);
                    return (result);
                }
            }

            /// <summary>
            /// Gets or sets the video 8 bit color space data.
            /// </summary>
            public byte[] GetData8Bit()
            {
                var size = Wrapper.Org_WebRtc.OverrideApi.org_webRtc_VideoData_size(this.native_);
                if (size < 1)
                    return null;

                byte[] buffer = new byte[size];

                Wrapper.Org_WebRtc.OverrideApi.org_webRtc_VideoData_get_data8bit(this.native_, buffer, size);

                return buffer;
            }

            /// <summary>
            /// Gets or sets the video 8 bit color space data.
            /// </summary>
            public System.UInt16[] GetData16Bit()
            {
                var size = Wrapper.Org_WebRtc.OverrideApi.org_webRtc_VideoData_size(this.native_);
                if (size < 1)
                    return null;

                System.UInt16[] buffer = new System.UInt16[size];

                Wrapper.Org_WebRtc.OverrideApi.org_webRtc_VideoData_get_data16bit(this.native_, buffer, size);

                return buffer;
            }

            #endregion // Org.WebRtc.VideoData


        }

    } //WebRtc
} //Org

