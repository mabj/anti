# Context

This technique detects debuggers using timing analysis. It measures the elapsed time of a known workload using `timeGetTime()`, a multimedia timer function that returns the system time in milliseconds. When a debugger is attached and the analyst is stepping through code or hitting breakpoints, the elapsed time will be significantly longer than normal execution, revealing the debugger's presence. Unlike `GetTickCount()`, `timeGetTime()` comes from the Windows multimedia API (`winmm.dll`) and can offer higher precision when used with `timeBeginPeriod()`.

Key characteristics:

- Captures millisecond timestamps before and after a loop using `timeGetTime()`
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

- [Microsoft: timeGetTime](https://learn.microsoft.com/en-us/windows/win32/api/timeapi/nf-timeapi-timegettime)
- [Check Point: timeGetTime](https://anti-debug.checkpoint.com/techniques/timing.html#timegettime)
