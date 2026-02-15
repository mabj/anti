# Context

This technique uses the POPFD instruction with the Trap Flag (TF) set to detect debugger presence through single-step exception handling behavior. The code dynamically generates shellcode that sets the Trap Flag in the EFLAGS register, which triggers a single-step exception after the next instruction executes.

Key aspects:
- Dynamically generates shellcode that manipulates the EFLAGS register
- Uses PUSHFD to save flags, modifies the Trap Flag bit (0x100), then uses POPFD to restore
- Sets the Trap Flag (bit 8, value 0x100) in the EFLAGS register on the stack
- When POPFD restores EFLAGS with TF set, a single-step exception occurs after next instruction
- Debuggers typically intercept single-step exceptions internally for step-by-step execution
- Registers a vectored exception handler to catch the single-step exception
- If no debugger is attached, the VEH catches the single-step event
- If debugger is present, it intercepts the exception and VEH never receives it
- Uses dynamically allocated and executed shellcode for evasion
- More sophisticated than simple breakpoint-based techniques

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

- [Check Point: POPFD Trap Flag Technique](https://anti-debug.checkpoint.com/techniques/assembly.html#popf-and-trap-flag)
- [Intel: EFLAGS Register](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)
