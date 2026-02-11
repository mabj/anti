# Anti-Analysis Technique Collection

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Language: C](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform: Windows](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)](https://www.microsoft.com/windows)
[![Techniques](https://img.shields.io/badge/Techniques-55-brightgreen.svg)]()
[![Anti-Debugger](https://img.shields.io/badge/Anti--Debugger-47-red.svg)](anti-debugger/)
[![Anti-Sandbox](https://img.shields.io/badge/Anti--Sandbox-8-orange.svg)](anti-sandbox/)

> A comprehensive, practical collection of anti-analysis techniques used in modern malware, designed for security researchers, malware analysts, and reverse engineers.

## About

This repository documents 55 real-world anti-analysis techniques discovered during malware research and reverse engineering. Each technique is implemented as a standalone proof-of-concept with source code, build instructions, and detailed documentation.

**Purpose**: Educational resource for understanding how malware evades detection and analysis tools.

**Audience**: Security researchers, malware analysts, reverse engineers, and defensive security professionals.

**Technique Breakdown**:

- 🛡️ **Anti-Debugger** (47 techniques): Detect debuggers and prevent debugging
- 🔍 **Anti-Sandbox** (8 techniques): Detect sandboxes, VMs, and automated analysis
- 🔒 **Anti-Reversing** (0 techniques): Reserved for future code protection techniques

## Table of Contents

- [Anti-Analysis Technique Collection](#anti-analysis-technique-collection)
  - [About](#about)
  - [Table of Contents](#table-of-contents)
  - [Quick Start](#quick-start)
  - [Technique Categories](#technique-categories)
    - [Category Descriptions](#category-descriptions)
  - [Technique Index](#technique-index)
  - [Building Techniques](#building-techniques)
    - [Build System Overview](#build-system-overview)
      - [Docker + MinGW (Recommended)](#docker--mingw-recommended)
      - [Visual C++ (VC)](#visual-c-vc)
    - [General Build Process](#general-build-process)
    - [Build Requirements](#build-requirements)
    - [Troubleshooting](#troubleshooting)
  - [Contributing](#contributing)
  - [License](#license)
  - [Resources](#resources)
    - [Anti-Analysis References](#anti-analysis-references)
    - [Microsoft Documentation](#microsoft-documentation)
  - [Disclaimer](#disclaimer)

## Quick Start

Techniques are organized by category in dedicated directories:

- `anti-debugger/` - 47 techniques for detecting debuggers
- `anti-sandbox/` - 8 techniques for detecting sandboxes and VMs
- `anti-reversing/` - Reserved for future anti-reversing techniques

Each technique is in its own directory with category prefix (e.g., `anti-sandbox/AS001_SetErrorMode/`, `anti-debugger/AD002_IsDebuggerPresent/`). To explore a technique:

1. Navigate to the category directory, then technique subdirectory
2. Read the `README.md` for detailed explanation
3. Review the source code
4. Follow build instructions in the technique's README
5. Test in a safe, isolated environment

## Technique Categories

This collection organizes anti-analysis techniques into three main categories:

```mermaid
graph TB
    A[Anti-Analysis Techniques<br/>55 Total] --> B[Anti-Debugger<br/>47 techniques<br/>85.5%]
    A --> C[Anti-Sandbox<br/>8 techniques<br/>14.5%]
    A --> D[Anti-Reversing<br/>0 techniques<br/>0%]

    B --> B1[PEB/Process Checks]
    B --> B2[Exception-Based Detection]
    B --> B3[Memory/Breakpoint Detection]
    B --> B4[Self-Protection]

    C --> C1[Environment Detection]
    C --> C2[VM/Sandbox Artifacts]
    C --> C3[Timing Checks]

    D --> D1[Future: Code Obfuscation]
    D --> D2[Future: Anti-Disassembly]

    style A fill:#4A90E2,stroke:#2E5C8A,stroke-width:3px,color:#fff
    style B fill:#E74C3C,stroke:#C0392B,stroke-width:2px,color:#fff
    style C fill:#F39C12,stroke:#D68910,stroke-width:2px,color:#fff
    style D fill:#9B59B6,stroke:#7D3C98,stroke-width:2px,color:#fff
```

### Category Descriptions

- **Anti-Debugger** (47 techniques): Techniques that detect debuggers attached to or monitoring the process. Includes PEB checks, exception-based detection, breakpoint scanning, and self-protection mechanisms.

- **Anti-Sandbox** (8 techniques): Techniques that detect automated analysis environments, virtual machines, sandboxes, or analysis tools in the system. Includes environment checks, VM artifact detection, and timing-based detection.

- **Anti-Reversing** (0 techniques): Reserved for future techniques that actively hinder reverse engineering through code obfuscation, anti-disassembly, control flow flattening, or other code protection mechanisms. No techniques implemented yet.

> 📊 **Distribution**: 85.5% Anti-Debugger | 14.5% Anti-Sandbox | 0% Anti-Reversing

For detailed taxonomy and visual diagrams, see [docs/diagrams/taxonomy.md](docs/diagrams/taxonomy.md)

## Technique Index

| ID | Technique Name | Category | Platform | Description |
| --- | --- | --- | --- | --- |
| **Anti-Sandbox** | | | | |
| [AS001](anti-sandbox/AS001_SetErrorMode/) | SetErrorMode | Anti-Sandbox | Windows | Detects sandbox by inspecting SetErrorMode behavior for hooks |
| [AS002](anti-sandbox/AS002_ForcedRaceConditionSleep/) | Forced Race Condition Sleep | Anti-Sandbox | Windows | Forces race condition to detect changes in sleep() behavior |
| [AS003](anti-sandbox/AS003_CheckProcessList/) | Check Process List | Anti-Sandbox | Windows | Scans process list for known analysis tool names |
| [AS004](anti-sandbox/AS004_CheckLoadedModules/) | Check Loaded Modules | Anti-Sandbox | Windows | Detects injected DLLs from analysis tools in current process |
| [AS005](anti-sandbox/AS005_CheckRegistryKeys/) | Check Device Names | Anti-Sandbox | Windows | Searches Windows Registry for VM-related device names |
| [AS006](anti-sandbox/AS006_CopyOfNtdll/) | Copy of ntdll.dll | Anti-Sandbox | Windows | Loads clean ntdll.dll copy to bypass hooked functions |
| [AS007](anti-sandbox/AS007_EnumWindowsProc/) | FindWindow | Anti-Sandbox | Windows | Searches for windows with known analysis tool names |
| [AS008](anti-sandbox/AS008_BlockInput/) | BlockInput | Anti-Sandbox | Windows | Detects API hooking by analyzing BlockInput behavior |
| **Anti-Debugger** | | | | |
| [AD001](anti-debugger/AD001_CheckProcessDebugPort/) | Check Process Debug Port | Anti-Debugger | Windows | Queries ProcessDebugPort via NtQueryInformationProcess |
| [AD002](anti-debugger/AD002_IsDebuggerPresent/) | IsDebuggerPresent | Anti-Debugger | Windows | Checks PEB debug flag using IsDebuggerPresent API |
| [AD003](anti-debugger/AD003_CheckRemoteDebuggerPresent/) | CheckRemoteDebuggerPresent | Anti-Debugger | Windows | Detects debugger attached to specific process |
| [AD004](anti-debugger/AD004_ProcessDebugObjectHandle/) | ProcessDebugObjectHandle | Anti-Debugger | Windows | Queries ProcessDebugObjectHandle to detect debugging |
| [AD005](anti-debugger/AD005_CheckPEB/) | Check PEB | Anti-Debugger | Windows | Directly inspects debug flags in PEB structure |
| [AD006](anti-debugger/AD006_SetUnhandledExceptionFilter/) | SetUnhandledExceptionFilter | Anti-Debugger | Windows | Detects debugger takeover of exception handling chain |
| [AD007](anti-debugger/AD007_CloseHandle/) | CloseHandle Exception | Anti-Debugger | Windows | Checks if CloseHandle raises exception on invalid handle |
| [AD008](anti-debugger/AD008_SetHandleInformation/) | SetHandleInformation | Anti-Debugger | Windows | Abuses HANDLE_FLAG_PROTECT_FROM_CLOSE to detect debugger |
| [AD009](anti-debugger/AD009_RtlQueryProcessHeapInformation/) | RtlQueryProcessHeapInformation | Anti-Debugger | Windows | Detects debugger by examining heap flags |
| [AD010](anti-debugger/AD010_RtlQueryProcessDebugInformation/) | RtlQueryProcessDebugInformation | Anti-Debugger | Windows | Checks heap flags via RtlQueryProcessDebugInformation |
| [AD011](anti-debugger/AD011_DbgPrint/) | DbgPrint Exception | Anti-Debugger | Windows | Detects debugger via DbgPrint exception behavior |
| [AD012](anti-debugger/AD012_GetWriteWatch/) | GetWriteWatch | Anti-Debugger | Windows | Monitors protected memory for debugger modifications |
| [AD013](anti-debugger/AD013_GetThreadContext/) | GetThreadContext | Anti-Debugger | Windows | Inspects hardware breakpoint registers (Dr0-Dr7) |
| [AD014](anti-debugger/AD014_NtSetInformationThread/) | NtSetInformationThread | Anti-Debugger | Windows | Hides thread from debugger using ThreadHideFromDebugger |
| [AD015](anti-debugger/AD015_NtQueryObject/) | NtQueryObject | Anti-Debugger | Windows | Enumerates object types looking for DebugObject |
| [AD016](anti-debugger/AD016_RaiseException/) | RaiseException DBG_CONTROL_C | Anti-Debugger | Windows | Raises DBG_CONTROL_C to detect exception interception |
| [AD017](anti-debugger/AD017_SoftwareBreakpoint/) | Memory Breakpoint INT3 | Anti-Debugger | Windows | Scans function memory for breakpoints (0xCC) |
| [AD018](anti-debugger/AD018_AntiStepOver/) | Anti-Step-Over | Anti-Debugger | Windows | Checks for breakpoint at function return address |
| [AD019](anti-debugger/AD019_MemoryBreakpoint/) | Guard Page | Anti-Debugger | Windows | Uses guard page exception to detect debugger |
| [AD020](anti-debugger/AD020_NtQueryVirtualMemory_WorkingSetList/) | NtQueryVirtualMemory WorkingSetList | Anti-Debugger | Windows | Checks working set page attributes for modifications |
| [AD021](anti-debugger/AD021_DbgBreakPoint_patch/) | DbgBreakPoint Patch | Anti-Debugger | Windows | Patches DbgBreakPoint to prevent debugger attachment |
| [AD022](anti-debugger/AD022_DbgUiRemoteBreakin_hook/) | DbgUiRemoteBreakin Hook | Anti-Debugger | Windows | Patches DbgUiRemoteBreakin to block debugger attachment |
| [AD023](anti-debugger/AD023_INT3/) | INT3 (0xC3) | Anti-Debugger | Windows | Uses vectored exception handler with INT3 instruction |
| [AD024](anti-debugger/AD024_INT3_long/) | INT3 Long Form (0xCD03) | Anti-Debugger | Windows | Uses long form of INT3 for debugger detection |
| [AD025](anti-debugger/AD025_INT2D/) | INT 2D | Anti-Debugger | Windows | Kernel debugger interrupt for detection |
| [AD026](anti-debugger/AD026_INT1/) | INT1 ICEBP (0xF1) | Anti-Debugger | Windows | Uses ICEBP instruction for debugger detection |
| [AD027](anti-debugger/AD027_INT1_long/) | INT1 Long Form (0xCD01) | Anti-Debugger | Windows | Two-byte form of INT 1 for detection |
| [AD028](anti-debugger/AD028_popfd_trap/) | POPFD Trap Flag | Anti-Debugger | Windows | Manipulates Trap Flag via POPFD to trigger single-step |
| [AD029](anti-debugger/AD029_INT1_prefix/) | INT1 with Prefixes | Anti-Debugger | Windows | Uses instruction prefixes before ICEBP |
| [AD030](anti-debugger/AD030_self_debugging/) | Self-Debugging | Anti-Debugger | Windows | Attempts to debug itself to detect existing debugger |
| [AD031](anti-debugger/AD031_GenerateConsoleCtrlEvent/) | GenerateConsoleCtrlEvent | Anti-Debugger | Windows | Detects debugger by checking console control event handling |
| [AD032](anti-debugger/AD032_GetShellWindow/) | GetShellWindow | Anti-Debugger | Windows | Compares parent PID against Explorer to detect abnormal execution |
| [AD033](anti-debugger/AD033_FindWindow/) | FindWindow | Anti-Debugger | Windows | Detects debuggers by searching for known window class names |
| [AD034](anti-debugger/AD034_SwitchDesktop/) | SwitchDesktop | Anti-Debugger | Windows | Hides process from debugger by switching to a new desktop |
| [AD035](anti-debugger/AD035_GetLocalTime/) | GetLocalTime | Anti-Debugger | Windows | Detects debugger by measuring elapsed time of a known workload |
| [AD036](anti-debugger/AD036_GetSystemTime/) | GetSystemTime | Anti-Debugger | Windows | Detects debugger via UTC timing analysis of a known workload |
| [AD037](anti-debugger/AD037_GetTickCount/) | GetTickCount | Anti-Debugger | Windows | Detects debugger by comparing millisecond tick counts around a workload |
| [AD038](anti-debugger/AD038_QueryPerformanceCounter/) | QueryPerformanceCounter | Anti-Debugger | Windows | Detects debugger using high-resolution performance counter timing |
| [AD039](anti-debugger/AD039_timeGetTime/) | timeGetTime | Anti-Debugger | Windows | Detects debugger using multimedia timer elapsed time analysis |
| [AD040](anti-debugger/AD040_ProcessDebugFlags/) | ProcessDebugFlags | Anti-Debugger | Windows | Queries ProcessDebugFlags via NtQueryInformationProcess |
| [AD041](anti-debugger/AD041_NtGlobalFlag/) | NtGlobalFlag | Anti-Debugger | Windows | Checks PEB NtGlobalFlag for heap debugging flags set by debugger |
| [AD042](anti-debugger/AD042_HeapFlags/) | HeapFlags | Anti-Debugger | Windows | Inspects heap Flags and ForceFlags for debugger-set values |
| [AD043](anti-debugger/AD043_RDTSC/) | RDTSC | Anti-Debugger | Windows | Detects debugger using CPU timestamp counter cycle measurement |
| [AD044](anti-debugger/AD044_OpenProcess_CSRSS/) | OpenProcess CSRSS | Anti-Debugger | Windows | Detects elevated debugger by attempting to open protected csrss.exe process |
| [AD045](anti-debugger/AD045_CodeChecksum/) | Code Checksum | Anti-Debugger | Windows | Continuously monitors function checksums to detect breakpoints or code patches |
| [AD046](anti-debugger/AD046_CreateFileA_Exclusive/) | CreateFileA Exclusive | Anti-Debugger | Windows | Detects debuggers by attempting exclusive file access on current executable |
| [AD047](anti-debugger/AD047_SystemKernelDebuggerInformation/) | SystemKernelDebuggerInformation | Anti-Debugger | Windows | Detects kernel-mode debuggers by querying system kernel debugger flags |

## Building Techniques

Most techniques include:

- **Source code** (`main.c` or similar in `src/` directory)
- **Makefile** for compilation
- **Dockerfile** for containerized builds
- **README** with detailed explanation and references

### Build System Overview

This project uses a **mixed build system** to accommodate different compilation requirements:

#### Docker + MinGW (Recommended)

Most techniques use Docker with MinGW cross-compiler for consistent builds:

```bash
# Build Docker image
make build-image

# Compile technique (builds both x86 and x64)
make build

# Or build directly if you have MinGW installed
make
```

Output binaries are placed in the `bin/` directory.

#### Visual C++ (VC)

Some techniques may require Visual C++ compiler on Windows:

```bash
# Build with Visual Studio developer command prompt
cl /Fe:technique.exe src/main.c
```

### General Build Process

1. **Navigate to technique directory**:

   ```bash
   cd anti-sandbox/AS001_SetErrorMode/
   # or
   cd anti-debugger/AD002_IsDebuggerPresent/
   ```

2. **Check build requirements** in the technique's README

3. **Build using Docker** (most techniques):

   ```bash
   make build-image  # First time only
   make build
   ```

4. **Or build with MinGW** (if installed):

   ```bash
   make
   ```

5. **Find compiled binaries** in `bin/` directory

### Build Requirements

- **Docker**: For containerized builds (recommended)
- **MinGW-w64**: For native Windows builds on Linux/Mac
- **Visual Studio**: For techniques requiring VC compiler
- **GNU Make**: Build automation

### Troubleshooting

- **Docker not available**: Install MinGW cross-compiler and build directly
- **MinGW not available**: Use Docker for isolated builds
- **Build failures**: Check individual technique README for specific requirements
- **Missing dependencies**: Some techniques may require additional libraries

Refer to individual technique READMEs for specific build requirements and platform compatibility.

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
- [The Ultimate Anti-Debugging Reference](https://pferrie.epizy.com/papers/antidebug.pdf?i=1)
- [Apriorit Anti-Debugging with Examples](https://www.apriorit.com/dev-blog/367-anti-reverse-engineering-protection-techniques-to-use-before-releasing-software)

### Microsoft Documentation

- [Windows API Documentation](https://docs.microsoft.com/en-us/windows/win32/api/)
- [Undocumented NT Internals](http://undocumented.ntinternals.net/)

## Disclaimer

This repository is for **educational and research purposes only**. The techniques documented here are used by malware authors to evade detection. Understanding these techniques helps security professionals build better defenses.

**Do not use these techniques for malicious purposes.**

---

**Note**: Some techniques may not work on all Windows versions or with all debuggers. Compatibility notes are included in individual technique documentation where applicable.
