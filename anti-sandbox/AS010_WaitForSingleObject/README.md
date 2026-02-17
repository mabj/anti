# Context

Uses WaitForSingleObject with a non-signaled event to introduce execution delays that evade sandbox time acceleration. Creates an event object that will never be signaled and waits on it until timeout, forcing sandboxes to handle synchronization primitives that they cannot easily skip or accelerate like Sleep-based delays.

Key characteristics:

- Creates a manual-reset event in non-signaled state using CreateEvent
- Calls WaitForSingleObject with a timeout to force real-time waiting on synchronization object
- Event never gets signaled, so function always waits the full timeout period
- Sandboxes that accelerate Sleep() cannot easily skip WaitForSingleObject on kernel objects
- More robust than Sleep-based delays as it involves kernel synchronization mechanisms
- Uses kernel32.dll synchronization APIs (CreateEvent, WaitForSingleObject)
- Effective against automated analysis systems that patch or hook timing functions

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

- [Al-Khaser: Timing Attacks - WaitForSingleObject](https://github.com/LordNoteworthy/al-khaser/tree/master/al-khaser/TimingAttacks)
- [Microsoft WaitForSingleObject Documentation](https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-waitforsingleobject)
- [Microsoft CreateEvent Documentation](https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createeventa)
- [Unprotect Project: Timing Attacks](https://unprotect.it/category/evasion/timing-attack/)
