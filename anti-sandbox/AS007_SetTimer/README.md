# Context

Uses SetTimer API with a message loop to introduce execution delays that evade sandbox time acceleration. Sandboxes often skip or accelerate Sleep/delay functions to speed up analysis, but this technique forces real-time execution by pumping Windows messages with a timer callback.

Key characteristics:

- Uses SetTimer with a callback function instead of Sleep-based delays
- Implements Windows message pump (GetMessage/DispatchMessage) to process timer events
- Forces sandbox to either wait for real timer expiration or reveal hook behavior
- Sandboxes that accelerate Sleep() cannot easily skip message-driven timer events
- Effective against automated analysis systems with limited execution time windows
- Uses user32.dll timer APIs (SetTimer, KillTimer) and message queue mechanism

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

- [Al-Khaser: Timing Attacks](https://github.com/LordNoteworthy/al-khaser/tree/master/al-khaser/TimingAttacks)
- [Microsoft SetTimer Documentation](https://learn.microsoft.com/en-us/windows/win32/api/winuser/nf-winuser-settimer)
- [Unprotect Project: Timing Attacks](https://unprotect.it/category/evasion/timing-attack/)
