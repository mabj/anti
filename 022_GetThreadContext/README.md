# Context

This anti-debug technique detects debuggers by checking hardware breakpoint registers via the `GetThreadContext` API. Debuggers set hardware breakpoints using CPU debug registers (DR0-DR7). If any debug register contains non-zero values, it indicates active debugging.

Key points:
- Uses `GetThreadContext` with `CONTEXT_DEBUG_REGISTERS` flag
- Checks DR0, DR1, DR2, DR3, DR6, and DR7 registers
- Non-zero values in any register indicate debugger presence
- Effective against hardware-based debugging
- Can be bypassed by clearing debug registers before detection

## References

- https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-getthreadcontext
- https://anti-debug.checkpoint.com/techniques/process-memory.html#hardware-breakpoints