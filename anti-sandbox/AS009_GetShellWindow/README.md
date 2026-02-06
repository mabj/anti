# Context

This anti-debug technique checks if the current process was launched by Explorer.exe by comparing parent process IDs. It works because:

- Debuggers typically create new parent-child process relationships
- Uses `GetShellWindow()` to get Explorer's window handle
- Retrieves Explorer's PID via `GetWindowThreadProcessId()`
- Compares against current process' parent PID from `NtQueryInformationProcess()`
- Returns true if parent PID doesn't match Explorer's PID

## References

- <https://anti-debug.checkpoint.com/techniques/misc.html#parent-process-check-ntqueryinformationprocess>
