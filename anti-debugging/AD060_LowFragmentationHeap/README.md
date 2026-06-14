# Context

This technique detects a debugger by inspecting the state of the process heap's Low Fragmentation Heap (LFH) front-end allocator. On modern Windows the default process heap uses the LFH, but when a process is launched under a debugger the loader creates a *debug heap* (driven by the PEB `BeingDebugged` / `NtGlobalFlag` heap flags) that refuses to switch to the LFH. If the LFH cannot be activated, a debugger is likely present.

Key characteristics:

- Attempts to enable the LFH on `GetProcessHeap()` via `HeapSetInformation` with `HeapCompatibilityInformation`, then reads the heap's actual compatibility mode back with `HeapQueryInformation`.
- The compatibility flag returned is `0` (standard heap), `1` (look-aside list) or `2` (LFH active); a value other than `2` indicates the debug heap blocked LFH activation.
- Uses only documented Windows heap APIs, so it works across Windows versions and both x86 and amd64, unlike the classic variant that reads the `FrontEndHeap` pointer at hardcoded `_HEAP` offsets.
- Bypassable by *attaching* a debugger to an already-running process, since the debug heap is only selected at process creation.

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

- [Check Point Anti-Debug Research](https://anti-debug.checkpoint.com/)
- [Souhail Hammou - LFH Anti-Debugging trick](http://rce4fun.blogspot.com/)
- [Microsoft - HeapQueryInformation](https://learn.microsoft.com/en-us/windows/win32/api/heapapi/nf-heapapi-heapqueryinformation)
