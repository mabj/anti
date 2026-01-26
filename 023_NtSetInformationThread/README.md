# Context

This anti-debug technique uses the Windows Native API `NtSetInformationThread` with the `ThreadHideFromDebugger` (0x11) information class to:

- Detach debuggers from the current thread by setting THREAD_INFORMATION_CLASS to 0x11 (ThreadHideFromDebugger)
- Prevent debuggers from receiving thread events and exceptions
- Cause debuggers to lose control of the thread without terminating the process
- Typically used in combination with infinite loops to maintain execution control

The code demonstrates this by:
1. Calling `NtSetInformationThread(GetCurrentThread(), 0x11, NULL, 0)`
2. Entering an infinite loop to keep the process running after debugger detachment

## References

- https://anti-debug.checkpoint.com/techniques/interactive.html#ntsetinformationthread
- https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntsetinformationthread