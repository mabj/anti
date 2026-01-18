# Context

This technique checks if the current process is attached to a debugger by calling IsDebuggerPresent API from Kernel32. 

IsDebuggerPresent checks the BeingDebugged flag in the Process Execution Block (PEB).

## References

- https://learn.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-isdebuggerpresent