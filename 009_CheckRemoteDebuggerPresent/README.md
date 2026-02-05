# Context

This technique checks if the current process is attached to a debugger by calling CheckRemoteDebuggerPresent API from Kernel32.

CheckRemoteDebuggerPresent uses NtQueryInformationProcess to collect information about ProcessDebugPort (0x7). If debugger is present this API returns -1 (0xffffff).

## References

- <https://learn.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-checkremotedebuggerpresent>