# Context

This anti-debug technique checks for virtual machine/sandbox indicators by querying specific registry keys that often contain virtualization-related identifiers. It scans the `System\CurrentControlSet\Enum\IDE` and `System\CurrentControlSet\Enum\SCSI` registry paths for blacklisted strings (qemu, virt, vmware, vbox, xen) that indicate virtualization environments.

Key characteristics:

- Scans hardware registry paths known to contain VM identifiers
- Uses predefined blacklist of virtualization-related strings
- Performs case-insensitive comparison by lowercasing keys
- Returns positive detection if any blacklisted string is found
- Focuses on evasion of sandbox analysis environments

## Build (Docker)

```[text]
make build-image
make build
```

## References

- <https://bobvanderstaak.medium.com/unhooking-edr-by-remapping-ntdll-dll-101a99887dfe>