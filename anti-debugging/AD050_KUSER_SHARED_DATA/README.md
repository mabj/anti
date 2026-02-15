# Context

Detects a kernel-mode debugger by reading the `KdDebuggerEnabled` byte directly from the `KUSER_SHARED_DATA` structure at the fixed user-mode address `0x7FFE02D4`. This memory-mapped page is shared between kernel and user mode and always resides at address `0x7FFE0000` on all Windows versions. The technique checks bit 0 (debugger fully enabled) and bit 1 (debugger not present but enabled at boot) of the `KdDebuggerEnabled` field.

Key characteristics:

- Reads a single byte from the fixed address `0x7FFE02D4` (no API calls required)
- Checks `KdDebuggerEnabled` bit flags: bit 0 = kernel debugger active, bit 1 = enabled at boot
- `KUSER_SHARED_DATA` is always mapped at `0x7FFE0000` in every user-mode process
- Extremely lightweight — a single memory dereference with no system calls or API imports
- Detects kernel-mode debuggers (WinDbg kernel mode, KD, etc.)
- Does not detect user-mode debuggers (x64dbg, OllyDbg)

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

- [Geoff Chappell - KUSER_SHARED_DATA](https://www.geoffchappell.com/studies/windows/km/ntoskrnl/inc/api/ntexapi_x/kuser_shared_data/index.htm)
- [CheckPoint Anti-Debug: KUSER_SHARED_DATA](https://anti-debug.checkpoint.com/techniques/debug-flags.html#kuser_shared_data)
- [Microsoft KUSER_SHARED_DATA structure](https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntddk/ns-ntddk-kuser_shared_data)
