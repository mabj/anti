# Context

This technique attempts to evade sandbox analysis by using `NtDelayExecution` to introduce a long execution delay (10 seconds). Many automated sandboxes have limited analysis time windows (typically 30-60 seconds) and may skip or fast-forward sleep operations to maximize analysis coverage. By calling the native `NtDelayExecution` API directly instead of higher-level functions like `Sleep()` or `SleepEx()`, malware can potentially bypass some sandbox sleep acceleration hooks. The technique dynamically resolves `NtDelayExecution` from ntdll.dll and requests a 10-second delay. If the delay executes successfully, the sandbox may timeout before completing analysis of subsequent malicious behavior.

Key characteristics:

- Uses native `NtDelayExecution` API from ntdll.dll instead of kernel32 Sleep functions
- Introduces a 10-second delay to exhaust sandbox analysis time windows
- Dynamically resolves the function via `GetProcAddress` to avoid import table detection
- Converts milliseconds to 100-nanosecond intervals (Windows FILETIME format)
- Returns success if delay completes, indicating potential sandbox timeout
- Lower-level API may bypass some sandbox sleep acceleration hooks

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

- [Microsoft: NtDelayExecution function](https://learn.microsoft.com/en-us/windows/win32/api/winternl/nf-winternl-ntdelayexecution)
- [Undocumented NT Internals: NtDelayExecution](http://undocumented.ntinternals.net/index.html?page=UserMode%2FUndocumented%20Functions%2FNT%20Objects%2FThread%2FNtDelayExecution.html)
- [Al-Khaser: Timing-based evasion techniques](https://github.com/LordNoteworthy/al-khaser)
