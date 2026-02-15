# Context

This technique detects debuggers by examining heap flags using RtlQueryProcessDebugInformation. This function provides comprehensive debugging information about a process, including heap metadata that Windows modifies when a debugger is attached.

Key aspects:
- Uses `RtlCreateQueryDebugBuffer()` to allocate a debug information buffer
- Calls `RtlQueryProcessDebugInformation()` to retrieve detailed process debug data
- Examines flags of the first heap in the process
- Detects if any non-HEAP_GROWABLE flags are set
- Based on the observation that debuggers modify heap flags when attaching
- More comprehensive than RtlQueryProcessHeapInformation
- Provides additional debugging metadata beyond just heap information

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

- [Check Point: RtlQueryProcessDebugInformation](https://anti-debug.checkpoint.com/techniques/debug-flags.html#using-win32-api-checks-rtlqueryprocessdebuginformation)
- [Microsoft: Heap Functions](https://learn.microsoft.com/en-us/windows/win32/memory/heap-functions)
