# Context

This anti-debugging technique exploits the behavior of `GenerateConsoleCtrlEvent()` when a debugger intercepts control signals.

Key aspects:

- Uses `GenerateConsoleCtrlEvent(CTRL_C_EVENT, 0)` to trigger a console control event
- Registers a Vectored Exception Handler (VEH) to catch `DBG_CONTROL_C` exceptions
- Registers a Console Control Handler to process CTRL_C_EVENT normally
- When debugged: the VEH receives `DBG_CONTROL_C` and sets the debugger detection flag
- When not debugged: only the console handler is invoked, flag remains unset
- Waits with random sleep intervals (500ms-1.5s) to allow handlers to execute
- Detects debuggers by checking if the VEH was triggered
- Effective against user-mode and some kernel-mode debuggers

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

- [Microsoft: GenerateConsoleCtrlEvent function](https://learn.microsoft.com/en-us/windows/console/generateconsolectrlevent)
- [Microsoft: SetConsoleCtrlHandler function](https://learn.microsoft.com/en-us/windows/console/setconsolectrlhandler)
- [Checkpoint: anti-debug](https://anti-debug.checkpoint.com/techniques/interactive.html#generateconsolectrlevent)
