# Anti-Analysis Technique Collection

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Language: C](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform: Windows](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)](https://www.microsoft.com/windows)
[![Platform: Linux](https://img.shields.io/badge/Platform-Linux-orange.svg)](https://www.linux.org/)

> A comprehensive, practical collection of anti-analysis techniques used in modern malware, designed for security researchers, malware analysts, and reverse engineers.

## About

This repository documents 39 real-world anti-analysis techniques discovered during malware research and reverse engineering. Each technique is implemented as a standalone proof-of-concept with source code, build instructions, and detailed documentation.

**Purpose**: Educational resource for understanding how malware evades detection and analysis tools.

**Audience**: Security researchers, malware analysts, reverse engineers, and defensive security professionals.

## Table of Contents

- [Anti-Analysis Technique Collection](#anti-analysis-technique-collection)
  - [About](#about)
  - [Table of Contents](#table-of-contents)
  - [Quick Start](#quick-start)
  - [Technique Categories](#technique-categories)
  - [Technique Index](#technique-index)
  - [Building Techniques](#building-techniques)
    - [General Build Process](#general-build-process)
  - [Contributing](#contributing)
  - [License](#license)
  - [Resources](#resources)
    - [Anti-Analysis References](#anti-analysis-references)
    - [Microsoft Documentation](#microsoft-documentation)
  - [Disclaimer](#disclaimer)

## Quick Start

Each technique is contained in its own numbered directory (e.g., `001_SetErrorMode/`, `002_ForcedRaceConditionSleep/`). To explore a technique:

1. Navigate to the technique directory
2. Read the `README.md` for detailed explanation
3. Review the source code
4. Follow build instructions in the technique's README
5. Test in a safe, isolated environment

## Technique Categories

This collection organizes anti-analysis techniques into the following categories:

- **Debugger Detection**: Techniques that detect the presence of debuggers
- **Timing Checks**: Methods that detect analysis through timing anomalies
- **Environment Detection**: Checks for sandboxes, virtual machines, and analysis tools
- **Memory Protection**: Techniques that monitor or protect memory from tampering
- **Process/Thread Manipulation**: Methods involving process or thread behavior
- **Exception Handling**: Techniques exploiting exception handling mechanisms
- **Self-Protection**: Methods that prevent or hinder analysis

## Technique Index

| # | Technique Name | Category | Platform | Description |
| --- | --- | --- | --- | --- |
| [001](001_SetErrorMode/) | SetErrorMode | Environment Detection | Windows | Detects sandbox by inspecting SetErrorMode behavior for hooks |
| [002](002_ForcedRaceConditionSleep/) | Forced Race Condition Sleep | Timing Checks | Windows | Forces race condition to detect changes in sleep() behavior |
| [003](003_CheckProcessList/) | Check Process List | Environment Detection | Windows | Scans process list for known analysis tool names |
| [004](004_CheckLoadedModules/) | Check Loaded Modules | Environment Detection | Windows | Detects injected DLLs from analysis tools in current process |
| [005](005_CheckDeviceNames/) | Check Device Names | Environment Detection | Windows | Searches Windows Registry for VM-related device names |
| [006](006_CheckProcessDebugPort/) | Check Process Debug Port | Debugger Detection | Windows | Queries ProcessDebugPort via NtQueryInformationProcess |
| [007](007_CopyOfNtdll/) | Copy of ntdll.dll | Self-Protection | Windows | Loads clean ntdll.dll copy to bypass hooked functions |
| [008](008_IsDebuggerPresent/) | IsDebuggerPresent | Debugger Detection | Windows | Checks PEB debug flag using IsDebuggerPresent API |
| [009](009_CheckRemoteDebuggerPresent/) | CheckRemoteDebuggerPresent | Debugger Detection | Windows | Detects debugger attached to specific process |
| [010](010_FindWindow/) | FindWindow | Environment Detection | Windows | Searches for windows with known analysis tool names |
| [011](011_ProcessDebugObjectHandle/) | ProcessDebugObjectHandle | Debugger Detection | Windows | Queries ProcessDebugObjectHandle to detect debugging |
| [012](012_CheckPEB/) | Check PEB | Debugger Detection | Windows | Directly inspects debug flags in PEB structure |
| [013](013_SetUnhandledExceptionFilter/) | SetUnhandledExceptionFilter | Exception Handling | Windows | Detects debugger takeover of exception handling chain |
| [014](014_CloseHandle/) | CloseHandle Exception | Exception Handling | Windows | Checks if CloseHandle raises exception on invalid handle |
| [015](015_SetHandleInformation/) | SetHandleInformation | Exception Handling | Windows | Abuses HANDLE_FLAG_PROTECT_FROM_CLOSE to detect debugger |
| [016](016_RtlQueryProcessHeapInformation/) | RtlQueryProcessHeapInformation | Debugger Detection | Windows | Detects debugger by examining heap flags |
| [017](017_RtlQueryProcessDebugInformation/) | RtlQueryProcessDebugInformation | Debugger Detection | Windows | Checks heap flags via RtlQueryProcessDebugInformation |
| [018](018_FindWindow/) | FindWindow (Debugger Titles) | Environment Detection | Windows | Searches for window titles of known debuggers |
| [019](019_GetShellWindow/) | GetShellWindow | Environment Detection | Windows | Compares parent PID against shell window PID |
| [020](020_DbgPrint/) | DbgPrint Exception | Exception Handling | Windows | Detects debugger via DbgPrint exception behavior |
| [021](021_GetWriteWatch/) | GetWriteWatch | Memory Protection | Windows | Monitors protected memory for unexpected writes |
| [022](022_GetThreadContext/) | GetThreadContext | Debugger Detection | Windows | Inspects hardware breakpoint registers (Dr0-Dr7) |
| [023](023_NtSetInformationThread/) | NtSetInformationThread | Process/Thread Manipulation | Windows | Hides thread from debugger using ThreadHideFromDebugger |
| [024](024_NtQueryObject/) | NtQueryObject | Debugger Detection | Windows | Enumerates object types looking for DebugObject |
| [025](025_RaiseException/) | RaiseException DBG_CONTROL_C | Exception Handling | Windows | Raises DBG_CONTROL_C to detect exception interception |
| [026](026_MemoryBreakpoint/) | Memory Breakpoint INT3 | Memory Protection | Windows | Scans function memory for breakpoints (0xCC) |
| [027](027_AntiStepOver/) | Anti-Step-Over | Memory Protection | Windows | Checks for breakpoint at function return address |
| [028](028_MemoryBreakpoint/) | Guard Page | Memory Protection | Windows | Uses guard page exception to detect debugger |
| [029](029_NtQueryVirtualMemory_WorkingSetList/) | NtQueryVirtualMemory WorkingSetList | Memory Protection | Windows | Checks working set page attributes for modifications |
| [030](030_DbgBreakPoint_patch/) | DbgBreakPoint Patch | Self-Protection | Windows | Patches DbgBreakPoint to prevent debugger attachment |
| [031](031_DbgUiRemoteBreakin_hook/) | DbgUiRemoteBreakin Hook | Self-Protection | Windows | Patches DbgUiRemoteBreakin to block debugger attachment |
| [032](032_INT3/) | INT3 (0xC3) | Exception Handling | Windows | Uses vectored exception handler with INT3 instruction |
| [033](033_INT3_long/) | INT3 Long Form (0xCD03) | Exception Handling | Windows | Uses long form of INT3 for debugger detection |
| [034](034_INT_2D/) | INT 2D | Exception Handling | Windows | Kernel debugger interrupt for detection |
| [035](035_INT1/) | INT1 ICEBP (0xF1) | Exception Handling | Windows | Uses ICEBP instruction for debugger detection |
| [036](036_INT1_long/) | INT1 Long Form (0xCD01) | Exception Handling | Windows | Two-byte form of INT 1 for detection |
| [037](037_popfd_trap/) | POPFD Trap Flag | Exception Handling | Windows | Manipulates Trap Flag via POPFD to trigger single-step |
| [038](038_INT1_prefix/) | INT1 with Prefixes | Exception Handling | Windows | Uses instruction prefixes before ICEBP |
| [039](039_self_debugging/) | Self-Debugging | Debugger Detection | Windows | Attempts to debug itself to detect existing debugger |

## Building Techniques

Most techniques include:

- **Source code** (`main.c` or similar)
- **Build script** (`build.sh` or `build.bat`)
- **README** with detailed explanation and references

### General Build Process

For Windows techniques:

```[bash]
# Using build script
./build.sh

# Or manually with GCC/MinGW
gcc -o technique.exe main.c
```

Refer to individual technique READMEs for specific build requirements and dependencies.

## Contributing

Contributions are welcome! Please see [CONTRIBUTING.md](CONTRIBUTING.md) for guidelines on:

- Submitting new techniques
- Reporting issues
- Improving documentation
- Code style requirements

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Resources

### Anti-Analysis References

- [CheckPoint Anti-Debug Techniques](https://anti-debug.checkpoint.com/)
- [Al-Khaser Anti-Malware Scanner](https://github.com/LordNoteworthy/al-khaser)
- [Malware Analysis Bootcamp](https://www.malwaretech.com/)

### Microsoft Documentation

- [Windows API Documentation](https://docs.microsoft.com/en-us/windows/win32/api/)
- [Undocumented NT Internals](http://undocumented.ntinternals.net/)

## Disclaimer

This repository is for **educational and research purposes only**. The techniques documented here are used by malware authors to evade detection. Understanding these techniques helps security professionals build better defenses.

**Do not use these techniques for malicious purposes.**

---

**Note**: Some techniques may not work on all Windows versions or with all debuggers. Compatibility notes are included in individual technique documentation where applicable.
