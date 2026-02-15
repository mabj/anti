# Context

This technique exploits the behavior of the CloseHandle API (or NtClose) to detect if a process is running under a debugger. According to Microsoft documentation, if the application is running under a debugger, the function throws an exception when it receives an invalid handle value or when called on a handle that was already closed.

Key aspects:
- Calls `CloseHandle()` on an invalid handle or pseudo-handle
- When a debugger is attached, CloseHandle throws an exception
- Without a debugger, the function fails silently with a return value
- Uses Vectored Exception Handling (VEH) to catch the exception
- Exception code indicates debugger presence
- Can also test by closing a handle twice or closing FindFirstFile handles with CloseHandle instead of FindClose

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

- [Microsoft: CloseHandle function](https://learn.microsoft.com/en-us/windows/win32/api/handleapi/nf-handleapi-closehandle)
- [Check Point: CloseHandle Anti-Debug](https://anti-debug.checkpoint.com/techniques/object-handles.html#closehandle)
