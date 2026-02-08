# Context

This technique detects debuggers using timing analysis. It measures the elapsed time of a known workload using `GetTickCount()`, which returns the number of milliseconds since system startup. When a debugger is attached and the analyst is stepping through code or hitting breakpoints, the elapsed time will be significantly longer than normal execution, revealing the debugger's presence. Compared to `GetLocalTime()`/`GetSystemTime()`, `GetTickCount()` provides a simpler API that returns a single `DWORD` value, avoiding the need for `SYSTEMTIME`-to-`FILETIME` conversions.

Key characteristics:

- Captures millisecond timestamps before and after a loop using `GetTickCount()`
- Directly computes elapsed time by subtracting the two `DWORD` values
- Compares elapsed time against a predefined threshold (in milliseconds)
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

- [Microsoft: GetTickCount](https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-gettickcount)
- [Check Point: GetTickCount](https://anti-debug.checkpoint.com/techniques/timing.html#gettickcount)
