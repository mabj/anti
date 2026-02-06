# Context

This technique detects debuggers attempting to step over function calls by checking for breakpoints (INT3/0xCC) at the function's return address.

Key characteristics:

- Uses `_ReturnAddress` intrinsic to get the return pointer
- Checks first byte at return address for 0xCC (breakpoint)
- Immediately returns if breakpoint detected
- Includes dummy code path to camouflage real behavior
- Effective against step-over debugging in OllyDbg/x64dbg

## Build

1. Make sure Visual Studio is installed (`vc.exe` is required because of `_ReturnAddress`)
2. update the variable `$vcVarsPath` of the `build.ps1`with the path to VC
3. Run `make` using powershell

## References

- <https://anti-debug.checkpoint.com/techniques/process-memory.html#anti-step-over>
