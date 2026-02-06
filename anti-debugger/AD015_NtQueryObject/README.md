# Context

This technique detects debuggers by querying kernel object information using NtQueryObject(). It specifically searches for DebugObject kernel objects, which Windows creates when a debugger attaches to a process. The presence of these objects reliably indicates debugging activity.

Key aspects:
- Uses `NtQueryObject()` with `ObjectAllTypesInformation` class (0x03)
- Enumerates all kernel object types in the system
- Iterates through object type information structures
- Searches for entries with the name "DebugObject"
- Checks if any DebugObject instances exist (`TotalNumberOfObjects > 0`)
- Returns true if DebugObjects are found
- Effective because debuggers must create DebugObject kernel objects
- These objects persist until the debugger detaches
- Normal processes do not have DebugObject instances

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

- [Check Point: NtQueryObject Detection](https://anti-debug.checkpoint.com/techniques/object-handles.html#ntqueryobject)
- [Microsoft: NtQueryObject function](https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/ntifs/nf-ntifs-ntqueryobject)
- [al-khaser: NtQueryObject Implementation](https://github.com/ayoubfaouzi/al-khaser/blob/master/al-khaser/AntiDebug/NtQueryObject_AllTypesInformation.cpp)
