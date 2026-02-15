# Context

This technique exploits the Windows limitation that only one debugger can be attached to a process at a time. The program spawns a child instance of itself and attempts to attach it as a debugger to the parent process. If the attachment succeeds, no external debugger is present. If it fails, another debugger is already attached.

Key aspects:
- Creates a child process of itself, passing the parent's PID as a command-line argument
- Child process attempts to attach as a debugger using `DebugActiveProcess()`
- Enables `SE_DEBUG_NAME` privilege to allow debugging operations
- Uses a Windows named event object ("SelfDebugging") for synchronization between parent and child
- If `DebugActiveProcess()` succeeds, no external debugger is attached
- If attachment fails, signals that an external debugger is already present
- Immediately detaches with `DebugActiveProcessStop()` if successful
- Exploits the Windows restriction that prevents multiple debuggers from attaching simultaneously
- More sophisticated than flag-based detection methods
- Cannot be easily bypassed by PEB manipulation

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

- [Check Point: Self-Debugging Technique](https://anti-debug.checkpoint.com/techniques/process.html#debugactiveprocess)
- [Microsoft: DebugActiveProcess function](https://learn.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-debugactiveprocess)
- [Microsoft: DebugActiveProcessStop function](https://learn.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-debugactiveprocessstop)
