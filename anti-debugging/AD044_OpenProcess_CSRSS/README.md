# Context

This anti-debugging technique detects debuggers by attempting to open the protected csrss.exe (Client/Server Runtime Subsystem) process, which normally fails due to security restrictions.

Key aspects:

- Uses `CsrGetProcessId()` from ntdll.dll to retrieve the PID of csrss.exe
- Attempts to open csrss.exe using `OpenProcess()` with `PROCESS_QUERY_LIMITED_INFORMATION` flag
- Normal processes cannot open csrss.exe due to system-level protection
- Debuggers often run with elevated privileges that bypass these protections
- If `OpenProcess()` succeeds, it indicates a debugger with elevated privileges is present
- Returns the handle and detects debugger if csrss.exe can be accessed
- Effective against debuggers running with administrator or system privileges
- Simple technique that exploits privilege level differences between normal and debug contexts

> PS: this technique seems to not work with my setup using x64dbg or WinDBG and Windows 11.

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

- [Microsoft: NtQueryInformationProcess function](https://learn.microsoft.com/en-us/windows/win32/api/winternl/nf-winternl-ntqueryinformationprocess)
- [Check Point: ProcessDebugPort](https://anti-debug.checkpoint.com/techniques/debug-flags.html#manual-checks-processdebugport)
