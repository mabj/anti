# Context

This anti-debug technique uses structured exception handling (SEH) to detect debuggers by raising a `DBG_CONTROL_C` exception and observing its handling behavior.

Key characteristics:

- Raises a control-C exception (`DBG_CONTROL_C`) that debuggers typically intercept
- Uses SEH blocks (`__try`/`__except`) to handle the exception
- Returns `false` when the exception is handled by the program (no debugger)
- Returns `true` when the exception is intercepted by a debugger

The technique exploits how debuggers handle exceptions - when attached, they catch the exception before the program's exception handler can process it.

## Build

1. Make sure Visual Studio is installed (`vc.exe` is required because of `__try` and `__except`)
2. update the variable `$vcVarsPath` of the `build.ps1`with the path to VC
3. Run `make` using powershell

## References

- <https://anti-debug.checkpoint.com/techniques/exceptions.html#raiseexception>
- <https://docs.microsoft.com/en-us/windows/win32/api/errhandlingapi/nf-errhandlingapi-raiseexception>
