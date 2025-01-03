> [!WARNING]
> AppLifecycleOptOut has been deprecated in favor of [Stonecutter](https://github.com/Aetopia/Stonecutter).<br>
> AppLifecycleOptOut was originally made to fix issues caused by app suspension in Minecraft: Bedrock Edition.<br>
> Stonecutter focuses on fixing known bugs on Mojang's bug tracker for [Minecraft: Bedrock Edtion](https://bugs.mojang.com/projects/MCPE/summary).<br>

# AppLifecycleOptOut
 A tool to prevent UWP apps from being suspended.

## Context
UWP apps are governed by an application model, that defines how their execution states are handled.<br>
The following image showcases the possible app model states, an application may go through.<br>

<img src="https://raw.githubusercontent.com/MicrosoftDocs/windows-dev-docs/docs/uwp/launch-resume/images/updated-lifecycle.png">

The main intent of this application model is for power saving and reduction in system usage.

In certain instances, it might be desirable to prevent an app from suspending, potential reasons include:<br>
1. For performing prolonged workloads when in the background.
2. Prevention of undesirable behavior occuring in apps due to UWP app suspension.

Luckily, a developer may use the following for prolonged workloads that must be done when an UWP app is in the background:<br>

1. **[`ExtendedExecutionSession`](https://learn.microsoft.com/en-us/uwp/api/windows.applicationmodel.extendedexecution.extendedexecutionsession)**:<br>
    The following may be used to request more time for performing the specified workload before being suspended by the operating system, unfortunately this simply delays suspension doesn't prevent it.

2. **[`ExtendedExecutionForegroundSession`](https://learn.microsoft.com/en-us/uwp/api/windows.applicationmodel.extendedexecution.foreground.extendedexecutionforegroundsession)**:<br>
    The following may be used to prevent an UWP app from being suspended by the operating system, although this fulfills our needs, it prevents an UWP app from being published on the Microsoft Store.
    
3. **[`IPackageDebugSettings::EnableDebugging`](https://learn.microsoft.com/en-us/windows/win32/api/shobjidl_core/nf-shobjidl_core-ipackagedebugsettings-enabledebugging)**:<br>
    This following may be used to enable debug mode for an UWP app, when enabled the following happens:<br>     
    - Optionally enables debugger attach on activation.
    - Disables activation timeouts.
    - Disables automatic process suspension.
    - Disables automatic process termination.
    - Disables automatic process resumption.
    <br>
    
Out of the 3 methods, the 3rd one maybe used safely with any UWP app to prevent automatic suspension by the operating system.

## Usage
1. Download the latest release from [GitHub Releases](https://github.com/Aetopia/AppLifecycleOptOut/releases/latest).
2. Use the following command in PowerShell to obtain current installed UWP apps along with their package family and full names.<br>

    **Command**:<br>
    ```ps
    $AppxPackages = Get-AppxPackage 
    Get-StartApps | 
    ForEach-Object { 
        [Object]$StartApp = $_
        [Object]$AppxPackage = $AppxPackages |  Where-Object { $StartApp.AppID -like "$($_.PackageFamilyName)*" }
        if ($AppxPackage) { 
            Write-Host "$($StartApp.Name):`n`t$($AppxPackage.PackageFamilyName)`n`t$($AppxPackage.PackageFullName)`n" 
        } 
    }
    ```

    **Output**:<br>
    ```
    Settings:
            windows.immersivecontrolpanel_cw5n1h2txyewy
            windows.immersivecontrolpanel_10.0.2.1000_neutral_neutral_cw5n1h2txyewy
    ```

3. Provide the full package names of the UWP apps that shouldn't be suspended by the operating system to `AppLifecycleOptOut.exe` like this:<br>

    ```ps
    AppLifecycleOptOut.exe PackageFamilyName1 PackageFullName1 PackageFamilyName2 PackageFullName2
    ```
> [!IMPORTANT]
> - You need to simply run the program, everytime you log in.<br>
> - If possible always specify package family names, this way the program can resolve package full names correctly.<br>
> - Use package full names, if you need to use the program with any loose package.

## Building
1. Install [`GCC`](https://github.com/brechtsanders/winlibs_mingw) and [`UPX`](https://upx.github.io) for optional compression.
2. Run [`Build.cmd`](Build.cmd).
