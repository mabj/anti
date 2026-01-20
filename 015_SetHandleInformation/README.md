# Context

This anti-debug technique uses `SetHandleInformation()` to protect a mutex handle from being closed. When the process attempts to close this protected handle:

- If a debugger is attached, it catches the exception first
- If no debugger is attached, the program's exception handler catches it
- The technique exploits how debuggers intercept exception handling

The implementation creates a mutex, protects it with `HANDLE_FLAG_PROTECT_FROM_CLOSE`, then attempts closure in a structured exception handling block.

## Build

1. Make sure Visual Studio is installed (`vc.exe` is required because of `__try` and `__except`)
2. update the variable `$vcVarsPath` of the `build.ps1`with the path to VC
3. Run `make` using powershell

## References

- https://github.com/ayoubfaouzi/al-khaser/blob/master/al-khaser/AntiDebug/SetHandleInformation_API.cpp