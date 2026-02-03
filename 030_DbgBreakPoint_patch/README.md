# Context

This anti-debug technique patches the `DbgBreakPoint` function in ntdll.dll to prevent debuggers from breaking into the process.

- **How it works**: Replaces the first byte of `DbgBreakPoint` with `0xC3` (RET instruction)
- **Effect**: Debuggers cannot break into the process using standard breakpoint mechanisms
- **Implementation**:
  - Locates ntdll.dll using `GetModuleHandleA()`
  - Finds `DbgBreakPoint` address via `GetProcAddress()`
  - Changes memory protection with `VirtualProtect()`
  - Writes the `0xC3` byte to patch the function
- **Detection avoidance**: The patch occurs in memory at runtime

## Build (Docker)

```
$ make build-image
$ make build
```

## References

- https://anti-debug.checkpoint.com/techniques/process-memory.html#patch_ntdll_dbgbreakpoint