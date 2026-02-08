# Context

This technique detects a debugger by directly inspecting the `Flags` and `ForceFlags` fields in the process heap header. When a debugger creates the process, the heap manager sets additional diagnostic flags (tail checking, free checking, parameter validation). The code reads these fields at version-specific offsets and checks whether any unexpected flags are present.

Key characteristics:

- Reads the PEB via segment registers (`fs:[0x30]` on x86, `gs:[0x60]` on x64) to locate the default process heap
- Inspects `Heap.Flags` and `Heap.ForceFlags` at offsets that differ between pre-Vista and Vista+ systems
- Handles WoW64 (32-bit process on 64-bit OS) with a separate PEB heap pointer offset (`0x1030`)
- Detection logic: flags beyond `HEAP_GROWABLE` in `Flags`, or any non-zero `ForceFlags`, indicate a debugger
- No API calls — reads raw memory structures, making it invisible to API hooks
- Complementary to AD009 (RtlQueryProcessHeapInformation) and AD010 (RtlQueryProcessDebugInformation), which use APIs to query similar heap state

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

- [Microsoft: NtQueryInformationProcess function](https://learn.microsoft.com/en-us/windows/win32/api/winternl/nf-winternl-ntqueryinformationprocess)
- [Check Point: ProcessDebugPort](https://anti-debug.checkpoint.com/techniques/debug-flags.html#manual-checks-processdebugport)
