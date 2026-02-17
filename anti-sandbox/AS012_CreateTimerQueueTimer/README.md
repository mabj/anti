# Context

Uses CreateTimerQueueTimer with a callback function to introduce execution delays that evade sandbox time acceleration. Creates a timer queue and registers a timer with a callback that signals an event after a specified delay, forcing sandboxes to handle thread pool-based timer callbacks that cannot be easily skipped or accelerated like Sleep-based delays.

Key characteristics:

- Creates a timer queue using CreateTimerQueue for managing lightweight timers
- Registers a timer callback function using CreateTimerQueueTimer that executes on a thread pool thread
- Timer callback signals an event when the due time arrives and parameters match
- Main thread waits on the event with WaitForSingleObject to detect if timer executed properly
- Uses 10x timeout multiplier to detect if sandbox skipped the timer (wait expires = detection)
- Sandboxes that accelerate Sleep() cannot easily skip timer queue callbacks from thread pool
- More complex than simple timers as it involves callback mechanism and thread pool execution
- Uses kernel32.dll timer queue APIs (CreateTimerQueue, CreateTimerQueueTimer, DeleteTimerQueueEx)

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

- [Al-Khaser: Timing Attacks - CreateTimerQueueTimer](https://github.com/LordNoteworthy/al-khaser/tree/master/al-khaser/TimingAttacks)
- [Microsoft CreateTimerQueueTimer Documentation](https://learn.microsoft.com/en-us/windows/win32/api/threadpoollegacyapiset/nf-threadpoollegacyapiset-createtimerqueuetimer)
- [Microsoft CreateTimerQueue Documentation](https://learn.microsoft.com/en-us/windows/win32/api/threadpoollegacyapiset/nf-threadpoollegacyapiset-createtimerqueue)
- [Unprotect Project: Timing Attacks](https://unprotect.it/category/evasion/timing-attack/)
