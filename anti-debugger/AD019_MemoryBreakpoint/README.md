# Context

This technique uses guard page exceptions to detect debugger presence. It allocates memory with PAGE_GUARD protection and attempts to execute code in it. The technique exploits the fact that debuggers may suppress or handle guard page violations differently than normal exception handlers.

Key aspects:
- Allocates executable memory with `VirtualAlloc()`
- Writes a simple RET instruction (`0xC3`) to the allocated memory
- Marks the page as a guard page using `VirtualProtect()` with `PAGE_EXECUTE_READ | PAGE_GUARD`
- Attempts to execute the RET instruction in a protected __try block
- Checks if a `STATUS_GUARD_PAGE_VIOLATION` exception (0x80000001) occurs
- If exception is caught by the program, no debugger is present
- If exception is not caught (suppressed by debugger), debugger is detected
- Note: Works on OllyDbg and ImmunityDbg but not x64dbg
- Requires Visual Studio compiler for structured exception handling support

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

- [Check Point: Memory Breakpoints (Page Guard)](https://anti-debug.checkpoint.com/techniques/process-memory.html#memory-breakpoints)
- [Microsoft: VirtualProtect function](https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-virtualprotect)
- [al-khaser: MemoryBreakpoints Implementation](https://github.com/ayoubfaouzi/al-khaser/blob/master/al-khaser/AntiDebug/MemoryBreakpoints_PageGuard.cpp)
