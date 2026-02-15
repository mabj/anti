# Context

This technique detects a kernel debugger by calling `NtSetDebugFilterState` (the native API behind `DbgSetDebugFilterState`). The function attempts to modify the debug output filter state for a given component ID and level. Under normal conditions (no kernel debugger attached), the call fails and returns a non-success status. When a kernel debugger is present, the call succeeds because the debug filter infrastructure is active.

Key characteristics:

- Dynamically resolves `NtSetDebugFilterState` from `ntdll.dll` via `GetProcAddress`
- Calls `NtSetDebugFilterState(0, 0, TRUE)` to enable debug output for component 0, level 0
- Returns `NT_SUCCESS` only when a kernel debugger is attached and accepting filter changes
- Primarily detects kernel-mode debuggers (WinDbg in kernel mode, KD)
- Lightweight single API call with no side effects on normal execution
- May require elevated privileges depending on OS version

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

- [Check Point: DbgSetDebugFilterState](https://anti-debug.checkpoint.com/techniques/debug-flags.html#using-dbgsetdebugfilterstate)
- [Microsoft: DbgSetDebugFilterState function](https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-dbgsetdebugfilterstate)
