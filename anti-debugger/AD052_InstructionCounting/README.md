# Context

This technique detects a debugger by counting hardware breakpoint-triggered single-step exceptions. It creates a suspended thread containing a sequence of NOP instructions, sets hardware breakpoints (Dr0-Dr3) on each NOP, then resumes the thread. A Vectored Exception Handler increments a counter (EAX/RAX) for each EXCEPTION_SINGLE_STEP received. Without a debugger, all 4 exceptions fire and the counter reaches 4. A debugger that intercepts or consumes single-step exceptions causes the count to differ, revealing its presence.

Key characteristics:

- Sets hardware breakpoints on 4 consecutive NOP instructions using debug registers (Dr0-Dr3)
- Uses a Vectored Exception Handler (VEH) to count EXCEPTION_SINGLE_STEP exceptions
- Creates a dedicated thread with `__declspec(naked)` function containing the instrumented code
- Compares the final instruction count against the expected value (4) to detect debugger interference
- Debuggers that handle single-step exceptions (e.g., for stepping) will consume some exceptions, causing the count to mismatch
- Uses `SetHardwareBreakpoint` / `RemoveHardwareBreakpoint` helpers to manage debug registers via `SetThreadContext`

> This technique did NOT work on Windows 10 and x64dbg. The EXCEPTION_SINGLE_STEP exception from the Hardware Breakpoint is still raised when execute the sample without a debugger. :/

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

- [Check Point Anti-Debug: Instruction Counting](https://anti-debug.checkpoint.com/techniques/assembly.html#instruction-counting)
- [Microsoft Docs: Vectored Exception Handling](https://learn.microsoft.com/en-us/windows/win32/debug/vectored-exception-handling)
- [Microsoft Docs: SetThreadContext](https://learn.microsoft.com/en-us/windows/win32/api/processthreadsapi/nf-processthreadsapi-setthreadcontext)
