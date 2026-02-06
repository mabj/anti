# Context

This technique uses the Windows API GetWriteWatch to monitor memory pages for write operations, allowing detection of debugger breakpoints. When a software breakpoint (INT3 instruction) is set by a debugger, it triggers a write operation that can be detected by monitoring the write-watch state.

Key aspects:
- Allocates memory with the `MEM_WRITE_WATCH` flag to enable write monitoring
- Uses a watchdog thread to continuously monitor the buffer for write operations
- Calls `GetWriteWatch()` to check which pages have been written to
- Resets monitoring state with `ResetWriteWatch()` after each check
- Detects single write operations that indicate breakpoint insertion
- Can detect INT3 (0xCC) instructions written by debuggers
- Prints alert when memory tampering is detected
- Effective against software breakpoints

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

- [Check Point: GetWriteWatch Anti-Debug](https://anti-debug.checkpoint.com/techniques/misc.html#getwritewatch)
- [Microsoft: GetWriteWatch function](https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-getwritewatch)
- [Code in Security: Anti-Debug with VirtualAlloc's Write Watch](https://codeinsecurity.wordpress.com/2018/01/24/anti-debug-with-virtualallocs-write-watch/)
- [al-khaser: WriteWatch Implementation](https://github.com/gsuberland/al-khaser/blob/write-watch/al-khaser/Anti%20Debug/WriteWatch.cpp)
