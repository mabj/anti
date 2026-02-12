# Context

Detects a debugger by checking for the heap tail-checking sentinel pattern `0xABABABAB`. When a process is launched under a debugger, Windows enables `HEAP_TAIL_CHECKING_ENABLED`, which appends the fill pattern `0xABABABAB` immediately after each heap allocation's user data. The technique uses `HeapWalk` to find the first busy heap entry, then reads the memory right after the allocation's data region to check for this sentinel value.

Key characteristics:

- Uses `HeapWalk` with `GetProcessHeap` to enumerate heap entries
- Locates the first `PROCESS_HEAP_ENTRY_BUSY` block in the default process heap
- Reads the DWORD immediately after the allocation data (`lpData + cbData`)
- Checks for the `0xABABABAB` fill pattern indicating tail-checking is enabled
- Debuggers cause Windows to set `HEAP_TAIL_CHECKING_ENABLED` via `NtGlobalFlag`
- Lightweight technique — only requires walking the heap once to the first busy entry

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

- [CheckPoint Anti-Debug: Heap Protection](https://anti-debug.checkpoint.com/techniques/debug-flags.html#manual-checks-heap-protection)
- [Unprotect: Heap Flag](https://unprotect.it/technique/heap-flag/)
- [Microsoft HeapWalk](https://learn.microsoft.com/en-us/windows/win32/api/heapapi/nf-heapapi-heapwalk)
