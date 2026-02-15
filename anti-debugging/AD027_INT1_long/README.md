# Context

This technique uses the two-byte INT 1 instruction (0xCD 0x01) to detect debuggers by exploiting differences in exception handling behavior. Unlike the single-byte ICEBP (0xF1), this uses the long form of the INT 1 instruction for potentially better compatibility.

Key aspects:
- Allocates executable memory and writes shellcode containing the two-byte INT 1 instruction (0xCD 0x01)
- Sets up a Vectored Exception Handler (VEH) to catch `EXCEPTION_BREAKPOINT` exceptions
- Executes the shellcode which triggers an INT 1 exception
- VEH catches the exception, increments the instruction pointer (EIP/RIP), and continues execution
- When a debugger is present, it typically intercepts INT 1 before the VEH can handle it
- By checking the `SwallowedException` flag, determines if debugger intercepted the exception
- INT 1 is a privileged instruction that causes a debug exception
- The "long" variant uses the two-byte form (0xCD 0x01) rather than single-byte ICEBP (0xF1)
- Dynamically generated shellcode avoids static detection

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

- [Check Point: INT 1 Instruction](https://anti-debug.checkpoint.com/techniques/assembly.html#int-1)
- [Intel: Debug Exceptions](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)
