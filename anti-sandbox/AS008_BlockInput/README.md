# Context

This anti-sandbox technique detects API hooking by analyzing the behavior of consecutive `BlockInput()` calls.

Key aspects:

- Calls `BlockInput(true)` twice consecutively to block keyboard and mouse input
- `BlockInput()` normally returns FALSE on second call (input already blocked)
- In sandboxes with hooked APIs, the second call may incorrectly return TRUE
- Detects hooks by checking if the second `BlockInput(true)` returns TRUE
- Effective against sandboxes that hook user32.dll functions
- Does not require administrative privileges to detect hooks
- Simple technique that exploits API hook implementation flaws
- Relies on inconsistent hook behavior in automated analysis environments

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

- [Microsoft: BlockInput function](https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-blockinput)
- [Anti-Debugging Techniques: BlockInput](https://anti-debug.checkpoint.com/)
