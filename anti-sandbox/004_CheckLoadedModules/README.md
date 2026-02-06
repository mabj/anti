# Context

This technique detects sandbox environments by checking for specific blacklisted DLL modules that are commonly associated with debugging tools or analysis environments. It uses Windows Toolhelp32 API to scan all running processes and their loaded modules.

Key characteristics:

- Maintains a predefined blacklist of suspicious module names (e.g., `SbieDll.dll` for Sandboxie, `wpespy.dll` for WPE Pro)
- Iterates through all running processes using process snapshots
- For each process, scans all loaded modules/DLLs
- Flags detection if any blacklisted module is found loaded in any process
- Based on techniques observed in Trik/Phorpiex malware families

## Build (Docker)

```[text]
make build-image
make build
```

## References

- <https://docs.microsoft.com/en-us/windows/win32/toolhelp/taking-a-snapshot-and-viewing-processes>
