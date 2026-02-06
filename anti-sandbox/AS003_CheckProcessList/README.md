# Context

This technique detects sandbox and analysis environments by enumerating running processes and checking for known analysis tools. The method iterates through the system process list looking for blacklisted process names that indicate debugging or monitoring tools. Many malware families including Smokeloader implement this technique.

Key aspects:
- Uses Windows Toolhelp32 API to enumerate all running processes
- Maintains a blacklist of suspicious process names (plain text or hashed)
- Calls `CreateToolhelp32Snapshot` to capture system process state
- Uses `Process32First` and `Process32Next` to iterate through processes
- Compares each process name against the blacklist
- Can use plain text comparison or hash-based matching for obfuscation

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

- [Microsoft: CreateToolhelp32Snapshot function](https://learn.microsoft.com/en-us/windows/win32/api/tlhelp32/nf-tlhelp32-createtoolhelp32snapshot)
- [Microsoft: Process32First function](https://learn.microsoft.com/en-us/windows/win32/api/tlhelp32/nf-tlhelp32-process32first)
- [Microsoft: Process32Next function](https://learn.microsoft.com/en-us/windows/win32/api/tlhelp32/nf-tlhelp32-process32next)
