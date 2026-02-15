# Context

This anti-debugging technique detects debuggers by attempting to open the current executable file with exclusive access, which fails when debuggers lock the file differently.

Key aspects:

- Uses `GetModuleFileNameA()` to retrieve the path of the current executable
- Attempts to open the executable with `CreateFileA()` using share mode 0 (exclusive access)
- Under normal execution, the OS locks the running executable, preventing exclusive access
- Returns `INVALID_HANDLE_VALUE` when open fails, indicating potential debugger presence
- Debuggers may handle file locking differently, causing the open to fail
- Detects debuggers that modify how the OS manages executable file handles
- Simple technique exploiting file system locking behavior differences
- Effective against debuggers that alter standard file access patterns

> This technique seems to NOT work on the tested setup.

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

- [Check Point: CreateFile (exclusive open)](https://anti-debug.checkpoint.com/techniques/object-handles.html#createfile)
- [Microsoft: CreateFileA function](https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea)
