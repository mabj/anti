# Context

This technique detects debuggers by examining heap flags that Windows modifies when a debugger is attached. It uses RtlQueryProcessHeapInformation to access detailed heap metadata and checks for flag modifications that indicate debugging activity.

Key aspects:
- Uses `RtlCreateQueryDebugBuffer()` to allocate a debug information buffer
- Calls `RtlQueryProcessHeapInformation()` to retrieve heap metadata
- Examines flags of the first heap in the process
- Detects if any non-HEAP_GROWABLE flags are set
- Based on the observation that debuggers modify heap flags when attaching
- Flags like ForceFlags and Flags are commonly altered during debugging
- Lower-level check than simple PEB inspection

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

- [Check Point: RtlQueryProcessHeapInformation](https://anti-debug.checkpoint.com/techniques/debug-flags.html#using-win32-api-checks-rtlqueryprocessheapinformation)
- [Microsoft: Heap Functions](https://learn.microsoft.com/en-us/windows/win32/memory/heap-functions)
