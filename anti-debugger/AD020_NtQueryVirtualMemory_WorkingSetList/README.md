# Context

This anti-debug technique detects debuggers by querying the process's working set information using `NtQueryVirtualMemory`. It specifically checks the memory page containing the detection function for unusual sharing flags that indicate debugger manipulation.

Key characteristics:
- Uses `MemoryWorkingSetList` information class to retrieve working set details
- Locates the memory page containing the `__is_debugged` function
- Checks if the page is marked as non-shared (`Shared == 0`) or has zero share count (`ShareCount == 0`)
- These flags often indicate debugger activity due to memory breakpoints or code modifications

## Build (Docker)

```
$ make build-image
$ make build
```

## References

- https://anti-debug.checkpoint.com/techniques/debug-flags.html#using-win32-api-checks-rtlqueryprocessheapinformation