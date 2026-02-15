# Context

This technique hooks the DbgUiRemoteBreakin function in ntdll.dll to prevent debuggers from attaching to or controlling the process. When a debugger attempts to break in using this function, the hooked version immediately terminates the process instead of allowing debugger attachment.

Key aspects:
- Locates `DbgUiRemoteBreakin` function in ntdll.dll
- Constructs architecture-specific shellcode to call `TerminateProcess()`
- Changes memory protection to PAGE_EXECUTE_READWRITE with `VirtualProtect()`
- Writes the hook shellcode over the original function prologue
- Restores original memory protection after patching
- Effect: Prevents debuggers from gaining control by terminating on break-in attempts
- Works on both x86 and x64 architectures with different shellcode
- More aggressive than simple patching as it terminates the process

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

- [Check Point: Hook DbgUiRemoteBreakin](https://anti-debug.checkpoint.com/techniques/process-memory.html#hook-dbguiremotebreakin)
- [Microsoft: TerminateProcess function](https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-terminateprocess)
