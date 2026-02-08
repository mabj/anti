# Context

This technique detects debuggers using timing analysis. It measures the elapsed wall-clock time of a known workload using `GetLocalTime()` and compares it against an expected threshold. When a debugger is attached and the analyst is stepping through code or hitting breakpoints, the elapsed time will be significantly longer than normal execution, revealing the debugger's presence.

Key characteristics:

- Captures timestamps before and after a loop using `GetLocalTime()`
- Converts to `FILETIME` via `SystemTimeToFileTime()` for precise comparison
- Compares elapsed time against a predefined threshold (in 100-nanosecond intervals)
- Debugger single-stepping or breakpoints inflate the measured time well beyond the threshold

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

- [Microsoft: GetLocalTime](https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getlocaltime)
- [Check Point: PEB GetLocalTime](https://anti-debug.checkpoint.com/techniques/timing.html#getlocaltime)
