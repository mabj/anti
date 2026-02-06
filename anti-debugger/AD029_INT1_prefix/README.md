# Context

This technique leverages the ICEBP instruction (opcode 0xF1) prefixed with instruction prefixes to detect debugger presence. It dynamically generates shellcode containing a REP prefix (0xF3), FS segment prefix (0x64), followed by the ICEBP instruction, creating an unusual instruction sequence that debuggers handle differently than normal exception handlers.

Key aspects:
- Uses prefix obfuscation with REP (0xF3) and FS segment (0x64) prefixes before ICEBP
- Creates an unusual instruction sequence that is difficult to analyze statically
- Registers a Vectored Exception Handler (VEH) to catch `EXCEPTION_SINGLE_STEP` exceptions
- Builds the shellcode dynamically in allocated executable memory to evade static analysis
- When executed without debugger, VEH catches the exception and sets `SwallowedException` to false
- If debugger is present, it intercepts the prefixed ICEBP exception before VEH
- Detection mechanism: If `SwallowedException` remains true, debugger intercepted the exception
- ICEBP (0xF1) is a single-byte privileged instruction for in-circuit emulation debugging
- Prefix bytes make the instruction sequence more obscure and harder to detect
- Runtime generation prevents signature-based detection

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

- [Check Point: Instruction Prefixes](https://anti-debug.checkpoint.com/techniques/assembly.html#instruction_prefixes)
- [Intel: Instruction Prefixes](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)
