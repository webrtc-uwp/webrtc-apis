
using System.Runtime.InteropServices;

using bool_t = System.Boolean;
using uint64_t = System.UInt64;
using binary_t = System.IntPtr;
using string_t = System.IntPtr;
using raw_pointer_t = System.IntPtr;
using binary_size_t = System.UInt64;
using generic_handle_t = System.IntPtr;
using instance_id_t = System.IntPtr;
using callback_event_t = System.IntPtr;
using event_observer_t = System.IntPtr;
using const_char_star_t = System.IntPtr;
using exception_handle_t = System.IntPtr;
using box_bool_t = System.IntPtr;
using box_uchar_t = System.IntPtr;
using box_schar_t = System.IntPtr;
using box_ushort_t = System.IntPtr;
using box_sshort_t = System.IntPtr;
using box_uint_t = System.IntPtr;
using box_sint_t = System.IntPtr;
using box_ulong_t = System.IntPtr;
using box_slong_t = System.IntPtr;
using box_ullong_t = System.IntPtr;
using box_sllong_t = System.IntPtr;
using box_uint8_t = System.IntPtr;
using box_int8_t = System.IntPtr;
using box_uint16_t = System.IntPtr;
using box_int16_t = System.IntPtr;
using box_uint32_t = System.IntPtr;
using box_int32_t = System.IntPtr;
using box_uint64_t = System.IntPtr;
using box_int64_t = System.IntPtr;
using box_float_t = System.IntPtr;
using box_double_t = System.IntPtr;
using box_ldouble_t = System.IntPtr;
using box_binary_t = System.IntPtr;
using box_string_t = System.IntPtr;
using ConstBytePtr = System.IntPtr;
using zs_Time_t = System.IntPtr;
using zs_Days_t = System.IntPtr;
using zs_Hours_t = System.IntPtr;
using zs_Seconds_t = System.IntPtr;
using zs_Minutes_t = System.IntPtr;
using zs_Milliseconds_t = System.IntPtr;
using zs_Microseconds_t = System.IntPtr;
using zs_Nanoseconds_t = System.IntPtr;
using iterator_handle_t = System.IntPtr;
using std_list_uint16_t_t = System.IntPtr;
using uint16_t = System.UInt16;

using org_webRtc_AudioData_t = System.IntPtr;
using org_webRtc_EventQueue_t = System.IntPtr;
using org_webRtc_MediaElement_t = System.IntPtr;
using org_webRtc_MediaSample_t = System.IntPtr;
using org_webRtc_MediaSource_t = System.IntPtr;
using org_webRtc_VideoData_t = System.IntPtr;
using org_webRtc_VideoDeviceInfo_t = System.IntPtr;


namespace Wrapper
{
    namespace Org_WebRtc
    {

        internal static class OverrideApi
        {
            private const string UseDynamicLib = Wrapper.Org_WebRtc.Api.UseDynamicLib;

            private const CallingConvention UseCallingConvention = Wrapper.Org_WebRtc.Api.UseCallingConvention;

            private const UnmanagedType UseBoolMashal = Wrapper.Org_WebRtc.Api.UseBoolMashal;
            private const UnmanagedType UseStringMarshal = Wrapper.Org_WebRtc.Api.UseStringMarshal;


#region Struct API helpers

            //------------------------------------------------------------------
            //------------------------------------------------------------------
            // Struct API helpers
            //------------------------------------------------------------------
            //------------------------------------------------------------------

            #region Org.WebRtc.AudioData

