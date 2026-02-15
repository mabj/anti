# Context

This technique checks if the current process or a remote process is attached to a debugger by calling CheckRemoteDebuggerPresent API from kernel32.dll. Internally, this function uses NtQueryInformationProcess to query the ProcessDebugPort information class.

Key aspects:
- Calls `CheckRemoteDebuggerPresent()` from kernel32.dll
- Can check both local and remote processes for debugger attachment
- Internally uses `NtQueryInformationProcess` with ProcessDebugPort (0x7)
- Returns -1 (0xFFFFFFFF) in the output parameter if a debugger is present
- Returns 0 if no debugger is attached
- More versatile than IsDebuggerPresent as it can check remote processes
- Still bypassable through PEB manipulation or API hooking

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

- [Microsoft: CheckRemoteDebuggerPresent function](https://learn.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-checkremotedebuggerpresent)
- [Microsoft: NtQueryInformationProcess function](https://learn.microsoft.com/en-us/windows/win32/api/winternl/nf-winternl-ntqueryinformationprocess)
