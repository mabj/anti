# Context

This technique checks if the current process is attached to a debugger by calling the IsDebuggerPresent API from kernel32.dll. The function checks the BeingDebugged flag in the Process Environment Block (PEB), which Windows automatically sets when a debugger attaches to the process.

Key aspects:
- Calls `IsDebuggerPresent()` from kernel32.dll
- Internally checks the BeingDebugged flag at PEB offset 0x02
- Returns TRUE (non-zero) if debugger is present
- Returns FALSE (zero) if no debugger is attached
- One of the most well-known but easily bypassed techniques
- Can be defeated by PEB flag manipulation or debugger plugins like ScyllaHide

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

- [Microsoft: IsDebuggerPresent function](https://learn.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-isdebuggerpresent)
- [Microsoft: PEB Structure](https://learn.microsoft.com/en-us/windows/win32/api/winternl/ns-winternl-peb)
