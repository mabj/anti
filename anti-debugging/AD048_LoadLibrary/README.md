# Context

Detects debuggers by exploiting file handle behavior differences when attempting to load an executable as a library. The technique calls LoadLibraryA on an executable file (calc.exe), then attempts exclusive file access with CreateFileA. Under normal execution, the file can be opened, but debuggers may lock the file handle differently, causing the exclusive open to fail with INVALID_HANDLE_VALUE.

Key characteristics:

- Uses LoadLibraryA to attempt loading an executable file as a DLL
- Follows with CreateFileA using exclusive access (no sharing flags)
- Detects debugger by checking if CreateFileA returns INVALID_HANDLE_VALUE
- Works because debuggers may hold file handles differently than normal execution
- Targets file handle behavior inconsistencies in debugging environments

> This technique does NOT work on WinDBG and x64dbg (our testing setup).

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

- [CheckPoint LoadLibrary](https://anti-debug.checkpoint.com/techniques/object-handles.html#loadlibrary)
- [Microsoft LoadLibraryA](https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibrarya)
