typedef int __stdcall netCONSOLE_HANDLER(const char *buf);
typedef void __stdcall netERRMSG_HANDLER(const char *ErrMsg);

extern "C" __declspec(dllexport) int __stdcall KM_dotnet_Interop_New(int *handle, int board);
extern "C" __declspec(dllexport) int __stdcall KM_dotnet_Interop_Free(int *handle);
