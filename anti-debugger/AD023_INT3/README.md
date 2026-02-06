# Context

This technique uses the INT3 breakpoint instruction to detect debuggers through exception handling behavior. When an INT3 (0xCC) instruction is executed, it generates a breakpoint exception. Debuggers handle this exception differently than normal exception handlers, allowing for detection.

Key aspects:
- Executes an INT3 (0xCC) breakpoint instruction
- Can be implemented inline or in dynamically allocated shellcode
- If a debugger is attached, it intercepts the breakpoint exception
- If no debugger is present, the program's exception handler catches it
- One of the most fundamental anti-debug techniques
- Can be enhanced with vectored exception handlers for more reliable detection
- Simple but effective for basic debugger detection

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