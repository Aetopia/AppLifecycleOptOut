#define _WIN32_WINNT _WIN32_WINNT_WIN10
#include <initguid.h>
#include <windows.h>
#include <appmodel.h>
#include <shobjidl.h>

INT wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, INT nShowCmd)
{
    INT iNumArgs = 0;
    PWSTR *rgszArgvW = CommandLineToArgvW(lpCmdLine, &iNumArgs),
          *rgszPackageFullNames = NULL,
          pBuffer = NULL;
    IPackageDebugSettings *pPackageDebugSettings = NULL;
    UINT32 u32Index = 0,
           u32Count = 0,
           u32BufferLength = 0;
    HANDLE hHeap = GetProcessHeap();

    (VOID) CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    (VOID) CoCreateInstance(&CLSID_PackageDebugSettings,
                            NULL,
                            CLSCTX_INPROC_SERVER,
                            &IID_IPackageDebugSettings,
                            (LPVOID *)&pPackageDebugSettings);

    for (INT iIndex = 0;
         iIndex < iNumArgs;
         iIndex += 1)
    {
        (VOID) pPackageDebugSettings->lpVtbl->EnableDebugging(pPackageDebugSettings,
                                                              rgszArgvW[iIndex],
                                                              NULL,
                                                              NULL);
        if (GetPackagesByPackageFamily(rgszArgvW[iIndex],
                                       &u32Count,
                                       NULL,
                                       &u32BufferLength,
                                       NULL) != ERROR_INSUFFICIENT_BUFFER)
            continue;
        rgszPackageFullNames = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, sizeof(PWSTR) * u32Count);
        pBuffer = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, sizeof(WCHAR) * u32BufferLength);
        if (GetPackagesByPackageFamily(rgszArgvW[iIndex],
                                       &u32Count,
                                       rgszPackageFullNames,
                                       &u32BufferLength,
                                       pBuffer) == ERROR_SUCCESS)
            for (u32Index = 0; u32Index < u32Count; u32Index += 1)
                (VOID) pPackageDebugSettings->lpVtbl->EnableDebugging(pPackageDebugSettings,
                                                                      rgszPackageFullNames[u32Index],
                                                                      NULL,
                                                                      NULL);
        (VOID) HeapFree(hHeap, 0, rgszPackageFullNames);
        (VOID) HeapFree(hHeap, 0, pBuffer);
    }

    (VOID) pPackageDebugSettings->lpVtbl->Release(pPackageDebugSettings);
    (VOID) CloseHandle(hHeap);
    (VOID) LocalFree(rgszArgvW);
    (VOID) CoUninitialize();

    return EXIT_SUCCESS;
}