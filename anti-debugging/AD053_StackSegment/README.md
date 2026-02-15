# Context

Detects single-stepping debuggers by exploiting the x86/x64 Stack Segment register trap inhibit behavior. When the SS register is reloaded (via `push ss; pop ss` on x86 or `mov ss, ax` on x64), the CPU suppresses single-step exceptions for the immediately following instruction. After this inhibited window, the code pushes RFLAGS/EFLAGS and checks the Trap Flag (TF, bit 8). If a debugger is single-stepping the process, TF remains set in the saved flags, revealing the debugger's presence.

Key characteristics:

- Exploits the documented Intel/AMD "MOV SS / POP SS" trap inhibit behavior that delays debug exceptions by one instruction
- Works on both x86 (`push ss; pop ss; pushf`) and x64 (`mov ss, ax; pushfq`) with architecture-specific inline assembly
- Checks bit 8 (Trap Flag) of the pushed EFLAGS/RFLAGS to determine if single-stepping is active
- Effective against user-mode debuggers that rely on the TF for step-over/step-into operations (x64dbg, OllyDbg, WinDbg)
- Lightweight detection with no Windows API calls required — purely CPU instruction-level

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

- [Check Point Anti-Debug: Stack Segment Register](https://anti-debug.checkpoint.com/techniques/assembly.html#stack-segment-register)
- [Intel SDM Vol. 3A, Section 6.8.3 — Masking Exceptions and Interrupts When Switching Stacks](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)
- [Peter Ferrie, "The Ultimate Anti-Debugging Reference"](https://pferrie.epizy.com/papers/antidebug.pdf)
