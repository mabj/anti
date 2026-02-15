# Context

This technique detects debuggers by querying the process's working set information using NtQueryVirtualMemory. It examines the memory page containing the detection function for unusual sharing flags that indicate debugger manipulation through memory breakpoints or code modifications.

Key aspects:
- Uses `NtQueryVirtualMemory()` with `MemoryWorkingSetList` information class
- Retrieves working set details for all pages in the process
- Locates the memory page containing the detection function itself
- Checks if the page is marked as non-shared (`Shared == 0`)
- Checks if the page has zero share count (`ShareCount == 0`)
- These flags often indicate debugger activity due to memory breakpoints or code hooks
- Memory page attributes change when debuggers modify code pages
- Lower-level check that examines memory management internals

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

- [Check Point: Working Set Checks](https://anti-debug.checkpoint.com/techniques/debug-flags.html#using-win32-api-checks-workingset)
- [Microsoft: NtQueryVirtualMemory function](https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntqueryvirtualmemory)