# Context

This method detects behavioral changes caused by hooks on sleep calls by forcing a race condition. The technique was observed in-the-wild during analysis of Trik/Phorpiex spambot samples and relies on the timing of mutex creation to detect if Sleep() has been hooked or shortcutted by sandbox environments.

Key aspects:
- Creates a named mutex after calling Sleep() to establish timing expectations
- Persists itself to %APPDATA% and executes the persisted binary
- The persisted instance deletes the original binary and computes the main payload
- If the mutex already exists on startup, terminates immediately
- Main payload only executes if Sleep() runs normally without hooks
- Exploits sandbox behavior where Sleep() is commonly hooked to accelerate analysis

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

- [Microsoft: Sleep function](https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-sleep)
- [Microsoft: CreateMutex function](https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createmutexa)
