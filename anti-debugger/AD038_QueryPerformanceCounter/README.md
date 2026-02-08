# Context

This technique detects debuggers using high-resolution timing analysis. It measures the elapsed time of a known workload using `QueryPerformanceCounter()`, which provides the highest precision timer available on the system. When a debugger is attached and the analyst is stepping through code or hitting breakpoints, the elapsed time will be significantly longer than normal execution, revealing the debugger's presence. Compared to `GetTickCount()` or `GetLocalTime()`, `QueryPerformanceCounter()` offers sub-microsecond resolution via hardware performance counters, making it harder to spoof.

Key characteristics:

- Captures high-resolution timestamps before and after a loop using `QueryPerformanceCounter()`
- Directly computes elapsed time by subtracting `LARGE_INTEGER` quad-part values
- Compares elapsed time against a predefined threshold (in performance counter ticks)
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

- [Microsoft: QueryPerformanceCounter](https://learn.microsoft.com/en-us/windows/win32/api/profileapi/nf-profileapi-queryperformancecounter)
- [Check Point: QueryPerformanceCounter](https://anti-debug.checkpoint.com/techniques/timing.html#queryperformancecounter)
