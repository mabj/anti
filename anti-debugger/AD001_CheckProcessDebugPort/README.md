# Context

This anti-debug technique checks whether a debugger is attached to the current process by querying the `ProcessDebugPort` value using the Windows Native API function `NtQueryInformationProcess`.

Key characteristics:

- Uses low-level `NtQueryInformationProcess` instead of higher-level APIs
- Specifically checks the `ProcessDebugPort` information class
- Relies on the fact that a non-zero debug port indicates an active debugger
- Bypasses some user-mode debugger detection evasion techniques
- Requires linking against `ntdll.dll`

## Build (Docker)

```[text]
make build-image
make build
```

## References

- <https://bobvanderstaak.medium.com/unhooking-edr-by-remapping-ntdll-dll-101a99887dfe>
