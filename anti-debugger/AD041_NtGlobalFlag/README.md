# Context

This technique reads the `NtGlobalFlag` field directly from the PEB to determine whether the process was created by a debugger. When a debugger launches a process, the Windows heap manager automatically enables three diagnostic flags (`FLG_HEAP_ENABLE_TAIL_CHECK`, `FLG_HEAP_ENABLE_FREE_CHECK`, `FLG_HEAP_VALIDATE_PARAMETERS`), resulting in a combined value of `0x70` at the flag offset.

Key characteristics:

- Reads the PEB via segment registers (`fs:[0x30]` on x86, `gs:[0x60]` on x64)
- Checks `NtGlobalFlag` at PEB offset `0x68` (x86) or `0xBC` (x64)
- Tests for the bitmask `0x70` — the combination of three heap debugging flags
- Detects whether the process was **created** by a debugger, not just attached to one
- Does not call any API, making it invisible to API-level hooks
- Complementary to AD005 (CheckPEB), which checks `BeingDebugged` and `NtGlobalFlag` lives at a different PEB offset

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
