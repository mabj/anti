# Context

This technique exploits the behavior of the INT 2D (0x2D) interrupt instruction, which is handled differently by debuggers versus normal exception handlers. The INT 2D instruction is specifically designed to trigger kernel-mode debugging features, and debuggers typically handle it internally without passing exceptions to the application.

Key aspects:
- Registers a Vectored Exception Handler (VEH) to catch breakpoint exceptions (`EXCEPTION_BREAKPOINT`)
- Dynamically allocates executable memory for shellcode generation
- Writes shellcode containing: XOR RAX/EAX (zeroes register), INT 0x2D, NOP, and RET
- Without debugger: INT 2D generates an exception caught by the VEH, which increments instruction pointer
- With debugger: Most debuggers intercept and swallow the INT 2D exception internally
- Detection logic: If `SwallowedException` remains true after execution, debugger is detected
- INT 2D is specifically designed for kernel-mode debugging features
- Technique requires both VEH setup and dynamic shellcode execution to avoid static detection

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

- [Check Point: INT 2D Instruction](https://anti-debug.checkpoint.com/techniques/assembly.html#int-2d)
- [al-khaser: Interrupt_3 Implementation](https://github.com/ayoubfaouzi/al-khaser/blob/master/al-khaser/AntiDebug/Interrupt_3.cpp)
