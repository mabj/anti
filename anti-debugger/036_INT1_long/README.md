# Context

This anti-debug technique uses the **INT 1** instruction (also known as **ICEBP** - Ice Breakpoint) to detect debuggers by exploiting differences in exception handling behavior.

The technique works by:

- Allocating executable memory and writing shellcode containing the [`INT 1`](036_INT1_long/src/main.c:30) instruction (`0xCD 0x01`)
- Setting up a [`Vectored Exception Handler (VEH)`](036_INT1_long/src/main.c:23) to catch [`EXCEPTION_BREAKPOINT`](036_INT1_long/src/main.c:9) exceptions
- Executing the shellcode which triggers an INT 1 exception
- The VEH handler catches the exception, increments the instruction pointer (EIP/RIP), and continues execution
- When a debugger is present, it typically intercepts the INT 1 exception before the VEH can handle it
- By checking whether the VEH successfully handled the exception (via the [`SwallowedException`](036_INT1_long/src/main.c:5) flag), the code determines if a debugger is attached

**Key aspects:**

- INT 1 is a privileged single-byte instruction that causes a debug exception
- Debuggers handle INT 1 differently than normal exception handlers, often swallowing the exception
- The "long" variant uses dynamically generated shellcode rather than inline assembly
- The technique is effective because debuggers prioritize catching debug exceptions

## References

- <https://anti-debug.checkpoint.com/techniques/assembly.html#ice>
