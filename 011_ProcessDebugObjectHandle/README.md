# Context

This anti-debug technique checks if a process is being debugged by querying the `ProcessDebugObjectHandle` using `NtQueryInformationProcess`. When a debugger is attached, Windows creates a debug object for the process. By checking if this handle exists, we can detect debugging activity.

## Key Characteristics:
- **Method**: Uses `NtQueryInformationProcess` with `ProcessDebugObjectHandle` (class `0x1e`).
- **Detection**: A non-zero handle indicates an active debugger.
