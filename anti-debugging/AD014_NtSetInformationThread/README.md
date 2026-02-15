# Context

This technique uses the Windows Native API NtSetInformationThread with the ThreadHideFromDebugger information class to detach debuggers from the current thread. This causes the debugger to lose control of the thread without terminating the process, effectively breaking debugging sessions.

Key aspects:
- Calls `NtSetInformationThread()` with `ThreadHideFromDebugger` class (0x11)
- Detaches debuggers from the current thread without terminating execution
- Prevents debuggers from receiving thread events and exceptions
- Debuggers lose control and cannot continue stepping or breaking
- Typically combined with infinite loops to maintain execution after detachment
- Does not terminate the process, only hides it from debuggers
- Effective defensive technique against active debugging

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

- [Check Point: NtSetInformationThread](https://anti-debug.checkpoint.com/techniques/interactive.html#ntsetinformationthread)
- [Microsoft: NtSetInformationThread function](https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntsetinformationthread)
