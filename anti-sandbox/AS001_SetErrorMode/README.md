# Context

This anti-debug technique uses the Windows API `SetErrorMode()` function to detect debuggers or sandbox environments by checking if error mode settings persist.

Key aspects of this technique:

- Uses `SetErrorMode()` with `0x400` (SEM_FAILCRITICALERRORS) flag
- Immediately checks if the setting persists using `SetErrorMode(0)`
- Relies on the fact that debuggers/sandboxes often modify error mode settings
- Specifically detects environments that reset SEM_FAILCRITICALERRORS
- The value `0x400` prevents system modal dialogs for critical errors

## References

- <https://docs.microsoft.com/en-us/windows/win32/api/errhandlingapi/nf-errhandlingapi-seterrormode>
