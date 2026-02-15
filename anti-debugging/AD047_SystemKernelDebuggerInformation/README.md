# Context

This anti-debugging technique detects kernel-mode debuggers by querying system-level kernel debugger information flags.

Key aspects:

- Uses `NtQuerySystemInformation()` with `SystemKernelDebuggerInformation` class (0x23)
- Queries two kernel flags: `DebuggerEnabled` and `DebuggerNotPresent`
- Detects kernel debuggers attached at system level (WinDbg kernel mode, SoftICE)
- Returns true if `DebuggerEnabled` is true AND `DebuggerNotPresent` is false
- Operates at system level rather than process level
- Effective against kernel-mode debuggers that user-mode techniques cannot detect
- Requires appropriate privileges to query kernel information
- Cannot be bypassed by standard user-mode anti-anti-debugging techniques


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

- [Check Point: NtQuerySystemInformation (KernelDebugger)](https://anti-debug.checkpoint.com/techniques/debug-flags.html#ntquerysysteminformation-systemkerneldebuggerinformation)
- [Microsoft: NtQuerySystemInformation function](https://learn.microsoft.com/en-us/windows/win32/api/winternl/nf-winternl-ntquerysysteminformation)