            //------------------------------------------------------------------
            //------------------------------------------------------------------
            // Org.WebRtc.AudioData
            //------------------------------------------------------------------
            //------------------------------------------------------------------


            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static org_webRtc_AudioData_t org_webRtc_AudioData_wrapperClone(org_webRtc_AudioData_t handle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static void org_webRtc_AudioData_wrapperDestroy(org_webRtc_AudioData_t handle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static void org_webRtc_AudioData_wrapperDispose(org_webRtc_AudioData_t handle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static instance_id_t org_webRtc_AudioData_wrapperInstanceId(org_webRtc_AudioData_t handle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static org_webRtc_AudioData_t org_webRtc_AudioData_wrapperCreate_AudioData();

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static org_webRtc_AudioData_t org_webRtc_AudioData_wrapperCreate_AudioDataWithSize(binary_size_t size);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            [return: MarshalAs(UseBoolMashal)]
            public extern static bool_t org_webRtc_AudioData_get_readOnly(org_webRtc_AudioData_t thisHandle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static binary_size_t org_webRtc_AudioData_size(org_webRtc_AudioData_t thisHandle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static void org_webRtc_AudioData_get_data(
                org_webRtc_AudioData_t thisHandle,
                [Out] System.Int16[] buffer,
                binary_size_t size);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static void org_webRtc_AudioData_set_data(
                org_webRtc_AudioData_t thisHandle,
                System.Int16[] buffer,
                binary_size_t size);

            #endregion // Org.WebRtc.AudioData


            #region Org.WebRtc.EventQueueMaker

            //------------------------------------------------------------------
            //------------------------------------------------------------------
            // Org.WebRtc.EventQueueMaker
            //------------------------------------------------------------------
            //------------------------------------------------------------------

            #endregion // Org.WebRtc.EventQueueMaker


            #region Org.WebRtc.MediaElementMaker

            //------------------------------------------------------------------
            //------------------------------------------------------------------
            // Org.WebRtc.MediaElementMaker
            //------------------------------------------------------------------
            //------------------------------------------------------------------


            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static org_webRtc_MediaElement_t org_webRtc_MediaElementMaker_bind(System.IntPtr hwnd);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static System.IntPtr org_webRtc_MediaElementMaker_extract(org_webRtc_MediaElement_t element);


            #endregion // Org.WebRtc.MediaElementMaker


            #region Org.WebRtc.MediaSample

            //------------------------------------------------------------------
            //------------------------------------------------------------------
            // Org.WebRtc.MediaSample
            //------------------------------------------------------------------
            //------------------------------------------------------------------


            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static org_webRtc_MediaSample_t org_webRtc_MediaSample_wrapperClone(org_webRtc_MediaSample_t handle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static void org_webRtc_MediaSample_wrapperDestroy(org_webRtc_MediaSample_t handle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static instance_id_t org_webRtc_MediaSample_wrapperInstanceId(org_webRtc_MediaSample_t handle);

/*
            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static std_list_float_t_t org_webRtc_MediaSample_getCameraViewTransform(org_webRtc_MediaSample_t thisHandle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static std_list_float_t_t org_webRtc_MediaSample_getCameraProjectionTransform(org_webRtc_MediaSample_t thisHandle);
            */

#endregion // Org.WebRtc.MediaSample


            #region Org.WebRtc.MediaSource

            //------------------------------------------------------------------
            //------------------------------------------------------------------
            // Org.WebRtc.MediaSource
            //------------------------------------------------------------------
            //------------------------------------------------------------------


            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static org_webRtc_MediaSource_t org_webRtc_MediaSource_wrapperClone(org_webRtc_MediaSource_t handle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static void org_webRtc_MediaSource_wrapperDestroy(org_webRtc_MediaSource_t handle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static instance_id_t org_webRtc_MediaSource_wrapperInstanceId(org_webRtc_MediaSource_t handle);

            #endregion // Org.WebRtc.MediaSource


            #region Org.WebRtc.VideoData

            //------------------------------------------------------------------
            //------------------------------------------------------------------
            // Org.WebRtc.VideoData
            //------------------------------------------------------------------
            //------------------------------------------------------------------


            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static org_webRtc_VideoData_t org_webRtc_VideoData_wrapperClone(org_webRtc_VideoData_t handle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static void org_webRtc_VideoData_wrapperDestroy(org_webRtc_VideoData_t handle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static void org_webRtc_VideoData_wrapperDispose(org_webRtc_VideoData_t handle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static org_webRtc_VideoData_t org_webRtc_VideoData_wrapperCreate_VideoData(uint64_t size);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static instance_id_t org_webRtc_VideoData_wrapperInstanceId(org_webRtc_VideoData_t handle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            [return: MarshalAs(UseBoolMashal)]
            public extern static bool_t org_webRtc_VideoData_get_is8BitColorSpace(org_webRtc_VideoData_t thisHandle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            [return: MarshalAs(UseBoolMashal)]
            public extern static bool_t org_webRtc_VideoData_get_is16BitColorSpace(org_webRtc_VideoData_t thisHandle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static binary_size_t org_webRtc_VideoData_get_size(org_webRtc_VideoData_t thisHandle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static void org_webRtc_VideoData_get_data8bit(
                org_webRtc_VideoData_t thisHandle,
                [Out] byte[] buffer,
                binary_size_t size);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static void org_webRtc_VideoData_get_data16bit(
                org_webRtc_VideoData_t thisHandle,
                [Out] System.UInt16[] buffer,
                binary_size_t size);


            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static void org_webRtc_VideoData_set_data8bit(
                org_webRtc_VideoData_t thisHandle,
                byte[] buffer,
                binary_size_t size);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static void org_webRtc_VideoData_set_data16bit(
                org_webRtc_VideoData_t thisHandle,
                System.UInt16[] buffer,
                binary_size_t size);

            #endregion // Org.WebRtc.VideoData


            #region Org.WebRtc.VideoDeviceInfo

            //------------------------------------------------------------------
            //------------------------------------------------------------------
            // Org.WebRtc.VideoDeviceInfo
            //------------------------------------------------------------------
            //------------------------------------------------------------------


            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static org_webRtc_VideoDeviceInfo_t org_webRtc_VideoDeviceInfo_wrapperClone(org_webRtc_VideoDeviceInfo_t handle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static void org_webRtc_VideoDeviceInfo_wrapperDestroy(org_webRtc_VideoDeviceInfo_t handle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static instance_id_t org_webRtc_VideoDeviceInfo_wrapperInstanceId(org_webRtc_VideoDeviceInfo_t handle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static string_t org_webRtc_VideoDeviceInfo_get_id(org_webRtc_VideoDeviceInfo_t thisHandle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static string_t org_webRtc_VideoDeviceInfo_get_name(org_webRtc_VideoDeviceInfo_t thisHandle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static bool_t org_webRtc_VideoDeviceInfo_get_isDefault(org_webRtc_VideoDeviceInfo_t thisHandle);

            [DllImport(UseDynamicLib, CallingConvention = UseCallingConvention)]
            public extern static bool_t org_webRtc_VideoDeviceInfo_get_isEnabled(org_webRtc_VideoDeviceInfo_t thisHandle);

            #endregion // Org.WebRtc.VideoDeviceInfo



            #endregion // Struct API helpers

        }

        internal static class OverrideHelpers
        {
          

#region Struct helpers

            //------------------------------------------------------------------
            //------------------------------------------------------------------
            // Struct helpers
            //------------------------------------------------------------------
            //------------------------------------------------------------------

            #region Org.WebRtc.AudioData

            public static Org.WebRtc.AudioData org_webRtc_AudioData_FromC(org_webRtc_AudioData_t handle)
            {
                return Org.WebRtc.AudioData.org_webRtc_AudioData_FromC(handle);
            }

            public static Org.WebRtc.AudioData org_webRtc_AudioData_AdoptFromC(org_webRtc_AudioData_t handle)
            {
                return Org.WebRtc.AudioData.org_webRtc_AudioData_AdoptFromC(handle);
            }

            public static org_webRtc_AudioData_t org_webRtc_AudioData_ToC(Org.WebRtc.AudioData value)
            {
                return Org.WebRtc.AudioData.org_webRtc_AudioData_ToC(value);
            }

            #endregion // Org.WebRtc.AudioData

            #region Org.WebRtc.MediaSample

            public static Org.WebRtc.MediaSample org_webRtc_MediaSample_FromC(org_webRtc_MediaSample_t handle)
            {
                return Org.WebRtc.MediaSample.org_webRtc_MediaSample_FromC(handle);
            }

            public static Org.WebRtc.MediaSample org_webRtc_MediaSample_AdoptFromC(org_webRtc_MediaSample_t handle)
            {
                return Org.WebRtc.MediaSample.org_webRtc_MediaSample_AdoptFromC(handle);
            }

            public static org_webRtc_MediaSample_t org_webRtc_MediaSample_ToC(Org.WebRtc.MediaSample value)
            {
                return Org.WebRtc.MediaSample.org_webRtc_MediaSample_ToC(value);
            }

            #endregion // Org.WebRtc.MediaSample

            #region Org.WebRtc.MediaSource

            public static Org.WebRtc.MediaSource org_webRtc_MediaSource_FromC(org_webRtc_MediaSource_t handle)
            {
                return Org.WebRtc.MediaSource.org_webRtc_MediaSource_FromC(handle);
            }

            public static Org.WebRtc.MediaSource org_webRtc_MediaSource_AdoptFromC(org_webRtc_MediaSource_t handle)
            {
                return Org.WebRtc.MediaSource.org_webRtc_MediaSource_AdoptFromC(handle);
            }

            public static org_webRtc_MediaSource_t org_webRtc_MediaSource_ToC(Org.WebRtc.MediaSource value)
            {
                return Org.WebRtc.MediaSource.org_webRtc_MediaSource_ToC(value);
            }

            #endregion // Org.WebRtc.MediaSource

            #region Org.WebRtc.VideoData

            public static Org.WebRtc.VideoData org_webRtc_VideoData_FromC(org_webRtc_VideoData_t handle)
            {
                return Org.WebRtc.VideoData.org_webRtc_VideoData_FromC(handle);
            }

            public static Org.WebRtc.VideoData org_webRtc_VideoData_AdoptFromC(org_webRtc_VideoData_t handle)
            {
                return Org.WebRtc.VideoData.org_webRtc_VideoData_AdoptFromC(handle);
            }

            public static org_webRtc_VideoData_t org_webRtc_VideoData_ToC(Org.WebRtc.VideoData value)
            {
                return Org.WebRtc.VideoData.org_webRtc_VideoData_ToC(value);
            }

            #endregion // Org.WebRtc.VideoData

            #region Org.WebRtc.VideoDeviceInfo

            public static Org.WebRtc.VideoDeviceInfo org_webRtc_VideoDeviceInfo_FromC(org_webRtc_VideoDeviceInfo_t handle)
            {
                return Org.WebRtc.VideoDeviceInfo.org_webRtc_VideoDeviceInfo_FromC(handle);
            }

            public static Org.WebRtc.VideoDeviceInfo org_webRtc_VideoDeviceInfo_AdoptFromC(org_webRtc_VideoDeviceInfo_t handle)
            {
                return Org.WebRtc.VideoDeviceInfo.org_webRtc_VideoDeviceInfo_AdoptFromC(handle);
            }

            public static org_webRtc_VideoDeviceInfo_t org_webRtc_VideoDeviceInfo_ToC(Org.WebRtc.VideoDeviceInfo value)
            {
                return Org.WebRtc.VideoDeviceInfo.org_webRtc_VideoDeviceInfo_ToC(value);
            }

            #endregion // Org.WebRtc.VideoDeviceInfo

#endregion // Struct helpers



        }


    } // namespace Org_WebRtc
} // namespace Wrapper
