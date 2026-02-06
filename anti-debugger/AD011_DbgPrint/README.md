# Context

This technique uses the DbgPrint function from ntdll.dll to detect debugger presence by exploiting how Windows handles debug print exceptions. The function behaves differently when a debugger is attached versus normal execution, allowing for reliable detection in certain environments.

Key aspects:
- Loads ntdll.dll and resolves the `DbgPrint` function pointer
- Calls `DbgPrint` inside a structured exception handler (__try/__except)
- Checks if exception code is DBG_PRINTEXCEPTION_C (0x40010006)
- Returns true if no exception occurs, indicating debugger is attached
- Returns false if exception occurs, indicating no debugger
- Exploits debugger handling of debug print messages
- Note: This technique does not work on Windows 10 64-bit systems
- Requires Visual Studio compiler for structured exception handling support

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

- [Microsoft: DbgPrint function](https://learn.microsoft.com/en-us/windows-hardware/drivers/ddi/wdm/nf-wdm-dbgprint)
- [al-khaser: DbgPrint Implementation](https://github.com/ayoubfaouzi/al-khaser/blob/master/al-khaser/AntiDebug/DbgPrint.cpp)
