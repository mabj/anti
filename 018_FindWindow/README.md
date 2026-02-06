# Context

This technique detects debuggers by checking for known window class names used by debugging tools. The program scans for specific window titles/classes that are characteristic of debuggers like WinDbg, OllyDbg, and others.

Key characteristics:

- Uses Windows API `FindWindowA` to detect debugger windows
- Maintains a predefined blacklist of suspicious window class names
- Checks sequentially through the blacklist for matches
- Returns true if any debugger-related window is found

## References

- <https://anti-debug.checkpoint.com/techniques/misc.html#findwindow>
