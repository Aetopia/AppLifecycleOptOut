# AppLifecycleOptOut
 A tool to prevent UWP apps from being suspended.

## Context
UWP apps are governed by an application model, that defines how their execution states are handled.<br>
The following image showcases the possible app model states, an application may go through.<br>

<img src="https://raw.githubusercontent.com/MicrosoftDocs/windows-dev-docs/docs/uwp/launch-resume/images/updated-lifecycle.png">

The main intent of this application model is for power saving and reduction in system usage.

In certain instances, it might be desirable to prevent an app from suspending, potential reasons include:<br>
1. For performing prolonged workload when in the background.
2. Prevention of undesirable behavior occuring in apps due to UWP app suspension.

Luckily, a developer may use the following for prolonged workloads that must be done when an UWP app is in the background:<br>

1. **[`ExtendedExecutionSession`](https://learn.microsoft.com/en-us/uwp/api/windows.applicationmodel.extendedexecution.extendedexecutionsession)**:<br>
    The following may be used to request more time for performing the specified workload before suspended by the operating system, unfortunately this simply delays suspension doesn't prevent it.

    > [!NOTE]
    > Must be called from a WinRT application.

2. **[`ExtendedExecutionForegroundSession`](https://learn.microsoft.com/en-us/uwp/api/windows.applicationmodel.extendedexecution.foreground.extendedexecutionforegroundsession)**:<br>
    The following may be used to prevent an UWP app from being suspended by the operating system, although this fulfills our needs, it prevents an UWP app from being published on the Microsoft Store.
    
    > [!NOTE]
    > Must be called from a WinRT application.

3. **[`IPackageDebugSettings::EnableDebugging`](https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nf-shobjidl_core-ipackagedebugsettings-enabledebugging)**:<br>
    This following may be used to enable debug mode for a UWP app, when enabled the following happens:<br>     
    - Optionally enables debugger attach on activation.
    - Disables activation timeouts.
    - Disables automatic process suspension.
    - Disables automatic process termination.
    - Disables automatic process resumption.
    <br>
    
    > [!NOTE] 
    > Must be called from a Win32 application.

Out of the 3 methods, the 3rd one maybe used safely with any UWP app to prevent automatic suspension by the operating system.

## Usage
1. Download the latest release from [GitHub Releases](https://github.com/Aetopia/AppLifecycleOptOut/releases/latest).
2. Use the following command in PowerShell to obtain current installed UWP apps along with their package family name.<br>

    **Command**:<br>
    ```ps
    $AppxPackages = Get-AppxPackage; Get-StartApps | ForEach-Object { [Object]$StartApp = $_; [Object]$AppxPackage = $AppxPackages | Where-Object { $StartApp.AppID -like "$($_.PackageFamilyName)*" }; if ($AppxPackage) { Write-Host "$($StartApp.Name) : $($AppxPackage.PackageFamilyName)" } }
    ```

    **Output**:<br>
    ```ps
    Settings : windows.immersivecontrolpanel_cw5n1h2txyewy
    ```

3. Provide the full package names of the UWP apps that shouldn't be suspended by the operating system to `AppLifecycleOptOut.exe` like this:<br>

    ```ps
    AppLifecycleOptOut.exe PackageFamilyName1 PackageFamilyName2 PackageFamilyName3
    ```
    > [!NOTE]
    > You need to simply run the program, everytime you log in.<br>
    > If an app is still getting suspended after running the program, verify the provided package family names.

## Building
1. Install [`GCC`](https://github.com/brechtsanders/winlibs_mingw) and [`UPX`](https://upx.github.io) for optional compression.
2. Run `Build.bat`.