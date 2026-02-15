# Context

This technique patches the DbgBreakPoint function in ntdll.dll at runtime to prevent debuggers from breaking into the process using standard breakpoint mechanisms. By replacing the function's first byte with a RET instruction, the technique neutralizes attempts to trigger debugging breakpoints.

Key aspects:
- Locates ntdll.dll using `GetModuleHandleA("ntdll.dll")`
- Finds `DbgBreakPoint` function address via `GetProcAddress()`
- Changes memory protection with `VirtualProtect()` to allow writing
- Writes `0xC3` (RET instruction) to replace the first byte of DbgBreakPoint
- Restores original memory protection after patching
- Effect: Debuggers cannot break into the process using DbgBreakPoint
- The patch occurs in memory at runtime, avoiding static detection
- Prevents the debug interrupt mechanism from working correctly

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

- [Check Point: Patch DbgBreakPoint](https://anti-debug.checkpoint.com/techniques/process-memory.html#patch_ntdll_dbgbreakpoint)
- [Microsoft: DbgBreakPoint function](https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-dbgbreakpoint)
