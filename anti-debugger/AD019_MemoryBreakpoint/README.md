# Context

This technique uses guard page exceptions to detect debugger presence. It works by:

- Allocating executable memory and writing a `RET` instruction (`0xC3`)
- Marking the page as a guard page using `VirtualProtect()`
- Attempting to execute the `RET` in a protected `__try` block
- Checking if a `STATUS_GUARD_PAGE_VIOLATION` exception occurs:
  - Exception caught: No debugger present
  - Exception not caught: Debugger present (likely suppressing the exception)

> Note: This technique works on OllyDbg/ImmunityDBG but not x64dbg

## Build

1. Make sure Visual Studio is installed (`vc.exe` is required because of `__try` and `__except`)
2. update the variable `$vcVarsPath` of the `build.ps1`with the path to VC
3. Run `make` using powershell

## References

- <https://anti-debug.checkpoint.com/techniques/process-memory.html#memory-breakpoints>
- <https://github.com/ayoubfaouzi/al-khaser/blob/master/al-khaser/AntiDebug/MemoryBreakpoints_PageGuard.cpp>
