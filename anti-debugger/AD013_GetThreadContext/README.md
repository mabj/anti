# Context

This technique detects debuggers by checking hardware breakpoint registers via the GetThreadContext API. Debuggers use CPU debug registers (DR0-DR7) to set hardware breakpoints. By reading these registers, the technique can detect if any hardware breakpoints are currently active.

Key aspects:
- Uses `GetThreadContext()` with `CONTEXT_DEBUG_REGISTERS` flag
- Retrieves the thread context containing debug register values
- Checks DR0, DR1, DR2, and DR3 registers (hardware breakpoint addresses)
- Checks DR6 (debug status register) and DR7 (debug control register)
- Non-zero values in any debug register indicate active hardware breakpoints
- Effective against hardware-based debugging techniques
- Can be bypassed by clearing debug registers before the check
- More reliable than software breakpoint detection

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

- [Microsoft: GetThreadContext function](https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-getthreadcontext)
- [Check Point: Hardware Breakpoints Detection](https://anti-debug.checkpoint.com/techniques/process-memory.html#hardware-breakpoints)
- [Intel: Debug Registers](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)
