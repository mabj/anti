# Context

This technique detects a debugger by querying the `ProcessDebugFlags` information class (`0x1f`) via `NtQueryInformationProcess`. When no debugger is attached the flag is non-zero, but it drops to `0` as soon as a debugger is present, making it a simple and reliable check.

Key characteristics:

- Uses `NtQueryInformationProcess` with information class `ProcessDebugFlags` (`0x1f`)
- Returns `0` when a debugger is attached, non-zero otherwise
- Lower-level than `IsDebuggerPresent` or `CheckRemoteDebuggerPresent`, making it harder to hook
- Complementary to `ProcessDebugPort` (`0x7`, AD001) and `ProcessDebugObjectHandle` (`0x1e`, AD004) — together they cover all three debug-related information classes
- Requires linking against `ntdll.dll`

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
