#define _WIN32_WINNT _WIN32_WINNT_WIN10
#include <initguid.h>
#include <windows.h>
#include <shobjidl.h>

INT wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, INT nShowCmd)
{
    INT iNumArgs = 0;
    LPWSTR *rgszArgvW = CommandLineToArgvW(lpCmdLine, &iNumArgs);
    IPackageDebugSettings *pPackageDebugSettings = NULL;

    (VOID) CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    (VOID) CoCreateInstance(&CLSID_PackageDebugSettings,
                            NULL,
                            CLSCTX_INPROC_SERVER,
                            &IID_IPackageDebugSettings,
                            (LPVOID *)&pPackageDebugSettings);

    for (INT iIndex = 0;
         iIndex < iNumArgs;
         iIndex += 1)
        (VOID) pPackageDebugSettings->lpVtbl->EnableDebugging(pPackageDebugSettings,
                                                              rgszArgvW[iIndex],
                                                              NULL,
                                                              NULL);

    pPackageDebugSettings->lpVtbl->Release(pPackageDebugSettings);
    (VOID) LocalFree(rgszArgvW);
    (VOID) CoUninitialize();

    return EXIT_SUCCESS;
}