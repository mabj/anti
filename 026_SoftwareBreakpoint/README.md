# Context

This technique implements a memory breakpoint detection mechanism by:
- Periodically scanning function bytecode for the `0xCC` pattern (INT3 breakpoint instruction)
- Using a dedicated watchdog thread to monitor specific functions
- Scanning until `RET` instruction (`0xC3`) or known function size
- Printing warnings when breakpoints are detected in monitored functions

The implementation creates a persistent background check that can detect software breakpoints inserted by debuggers in critical functions.

![Tool Output](doc/images/software_breakpoint_watchdog_001.png)

## References

- https://anti-debug.checkpoint.com/techniques/process-memory.html#software-breakpoints