# BackgroundTaskCom

Win32 Console application registering a COM based background task.
Using the UWP Background Task infrastructure requires the application to be packaged as an MSIX package.

To ease debugging, the application can be packaged as a [sparse package](https://learn.microsoft.com/en-us/windows/apps/desktop/modernize/grant-identity-to-nonpackaged-apps).

The application performs the following steps:
- Checks if running wit a package identity. If not registers a sparce package
- Requests backgrund task access
- Registers a COM based background task

## Prerequisites
Requires Windows 10 2004 or later.

## Contents

| Folder                     | Description                                                           |
|:---------------------------|:----------------------------------------------------------------------|
| ComBackgroundTask          | Holds the Out of Process COM Server implementing the background tasks |
| Win32Console               | Holds the Win32 Console application registering the background task   |
| Win32Console.Package       | Holds the MSIX packging project for the Win32 Console application     |
| Win32Console.SparsePackage | Holds the sparse package for the Win32 Console application            |
| eng                        | Holds config files and scripts for the MSIX packaging process         |

## References
https://blogs.windows.com/windowsdeveloper/2019/10/29/identity-registration-and-activation-of-non-packaged-win32-apps/
https://learn.microsoft.com/en-us/windows/apps/desktop/modernize/grant-identity-to-nonpackaged-apps
