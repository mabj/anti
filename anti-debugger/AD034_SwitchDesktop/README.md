# Context

This technique hides the current process from debuggers by creating and switching to a new Windows desktop. Debuggers attached to the default desktop cannot follow processes that switch desktops.

Key characteristics:

- Creates a hidden desktop with `CreateDesktopA()`
- Uses `DESKTOP_SWITCDESKTOP` privilege for switching
- Debuggers lose process visibility after switch
- Particularly effective against user-mode debuggers

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

- [Check Point: SwitchDesktop Anti-Debug Technique](https://anti-debug.checkpoint.com/techniques/interactive.html#switchdesktop)
