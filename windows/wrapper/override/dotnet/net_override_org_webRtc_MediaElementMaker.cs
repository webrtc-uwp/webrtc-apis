
using zs_Any_t = System.IntPtr;
using org_webRtc_MediaElement_t = System.IntPtr;

namespace Org
{
    namespace WebRtc
    {

        public static class MediaElementMaker
        {

            #region Org.WebRtc.MediaElementMaker

            //------------------------------------------------------------------
            //------------------------------------------------------------------
            // Org.WebRtc.MediaElementMaker
            //------------------------------------------------------------------
            //------------------------------------------------------------------


            /// <summary>
            /// Creates an media element object from a media element type.
            /// </summary>
            static public Org.WebRtc.MediaElement Bind(System.IntPtr hwnd)
            {
                org_webRtc_MediaElement_t wrapper_c_wrapper_result = Wrapper.Org_WebRtc.OverrideApi.org_webRtc_MediaElementMaker_bind(hwnd);
                return Wrapper.Org_WebRtc.Helpers.org_webRtc_MediaElement_AdoptFromC(wrapper_c_wrapper_result);
            }

            /// <summary>
            /// Extracts a native media element from an media element object.
            /// </summary>
            static public object Extract(Org.WebRtc.MediaElement element)
            {
                org_webRtc_MediaElement_t wrapper_c_element = Wrapper.Org_WebRtc.Helpers.org_webRtc_MediaElement_ToC(element);
                System.IntPtr hwnd = Wrapper.Org_WebRtc.OverrideApi.org_webRtc_MediaElementMaker_extract(wrapper_c_element);
                Wrapper.Org_WebRtc.Api.org_webRtc_MediaElement_wrapperDestroy(wrapper_c_element);
                return hwnd;
            }

            #endregion // Org.WebRtc.MediaElementMaker


        }

    } //WebRtc
} //Org

