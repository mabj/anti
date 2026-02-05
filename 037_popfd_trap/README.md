# Context

This anti-debug technique uses the POPFD instruction with the Trap Flag (TF) set to detect debugger presence through single-step exception handling behavior. The code dynamically generates shellcode that sets the Trap Flag in the EFLAGS register and then restores it with POPFD, which triggers a single-step exception after the next instruction executes.

**Key aspects:**

- Sets the Trap Flag (bit 8, value 0x100) in the EFLAGS register by manipulating it on the stack
- Uses PUSHFD to save flags, modifies the Trap Flag bit, then uses POPFD to restore the modified flags
- When POPFD restores EFLAGS with TF set, a single-step exception occurs after the next instruction
- Debuggers typically intercept single-step exceptions internally without passing them to the program's exception handlers
- The technique detects debugger presence by checking if the vectored exception handler receives the single-step exception
- Uses dynamically allocated and executed shellcode rather than inline assembly for evasion
- If no debugger is attached, the program's vectored exception handler catches the single-step event

## References

- <https://anti-debug.checkpoint.com/techniques/assembly.html#ice>
