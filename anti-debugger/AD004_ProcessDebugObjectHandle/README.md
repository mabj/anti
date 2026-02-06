# Context

This technique checks if a process is being debugged by querying the ProcessDebugObjectHandle using NtQueryInformationProcess. When a debugger attaches to a process, Windows creates a debug object and associates it with the process. By checking if this handle exists, the technique can detect debugging activity.

Key aspects:
- Uses `NtQueryInformationProcess` with `ProcessDebugObjectHandle` information class (0x1E)
- Queries the handle to the debug object associated with the process
- A non-zero handle indicates an active debugger is attached
- A zero handle indicates no debugger is present
- More difficult to bypass than simple PEB checks
- Requires ntdll.dll for the native API call

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

- [Microsoft: NtQueryInformationProcess function](https://learn.microsoft.com/en-us/windows/win32/api/winternl/nf-winternl-ntqueryinformationprocess)
- [Check Point: ProcessDebugObjectHandle](https://anti-debug.checkpoint.com/techniques/debug-flags.html#manual-checks-processdebugobjecthandle)
