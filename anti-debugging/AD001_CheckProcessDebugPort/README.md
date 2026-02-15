# Context

This technique checks whether a debugger is attached to the current process by querying the ProcessDebugPort value using the Windows Native API function NtQueryInformationProcess. This low-level approach can bypass some debugger detection evasion techniques that only hook higher-level APIs.

Key aspects:
- Uses `NtQueryInformationProcess` from ntdll.dll instead of higher-level kernel32 APIs
- Specifically queries the `ProcessDebugPort` information class (0x7)
- Returns a non-zero debug port value when an active debugger is attached
- More difficult to hook than kernel32.dll functions
- Bypasses some user-mode debugger detection evasion techniques
- Requires linking against ntdll.dll

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
- [Check Point: ProcessDebugPort](https://anti-debug.checkpoint.com/techniques/debug-flags.html#manual-checks-processdebugport)
