# Context

This technique exploits the ICEBP (In-Circuit Emulator Breakpoint) instruction to detect the presence of a debugger. ICEBP is a single-byte instruction (opcode 0xF1) that generates a breakpoint exception, similar to INT3 but with different behavior under debugging.

Key aspects:
- Dynamically allocates executable memory and writes shellcode containing ICEBP instruction (0xF1)
- Includes a RET instruction (0xC3) after ICEBP to return execution
- Registers a Vectored Exception Handler (VEH) to catch `EXCEPTION_BREAKPOINT` exceptions
- When executed normally (no debugger), ICEBP triggers an exception caught by the VEH
- VEH increments the instruction pointer and sets `SwallowedException` to false
- If debugger is present, it intercepts the ICEBP exception before the VEH can handle it
- If `SwallowedException` remains true after execution, debugger is detected
- ICEBP (INT 1) was originally used for in-circuit emulation debugging
- Single-byte privileged instruction unlike standard INT3 (0xCC)
- Dynamic shellcode generation avoids static analysis detection

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

- [Check Point: ICEBP (INT 1) Instruction](https://anti-debug.checkpoint.com/techniques/assembly.html#ice)
- [Intel: Debug Exceptions](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)
