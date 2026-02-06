# [008] IsDebuggerPresent

[![Category: Anti-Debugger](https://img.shields.io/badge/Category-Anti--Debugger-red)]()
[![Platform: Windows](https://img.shields.io/badge/Platform-Windows-blue)]()

## Overview

This technique checks if the current process is attached to a debugger by calling IsDebuggerPresent API from Kernel32.

## How It Works

The `IsDebuggerPresent` function is a Windows API that checks the `BeingDebugged` flag in the Process Environment Block (PEB). When a debugger attaches to a process, Windows automatically sets this flag to indicate debugging status.

## Technical Details

### API Calls Used
- `IsDebuggerPresent()` - Checks the BeingDebugged flag in the PEB structure

### Detection Method
1. Call `IsDebuggerPresent()` from kernel32.dll
2. Function returns TRUE (non-zero) if a debugger is present
3. Function returns FALSE (zero) if no debugger is attached

The function internally accesses:
```
PEB->BeingDebugged flag (offset 0x02 in PEB structure)
```

## Building

```bash
# Using Docker
make build-image
make build

# Or with MinGW
make
```

## Example Output

### Normal Execution (No Debugger)

> 📸 **Screenshot placeholder**: Add screenshot showing normal execution without debugger

Expected output:
```
[*] Anti-Analysis Technique: IsDebuggerPresent
[+] No debugger detected
[+] Execution completed successfully
```

### Debugger Detected

> 📸 **Screenshot placeholder**: Add screenshot showing debugger detection

Expected output:
```
[*] Anti-Analysis Technique: IsDebuggerPresent
[!] Debugger detected!
[!] Terminating execution
```

### Visual Comparison

> 📸 **Screenshot placeholder**: Add side-by-side comparison of both scenarios

## Effectiveness

| Debugger/Tool | Detection Success | Notes |
|---------------|-------------------|-------|
| x64dbg | ✓ | Reliable detection |
| OllyDbg | ✓ | Works on all versions |
| WinDbg | ✓ | Detected in user-mode |
| IDA Pro | ✓ | Standard detection |

## Limitations

- **Easily bypassed**: This is one of the most well-known anti-debug techniques
- **Can be patched**: The PEB BeingDebugged flag can be manually set to 0
- **Debugger plugins**: Many debuggers have plugins to hide this flag automatically
- **Not kernel-mode safe**: Kernel debuggers may not trigger this check

## Bypasses

Common bypass methods:
1. Manually set `PEB->BeingDebugged` to 0
2. Use debugger plugins (ScyllaHide, HideDebugger)
3. Hook `IsDebuggerPresent` to always return FALSE

## References

- [Microsoft: IsDebuggerPresent function](https://learn.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-isdebuggerpresent)
- [Windows Internals: PEB Structure](https://learn.microsoft.com/en-us/windows/win32/api/winternl/ns-winternl-peb)

---

**Category**: Anti-Debugger
**Effectiveness**: Low (easily bypassed)
**Last Updated**: 2026-02-06
