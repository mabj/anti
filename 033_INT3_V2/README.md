# Context

This anti-debug technique uses a vectored exception handler to detect debuggers by triggering an INT3 breakpoint. The technique relies on the fact that debuggers will typically catch breakpoint exceptions before the program's own handlers can process them.

Key points:

- Uses a custom vectored exception handler (`VectoredHandler`) to intercept `EXCEPTION_BREAKPOINT`
- Allocates executable memory containing an `INT3` instruction (`\xCD\x03`) followed by a `RET`
- Executes the shellcode to trigger a breakpoint exception
- If a debugger is attached, it catches the exception first and the handler's `SwallowedException` flag remains `true`
- If no debugger is present, the program's handler processes the exception and sets `SwallowedException` to `false`
- The technique uses the two-byte `INT3` instruction (`0xCD 0x03`) instead of the more common one-byte `0xCC` to avoid simple breakpoint scanners

## References

- https://github.com/ayoubfaouzi/al-khaser/blob/master/al-khaser/AntiDebug/Interrupt_3.cpp
- https://anti-debug.checkpoint.com/techniques/assembly.html#int3