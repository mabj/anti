# Context

- Copies `ntdll.dll` to temporary directory with random filename
- Loads copied DLL and retrieves `NtCreateMutant` address
- Creates named mutex "FLAG" using `NtCreateMutant` from clean copy of ntdll
- Technique bypasses EDR hooks by loading clean ntdll copy

## References
- https://bobvanderstaak.medium.com/unhooking-edr-by-remapping-ntdll-dll-101a99887dfe