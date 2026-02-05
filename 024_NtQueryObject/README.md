# Context

This anti-debug technique detects debuggers by querying kernel object information using `NtQueryObject()`. It specifically checks for the existence of "DebugObject" kernel objects, which are created when a debugger attaches to a process.

Key characteristics:

- Uses `NtQueryObject()` with `ObjectAllTypesInformation` to enumerate all object types
- Iterates through object information structures to find "DebugObject" entries
- Checks if any DebugObject instances exist (`TotalNumberOfObjects > 0`)
- Returns true if DebugObjects are found, indicating debugger presence

The technique is effective because:

1. Debuggers must create DebugObject kernel objects to manage debugging sessions
2. These objects persist until the debugger detaches
3. Normal processes don't have DebugObject instances

## References

- <https://anti-debug.checkpoint.com/techniques/object-handles.html#ntqueryobject>
- <https://github.com/ayoubfaouzi/al-khaser/blob/master/al-khaser/AntiDebug/NtQueryObject_AllTypesInformation.cpp>