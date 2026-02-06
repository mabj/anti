# Context

This technique bypasses EDR and sandbox hooks by creating a clean copy of ntdll.dll and using functions from the unhooked version. The method loads a fresh copy of ntdll.dll from disk to avoid inline hooks that may be present in the loaded version.

Key aspects:
- Copies `ntdll.dll` from System32 to temporary directory with random filename
- Loads the copied DLL using `LoadLibrary` to get a clean, unhooked version
- Retrieves function addresses (e.g., `NtCreateMutant`) from the clean copy
- Executes sensitive operations using unhooked functions
- Bypasses userland hooks commonly deployed by EDR and sandbox solutions
- Creates named mutex "FLAG" as a demonstration using clean `NtCreateMutant`

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

- [Unhooking EDR by Remapping ntdll.dll](https://bobvanderstaak.medium.com/unhooking-edr-by-remapping-ntdll-dll-101a99887dfe)
- [Microsoft: LoadLibrary function](https://learn.microsoft.com/en-us/windows/win32/api/libloaderapi/nf-libloaderapi-loadlibrarya)
