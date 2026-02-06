# Context

This technique detects debuggers by checking for known window class names used by debugging tools. The program uses FindWindowA to search for specific window classes that are characteristic of debuggers like WinDbg, OllyDbg, x64dbg, and other analysis tools.

Key aspects:
- Uses Windows API `FindWindowA` to detect debugger windows by class name
- Maintains a predefined blacklist of suspicious window class names
- Checks sequentially through the blacklist for matches
- Returns true if any debugger-related window is found
- Simpler than EnumWindows approach but limited to known class names
- Can detect debuggers even if window titles are modified

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

- [Check Point: FindWindow Anti-Debug Technique](https://anti-debug.checkpoint.com/techniques/misc.html#findwindow)
- [Microsoft: FindWindow function](https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-findwindowa)
