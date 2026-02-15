# Context

This technique uses SetHandleInformation() to protect a handle from being closed by setting the HANDLE_FLAG_PROTECT_FROM_CLOSE flag. When the process attempts to close this protected handle, it generates an exception. The technique exploits how debuggers intercept and handle these exceptions differently than normal exception handlers.

Key aspects:
- Creates a mutex handle for testing
- Protects the handle using `SetHandleInformation()` with `HANDLE_FLAG_PROTECT_FROM_CLOSE` flag
- Attempts to close the protected handle
- Uses Vectored Exception Handling (VEH) to catch the exception
- If a debugger is attached, closing the protected handle raises an exception
- If no debugger is present, CloseHandle fails silently
- Similar to CloseHandle technique but more explicit about protection

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

- [Microsoft: SetHandleInformation function](https://learn.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-sethandleinformation)
- [al-khaser: SetHandleInformation Implementation](https://github.com/ayoubfaouzi/al-khaser/blob/master/al-khaser/AntiDebug/SetHandleInformation_API.cpp)
