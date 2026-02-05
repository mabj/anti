# Context

This anti-debug technique exploits the behavior of the `INT 2D` (0x2D) interrupt instruction, which is handled differently by debuggers versus normal exception handlers.

## How it works

- **Vectored Exception Handler (VEH)**: The code registers a VEH to catch breakpoint exceptions (`EXCEPTION_BREAKPOINT`)
- **Shellcode Generation**: Dynamically allocates executable memory and writes shellcode containing:
  - `XOR RAX, RAX` (or `XOR EAX, EAX` on x86) - zeroes the register
  - `INT 0x2D` - the key anti-debug instruction
  - `NOP` and `RET` - padding and return
- **Execution & Detection**: When the shellcode executes:
  - **Without debugger**: `INT 2D` generates an exception that gets caught by the VEH, which increments the instruction pointer and sets `SwallowedException = FALSE`
  - **With debugger**: Most debuggers intercept and swallow the `INT 2D` exception without passing it to the application's exception handlers, so `SwallowedException` remains `TRUE`
- **Result**: If `SwallowedException` is still `true` after execution, a debugger is detected

## Key Points

- The `INT 2D` instruction is specifically designed to trigger kernel-mode debugging features
- Debuggers typically handle this interrupt internally to prevent breaking execution flow
- By registering a custom exception handler, the application can detect when the exception was swallowed by a debugger
- The technique requires both VEH setup and dynamic shellcode execution to avoid static detection

## References

- <https://github.com/ayoubfaouzi/al-khaser/blob/master/al-khaser/AntiDebug/Interrupt_3.cpp>
- <https://anti-debug.checkpoint.com/techniques/assembly.html#int3>
