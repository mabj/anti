# Context

This technique detects debuggers by exploiting the behavior of the `SwitchToThread` API function when single-stepping through code. The function yields execution to another thread of equal or higher priority. Under normal conditions, `SwitchToThread` returns non-zero if another thread was scheduled. However, when single-stepping in a debugger, the scheduler behavior changes, causing the function to return zero more frequently. The technique performs eight iterations with short sleep delays, left-shifting a counter based on the return value. If all iterations return zero (counter becomes 0), a debugger is detected.

Key characteristics:

- Exploits thread scheduling behavior differences during single-step debugging
- Uses `SwitchToThread()` combined with `Sleep(0x0F)` to create timing-sensitive conditions
- Performs 8 iterations with bit-shifting counter mechanism to detect anomalies
- Returns zero when debugger manipulates thread scheduling via single-stepping
- Minimal API footprint (only kernel32.dll functions)
- Timing-based detection that is difficult to bypass without patching or emulation

> This technique did not work reliably with x32dbg and windbg under Windows 10 64 bits.

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

- [Check Point: SwitchToThread](https://anti-debug.checkpoint.com/techniques/interactive.html#switchtothread-ntyieldexecution)
- [Microsoft: SwitchToThread function](https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-switchtothread)
