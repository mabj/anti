# Context

Uses CreateWaitableTimer and SetWaitableTimer to introduce execution delays that evade sandbox time acceleration. Creates a manual-reset waitable timer with a due time and waits on it until signaled, forcing sandboxes to handle high-resolution timer objects that cannot be easily skipped like Sleep-based delays.

Key characteristics:

- Creates a manual-reset waitable timer using CreateWaitableTimer
- Sets timer due time using SetWaitableTimer with negative relative time (100-nanosecond intervals)
- Waits on the timer object with WaitForSingleObject until it becomes signaled
- Timer is signaled automatically by the system when the due time arrives
- Sandboxes that accelerate Sleep() cannot easily skip waitable timer synchronization
- Uses high-resolution timer mechanism (100-nanosecond precision) instead of millisecond-based delays
- More resistant to time acceleration than standard Sleep or event-based delays
- Uses kernel32.dll synchronization APIs (CreateWaitableTimer, SetWaitableTimer, CancelWaitableTimer)

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

- [Al-Khaser: Timing Attacks - CreateWaitableTimer](https://github.com/LordNoteworthy/al-khaser/tree/master/al-khaser/TimingAttacks)
- [Microsoft CreateWaitableTimer Documentation](https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-createwaitabletimerw)
- [Microsoft SetWaitableTimer Documentation](https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-setwaitabletimer)
- [Unprotect Project: Timing Attacks](https://unprotect.it/category/evasion/timing-attack/)
