# Context

This technique hooks the `DbgUiRemoteBreakin` function in ntdll.dll to prevent debuggers from attaching to or controlling the process. When a debugger attempts to break in, the hooked function terminates the process immediately instead.

- **Implementation**:
  - Locates `DbgUiRemoteBreakin` in ntdll.dll
  - Constructs architecture-specific patch to call `TerminateProcess`
  - Temporarily changes memory protection to apply patch
  - Restores original memory protection after patching
- **Effect**: Prevents debuggers from gaining control by terminating the process upon break-in attempts

## Build (Docker)

```[bash]
make build-image
make build
```

## References

- <https://anti-debug.checkpoint.com/techniques/process-memory.html#patch_ntdll_dbgbreakpoint>
