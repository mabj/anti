# Context

This technique uses structured exception handling (SEH) to detect debuggers by raising a DBG_CONTROL_C exception and observing its handling behavior. Debuggers typically intercept exceptions before they reach the program's exception handlers, allowing for reliable detection.

Key aspects:
- Raises a `DBG_CONTROL_C` exception (0x40010005) that debuggers typically intercept
- Uses SEH blocks (__try/__except) to handle the exception
- Returns false when the exception is handled by the program's handler (no debugger)
- Returns true when the exception is intercepted by a debugger
- Exploits the exception handling priority where debuggers get first chance at exceptions
- Control-C exceptions are specifically designed to be caught by debuggers
- Requires Visual Studio compiler for structured exception handling support

## Build

### Using Docker (Recommended)

```bash
make build-image  # First time only
make build
```

### Alternative: MinGW

```bash
make
```

## References

- [Check Point: RaiseException Anti-Debug](https://anti-debug.checkpoint.com/techniques/exceptions.html#raiseexception)
- [Microsoft: RaiseException function](https://learn.microsoft.com/en-us/windows/win32/api/errhandlingapi/nf-errhandlingapi-raiseexception)
