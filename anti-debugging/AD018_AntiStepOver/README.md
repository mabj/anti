# Context

This technique detects debuggers attempting to step over function calls by checking for breakpoints (INT3/0xCC) at the function's return address. When debuggers use step-over, they temporarily set a breakpoint at the return address, which this technique can detect.

Key aspects:
- Uses `__builtin_return_address(0)` to get the return pointer from the stack
- Checks the first byte at the return address for 0xCC (INT3 breakpoint)
- Immediately returns or takes evasive action if breakpoint is detected
- Includes dummy code paths to camouflage the real detection logic
- Effective against step-over debugging in OllyDbg, x64dbg, and IDA Pro
- Exploits the temporary breakpoint mechanism used by debuggers for step-over
- Uses GCC `__builtin_return_address` intrinsic (MinGW compatible)

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

- [Check Point: Anti-Step-Over Technique](https://anti-debug.checkpoint.com/techniques/process-memory.html#anti-step-over)
- [Microsoft: _ReturnAddress intrinsic](https://learn.microsoft.com/en-us/cpp/intrinsics/returnaddress)
