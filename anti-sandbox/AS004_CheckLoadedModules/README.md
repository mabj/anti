# Context

This technique detects sandbox environments by checking for specific blacklisted DLL modules that are commonly associated with debugging tools or analysis environments. It uses Windows Toolhelp32 API to scan all running processes and their loaded modules. Based on techniques observed in Trik/Phorpiex malware families.

Key aspects:
- Maintains a predefined blacklist of suspicious module names (e.g., `SbieDll.dll` for Sandboxie, `wpespy.dll` for WPE Pro)
- Iterates through all running processes using process snapshots
- For each process, scans all loaded modules/DLLs using `Module32First` and `Module32Next`
- Flags detection if any blacklisted module is found loaded in any process
- More comprehensive than simple process name checking

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

- [Microsoft: Taking a Snapshot and Viewing Processes](https://learn.microsoft.com/en-us/windows/win32/toolhelp/taking-a-snapshot-and-viewing-processes)
- [Microsoft: Module32First function](https://learn.microsoft.com/en-us/windows/win32/api/tlhelp32/nf-tlhelp32-module32first)
