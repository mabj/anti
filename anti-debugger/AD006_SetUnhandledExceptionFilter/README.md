# Context

This technique detects debuggers by setting an Unhandled Exception Filter (UEF) and triggering an exception. Windows provides four mechanisms to handle exceptions in order: Debugger, Vectored Exception Handlers (VEH), Frame-based SEH (try/except), and Unhandled Exception Filter (UEF) as the last resort. If a debugger is attached, it captures exceptions before they reach the UEF handler.

Key aspects:
- Sets a custom exception handler using `SetUnhandledExceptionFilter()`
- Triggers an INT3 (0xCC) exception intentionally
- If debugger is present, it captures the exception before UEF handler executes
- If no debugger, execution flows to the UEF handler as expected
- Can be combined with Vectored Exception Handlers for more sophisticated detection
- Exploits the exception handling chain priority in Windows

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

- [Check Point: Exception-based Anti-Debug Techniques](https://anti-debug.checkpoint.com/techniques/exceptions.html)
- [Microsoft: SetUnhandledExceptionFilter function](https://learn.microsoft.com/en-us/windows/win32/api/errhandlingapi/nf-errhandlingapi-setunhandledexceptionfilter)
- [GuLoader: Vectored Exception Handler Approach](https://www.sonicwall.com/blog/guloader-demystified-unraveling-its-vectored-exception-handler-approach)
- [Exception-Oriented Programming](https://billdemirkapi.me/exception-oriented-programming-abusing-exceptions-for-code-execution-part-1/)
