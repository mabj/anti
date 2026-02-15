# Context

This technique directly checks the BeingDebugged flag in the Process Environment Block (PEB) to detect if a debugger is attached. The PEB is a data structure maintained by Windows that contains process-specific information, including debugging status. This method bypasses API calls by reading the flag directly from memory.

Key aspects:

- Accesses the PEB structure directly to read the BeingDebugged flag
- The BeingDebugged flag is located at offset 0x02 in the PEB structure
- Uses inline assembly or intrinsics to access FS/GS segment registers
- FS:[0x30] (x86) or GS:[0x60] (x64) points to the PEB
- Returns 1 if debugger is attached, 0 if not
- Harder to hook than API-based checks but can still be bypassed
- Requires manual memory access rather than API calls

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

- [Microsoft: PEB Structure](https://learn.microsoft.com/en-us/windows/win32/api/winternl/ns-winternl-peb)
- [Check Point: PEB BeingDebugged Flag](https://anti-debug.checkpoint.com/techniques/debug-flags.html#manual-checks-beingdebugged)
