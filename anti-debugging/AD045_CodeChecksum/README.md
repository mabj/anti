# Context

This anti-debugging technique uses continuous CRC32 checksum monitoring to detect code modifications from breakpoints or patches in protected functions.

Key aspects:
- Calculates CRC32 checksum of a protected function's code at startup
- Determines function size by scanning for return instruction (0xC3)
- Spawns a watchdog thread that continuously monitors the function's checksum
- Watchdog recalculates CRC32 every 300ms and compares with original value
- Detects software breakpoints (0xCC) that modify function bytes
- Terminates process immediately if tampering is detected
- Protected function runs in an infinite loop for demonstration
- Effective against debuggers that insert INT3 breakpoints in monitored code


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

- [Check Point: Code Checksums](https://anti-debug.checkpoint.com/techniques/process-memory.html#code-checksums)
- [The Ultimate Anti-Debugging Reference - Code Integrity Checks](https://pferrie.epizy.com/papers/antidebug.pdf)
