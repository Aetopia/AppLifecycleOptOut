#define _WIN32_WINNT _WIN32_WINNT_WIN10
#include <initguid.h>
#include <windows.h>
#include <appmodel.h>
#include <shobjidl.h>

int WinMainCRTStartup()
{
    INT NumArgs = 0;
    LPWSTR *ArgvW = CommandLineToArgvW(GetCommandLineW(), &NumArgs);
    HANDLE hHeap = GetProcessHeap();

    CoInitialize(NULL);
    IPackageDebugSettings *pPackageDebugSettings = NULL;
    CoCreateInstance(&CLSID_PackageDebugSettings, NULL, CLSCTX_INPROC_SERVER, &IID_IPackageDebugSettings,
                     (LPVOID *)&pPackageDebugSettings);

    for (INT nArg = 0; nArg < NumArgs; nArg++)
    {
        UINT32 count = 0, bufferLength = 0;
        PCWSTR packageFamilyName = ArgvW[nArg];

        if (GetPackagesByPackageFamily(packageFamilyName, &count, NULL, &bufferLength, NULL) !=
            ERROR_INSUFFICIENT_BUFFER)
            continue;

        PWSTR *packageFullNames = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, sizeof(PWSTR) * count),
              buffer = HeapAlloc(hHeap, HEAP_ZERO_MEMORY, sizeof(WCHAR) * bufferLength);

        if (!GetPackagesByPackageFamily(packageFamilyName, &count, packageFullNames, &bufferLength, buffer))
            for (UINT32 nIndex = 0; nIndex < count; nIndex++)
                pPackageDebugSettings->lpVtbl->EnableDebugging(pPackageDebugSettings, packageFullNames[nIndex], NULL,
                                                               NULL);
    }

    ExitProcess(0);
    return 0;
}