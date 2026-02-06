# Context

This technique uses a vectored exception handler to detect debuggers by triggering an INT3 breakpoint using the two-byte form (0xCD 0x03). The technique relies on the fact that debuggers typically catch breakpoint exceptions before the program's own handlers can process them.

Key aspects:
- Registers a custom vectored exception handler (VEH) to intercept `EXCEPTION_BREAKPOINT`
- Allocates executable memory containing the two-byte INT3 instruction (`0xCD 0x03`)
- Writes shellcode with INT3 followed by RET instruction
- Executes the shellcode to trigger a breakpoint exception
- If debugger is attached, it catches the exception first and `SwallowedException` remains true
- If no debugger is present, the VEH processes the exception and sets `SwallowedException` to false
- Uses the two-byte INT3 (`0xCD 0x03`) instead of one-byte `0xCC` to evade simple scanners
- More sophisticated than basic INT3 detection

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

- [Check Point: INT3 Instruction](https://anti-debug.checkpoint.com/techniques/assembly.html#int3)
- [al-khaser: Interrupt_3 Implementation](https://github.com/ayoubfaouzi/al-khaser/blob/master/al-khaser/AntiDebug/Interrupt_3.cpp)
