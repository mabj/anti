# Context

Detects debuggers by comparing the first bytes of `IsDebuggerPresent` in the current process against its copy in every other accessible process. The technique resolves the address of `IsDebuggerPresent` via `GetProcAddress`, enumerates all running processes with `CreateToolhelp32Snapshot`, and uses `ReadProcessMemory` to read the function prologue from each one. If any process has different bytes at that address, it indicates a debugger has patched or hooked the API.

Key characteristics:

- Uses `GetModuleHandleA` + `GetProcAddress` to locate `IsDebuggerPresent` in kernel32.dll
- Enumerates all processes via `CreateToolhelp32Snapshot` and `Process32FirstW`/`Process32NextW`
- Opens each process with `PROCESS_ALL_ACCESS` and reads the function bytes with `ReadProcessMemory`
- Compares the first `DWORD` of the remote function against the local copy to detect patches
- Detects API hooking or inline patching applied by debuggers to intercept `IsDebuggerPresent`
- Requires sufficient privileges to open and read memory from other processes

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

- [CheckPoint Anti-Debug: Detecting Function Patches](https://anti-debug.checkpoint.com/techniques/assembly.html)
- [Microsoft ReadProcessMemory](https://learn.microsoft.com/en-us/windows/win32/api/memoryapi/nf-memoryapi-readprocessmemory)
- [Microsoft GetProcAddress](https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-getprocaddress)
