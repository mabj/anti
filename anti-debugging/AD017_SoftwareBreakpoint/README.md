# Context

This technique implements a continuous memory breakpoint detection mechanism by scanning function bytecode for the 0xCC pattern (INT3 breakpoint instruction). It uses a dedicated watchdog thread to monitor critical functions for software breakpoints inserted by debuggers.

Key aspects:
- Periodically scans function bytecode for the `0xCC` pattern (INT3 instruction)
- Uses a dedicated watchdog thread to continuously monitor specific functions
- Scans until RET instruction (`0xC3`) or known function size is reached
- Prints warnings when software breakpoints are detected in monitored functions
- Can monitor multiple functions simultaneously
- Creates a persistent background check that runs throughout execution
- Effective against standard software breakpoints used by debuggers
- Can detect breakpoints set after the program starts

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

- [Check Point: Software Breakpoints Detection](https://anti-debug.checkpoint.com/techniques/process-memory.html#software-breakpoints)
- [Microsoft: Software Breakpoints](https://learn.microsoft.com/en-us/windows-hardware/drivers/debugger/x86-architecture)
