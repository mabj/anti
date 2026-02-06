# Context

This technique detects sandbox environments by inspecting SetErrorMode behavior for hooks. It uses the Windows API `SetErrorMode()` function to check if error mode settings persist as expected.

Key aspects:
- Uses `SetErrorMode()` with `0x400` (SEM_FAILCRITICALERRORS) flag
- Immediately checks if the setting persists using `SetErrorMode(0)`
- Relies on the fact that debuggers/sandboxes often modify error mode settings
- Specifically detects environments that reset SEM_FAILCRITICALERRORS
- The value `0x400` prevents system modal dialogs for critical errors

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

- [Microsoft: SetErrorMode function](https://docs.microsoft.com/en-us/windows/win32/api/errhandlingapi/nf-errhandlingapi-seterrormode)
