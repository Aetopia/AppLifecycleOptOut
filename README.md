# AppLifecycleOptOut
 A tool to prevent UWP apps from being suspended.

## Aim
### Context
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
    