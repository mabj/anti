# Context

This technique detects debuggers and analysis tools by enumerating all active windows and examining their titles. It uses the Windows API to iterate through visible windows and check for title strings that indicate the presence of debugging tools like OllyDbg, x64dbg, IDA Pro, and others.

Key aspects:
- Uses `EnumWindows` API to enumerate all top-level windows
- Implements a callback function to inspect each window's title
- Calls `GetWindowText` to retrieve window titles
- Compares window titles against a blacklist of known debugger strings
- Can detect both active debugger windows and tool windows
- Effective against debuggers running in the same session

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

- [Check Point: Interactive Anti-Debug Techniques](https://anti-debug.checkpoint.com/techniques/interactive.html)
- [Microsoft: EnumWindows function](https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-enumwindows)
- [Microsoft: GetWindowText function](https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-getwindowtexta)
