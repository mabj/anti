# Context

This technique checks for virtual machine and sandbox indicators by querying specific registry keys that often contain virtualization-related identifiers. It scans hardware enumeration registry paths to detect the presence of virtualized hardware components.

Key aspects:
- Scans `System\CurrentControlSet\Enum\IDE` and `System\CurrentControlSet\Enum\SCSI` registry paths
- Uses predefined blacklist of virtualization-related strings (qemu, virt, vmware, vbox, xen)
- Performs case-insensitive comparison by converting registry keys to lowercase
- Checks hardware identifiers commonly present in VM environments
- Returns positive detection if any blacklisted string is found in registry values
- Effective against automated sandbox analysis environments

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

- [Microsoft: Registry Functions](https://learn.microsoft.com/en-us/windows/win32/sysinfo/registry-functions)
- [Microsoft: RegOpenKeyEx function](https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regopenkeyexa)
- [Microsoft: RegEnumKeyEx function](https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regenumkeyexa)
