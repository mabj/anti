# Context

This technique uses the `DbgPrint` function from ntdll.dll to detect debugger presence:

- Loads ntdll.dll and resolves DbgPrint function pointer
- Calls DbgPrint inside a structured exception handler (__try/__except)
- Checks if exception code is DBG_PRINTEXCEPTION_C
- Returns true if no exception occurs (debugger attached), false if exception occurs (no debugger)

The technique exploits how Windows handles debug print exceptions when a debugger is attached.

Note: As per the code comments, this technique doesn't work on Windows 10 64-bit systems.

## Build

1. Make sure Visual Studio is installed (`vc.exe` is required because of `__try` and `__except`)
2. update the variable `$vcVarsPath` of the `build.ps1`with the path to VC
3. Run `make` using powershell

## References

- <https://github.com/ayoubfaouzi/al-khaser/blob/master/al-khaser/AntiDebug/SetHandleInformation_API.cpp>
