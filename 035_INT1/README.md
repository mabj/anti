# Context

This anti-debug technique exploits the ICEBP (In-Circuit Emulator Breakpoint) instruction to detect the presence of a debugger. ICEBP is a single-byte instruction (opcode `0xF1`) that generates a breakpoint exception, similar to INT3 but with different behavior under debugging.

## How It Works

- The technique dynamically allocates executable memory and writes shellcode containing the ICEBP instruction (`0xF1`) followed by a return (`0xC3`)
- A Vectored Exception Handler (VEH) is registered to catch [`EXCEPTION_BREAKPOINT`](src/main.c:9) exceptions
- When the shellcode executes normally (no debugger), ICEBP triggers an exception that the VEH catches
- The VEH increments the instruction pointer and sets [`SwallowedException`](src/main.c:8) to FALSE, indicating normal execution
- If a debugger is present, it typically intercepts the ICEBP exception before the VEH can handle it
- If [`SwallowedException`](src/main.c:24) remains TRUE after execution, it indicates the VEH never ran, meaning a debugger intercepted the exception

## Key Points

- **ICEBP instruction**: Opcode `0xF1`, also known as INT 1, originally used for in-circuit emulation debugging
- **Single-byte breakpoint**: Unlike the standard INT3 (`0xCC`), ICEBP is a privileged single-byte instruction
- **Debugger interception**: Most debuggers handle ICEBP specially and intercept it before application exception handlers
- **VEH-based detection**: Uses Vectored Exception Handling to determine if the exception reached the application or was swallowed by the debugger
- **Dynamic shellcode**: Generates the instruction at runtime to avoid static analysis detection

## References

- <https://anti-debug.checkpoint.com/techniques/assembly.html#ice>
