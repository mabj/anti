# Context

This technique detects debuggers and sandboxes by verifying if the current process was launched by Explorer.exe, which is the expected parent process for normally executed programs. It compares the parent process ID against Explorer's PID to identify abnormal execution environments.

Key aspects:
- Uses `GetShellWindow()` to obtain Explorer.exe's window handle
- Retrieves Explorer's process ID via `GetWindowThreadProcessId()`
- Gets current process' parent PID using `NtQueryInformationProcess()` with ProcessBasicInformation class
- Compares parent PID against Explorer's PID
- Returns detection if parent PID doesn't match Explorer's PID
- Effective because debuggers typically create different parent-child process relationships
- Can detect automated sandbox execution where Explorer is not the parent

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

- [Check Point: Parent Process Check](https://anti-debug.checkpoint.com/techniques/misc.html#parent-process-check-ntqueryinformationprocess)
- [Microsoft: GetShellWindow function](https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getshellwindow)
- [Microsoft: GetWindowThreadProcessId function](https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowthreadprocessid)
