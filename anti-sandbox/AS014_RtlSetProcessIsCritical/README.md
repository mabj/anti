# Context

This technique abuses the undocumented `ntdll!RtlSetProcessIsCritical` API to detect API hooking by a sandbox. It marks the current process as *critical* and then reads the `BreakOnTermination` flag back with `NtQueryInformationProcess`. If the call to set the flag reports success but the flag is not actually set, the API has been hooked/neutered — a strong indicator of an automated analysis environment.

Key characteristics:

- `RtlSetProcessIsCritical(TRUE, NULL, FALSE)` internally calls `NtSetInformationProcess` with the `ProcessBreakOnTermination` (0x1D) class, flipping the `BreakOnTermination` flag in the kernel `EPROCESS` structure.
- Verification uses `NtQueryInformationProcess(ProcessBreakOnTermination)` to read the flag back (set-then-query mismatch detection).
- Sandboxes frequently hook these APIs into a silent no-op (still returning `STATUS_SUCCESS`) so a critical process exiting cannot bugcheck the analysis host — exactly the mismatch this PoC looks for.
- Requires **Administrator privileges** (the kernel demands `SeDebugPrivilege` to change a process's critical status); the PoC enables `SeDebugPrivilege` in-process via `AdjustTokenPrivileges`.
- **Safety**: while the flag is set, terminating the process would bugcheck the machine (`CRITICAL_PROCESS_DIED`, 0xEF). The PoC resets the flag to `FALSE` before exiting.

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

- [Geoff Chappell - RtlSetProcessIsCritical](https://www.geoffchappell.com/studies/windows/win32/ntdll/api/rtl/peb/setprocessiscritical.htm)
- [6nz/RtlSetProcessIsCritical (PoC)](https://github.com/6nz/RtlSetProcessIsCritical)
- [Microsoft Win32 API - NtSetInformationProcess](https://learn.microsoft.com/en-us/windows/win32/procthread/zwsetinformationprocess)
