# Context

This technique detects a debugger by calling `WudfIsAnyDebuggerPresent`, an exported function from `WudfPlatform.dll` — the Windows User Mode Driver Framework (UMDF) runtime library. The function is normally used inside UMDF driver host processes to determine whether any debugger is attached, but it is accessible to any process that loads the DLL dynamically.

Key characteristics:

- Loads `WudfPlatform.dll` at runtime via `LoadLibraryA` and resolves the target function with `GetProcAddress`
- `WudfIsAnyDebuggerPresent` is an undocumented UMDF platform API that internally checks for debugger presence
- Avoids commonly monitored APIs (`IsDebuggerPresent`, `CheckRemoteDebuggerPresent`) in favor of an obscure UMDF export
- If `WudfPlatform.dll` is not present (e.g., on systems without UMDF or WDK components), the check is skipped

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

- [Al-Khaser - WudfIsAnyDebuggerPresent](https://github.com/ayoubfaouzi/al-khaser/tree/master/al-khaser)
- [Microsoft UMDF Documentation](https://learn.microsoft.com/en-us/windows-hardware/drivers/wdf/user-mode-driver-framework-design-guide)
