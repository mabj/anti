# Anti-Analysis Technique Collection

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Language: C](https://img.shields.io/badge/Language-C-blue.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Platform: Windows](https://img.shields.io/badge/Platform-Windows-lightgrey.svg)](https://www.microsoft.com/windows)
[![Techniques](https://img.shields.io/badge/Techniques-61-brightgreen.svg)]()
[![Anti-Debugging](https://img.shields.io/badge/Anti--Debugging-53-red.svg)](anti-debugging/)
[![Anti-Sandbox](https://img.shields.io/badge/Anti--Sandbox-8-orange.svg)](anti-sandbox/)

> A comprehensive, practical collection of anti-analysis techniques used in modern malware, designed for security researchers, malware analysts, and reverse engineers.

## About

This repository documents 61 real-world anti-analysis techniques discovered during malware research and reverse engineering. Each technique is implemented as a standalone proof-of-concept with source code, build instructions, and detailed documentation.

**Purpose**: Educational resource for understanding how malware evades detection and analysis tools.

**Audience**: Security researchers, malware analysts, reverse engineers, and defensive security professionals.

**Technique Breakdown**:

- 🛡️ **Anti-Debugging** (53 techniques): Detect debuggers and prevent debugging
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

- `anti-debugging/` - 53 techniques for detecting debuggers
- `anti-sandbox/` - 8 techniques for detecting sandboxes and VMs
- `anti-reversing/` - Reserved for future anti-reversing techniques

Each technique is in its own directory with category prefix (e.g., `anti-sandbox/AS001_SetErrorMode/`, `anti-debugging/AD002_IsDebuggerPresent/`). To explore a technique:

1. Navigate to the category directory, then technique subdirectory
2. Read the `README.md` for detailed explanation
3. Review the source code
4. Follow build instructions in the technique's README
5. Test in a safe, isolated environment

## Technique Categories

This collection organizes anti-analysis techniques into three main categories:

```mermaid
graph TB
    A[Anti-Analysis Techniques<br/>61 Total] --> B[Anti-Debugging<br/>53 techniques<br/>86.9%]
    A --> C[Anti-Sandbox<br/>8 techniques<br/>13.1%]
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

- **Anti-Debugging** (53 techniques): Techniques that detect debuggers attached to or monitoring the process. Includes PEB checks, exception-based detection, breakpoint scanning, and self-protection mechanisms.

- **Anti-Sandbox** (8 techniques): Techniques that detect automated analysis environments, virtual machines, sandboxes, or analysis tools in the system. Includes environment checks, VM artifact detection, and timing-based detection.

- **Anti-Reversing** (0 techniques): Reserved for future techniques that actively hinder reverse engineering through code obfuscation, anti-disassembly, control flow flattening, or other code protection mechanisms. No techniques implemented yet.

> 📊 **Distribution**: 86.9% Anti-Debugging | 13.1% Anti-Sandbox | 0% Anti-Reversing

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
| **Anti-Debugging** | | | | |
| [AD001](anti-debugging/AD001_CheckProcessDebugPort/) | Check Process Debug Port | Anti-Debugging | Windows | Queries ProcessDebugPort via NtQueryInformationProcess |
| [AD002](anti-debugging/AD002_IsDebuggerPresent/) | IsDebuggerPresent | Anti-Debugging | Windows | Checks PEB debug flag using IsDebuggerPresent API |
| [AD003](anti-debugging/AD003_CheckRemoteDebuggerPresent/) | CheckRemoteDebuggerPresent | Anti-Debugging | Windows | Detects debugger attached to specific process |
| [AD004](anti-debugging/AD004_ProcessDebugObjectHandle/) | ProcessDebugObjectHandle | Anti-Debugging | Windows | Queries ProcessDebugObjectHandle to detect debugging |
| [AD005](anti-debugging/AD005_CheckPEB/) | Check PEB | Anti-Debugging | Windows | Directly inspects debug flags in PEB structure |
| [AD006](anti-debugging/AD006_SetUnhandledExceptionFilter/) | SetUnhandledExceptionFilter | Anti-Debugging | Windows | Detects debugger takeover of exception handling chain |
| [AD007](anti-debugging/AD007_CloseHandle/) | CloseHandle Exception | Anti-Debugging | Windows | Checks if CloseHandle raises exception on invalid handle |
| [AD008](anti-debugging/AD008_SetHandleInformation/) | SetHandleInformation | Anti-Debugging | Windows | Abuses HANDLE_FLAG_PROTECT_FROM_CLOSE to detect debugger |
| [AD009](anti-debugging/AD009_RtlQueryProcessHeapInformation/) | RtlQueryProcessHeapInformation | Anti-Debugging | Windows | Detects debugger by examining heap flags |
| [AD010](anti-debugging/AD010_RtlQueryProcessDebugInformation/) | RtlQueryProcessDebugInformation | Anti-Debugging | Windows | Checks heap flags via RtlQueryProcessDebugInformation |
| [AD011](anti-debugging/AD011_DbgPrint/) | DbgPrint Exception | Anti-Debugging | Windows | Detects debugger via DbgPrint exception behavior |
| [AD012](anti-debugging/AD012_GetWriteWatch/) | GetWriteWatch | Anti-Debugging | Windows | Monitors protected memory for debugger modifications |
| [AD013](anti-debugging/AD013_GetThreadContext/) | GetThreadContext | Anti-Debugging | Windows | Inspects hardware breakpoint registers (Dr0-Dr7) |
| [AD014](anti-debugging/AD014_NtSetInformationThread/) | NtSetInformationThread | Anti-Debugging | Windows | Hides thread from debugger using ThreadHideFromDebugger |
| [AD015](anti-debugging/AD015_NtQueryObject/) | NtQueryObject | Anti-Debugging | Windows | Enumerates object types looking for DebugObject |
| [AD016](anti-debugging/AD016_RaiseException/) | RaiseException DBG_CONTROL_C | Anti-Debugging | Windows | Raises DBG_CONTROL_C to detect exception interception |
| [AD017](anti-debugging/AD017_SoftwareBreakpoint/) | Memory Breakpoint INT3 | Anti-Debugging | Windows | Scans function memory for breakpoints (0xCC) |
| [AD018](anti-debugging/AD018_AntiStepOver/) | Anti-Step-Over | Anti-Debugging | Windows | Checks for breakpoint at function return address |
| [AD019](anti-debugging/AD019_MemoryBreakpoint/) | Guard Page | Anti-Debugging | Windows | Uses guard page exception to detect debugger |
| [AD020](anti-debugging/AD020_NtQueryVirtualMemory_WorkingSetList/) | NtQueryVirtualMemory WorkingSetList | Anti-Debugging | Windows | Checks working set page attributes for modifications |
| [AD021](anti-debugging/AD021_DbgBreakPoint_patch/) | DbgBreakPoint Patch | Anti-Debugging | Windows | Patches DbgBreakPoint to prevent debugger attachment |
| [AD022](anti-debugging/AD022_DbgUiRemoteBreakin_hook/) | DbgUiRemoteBreakin Hook | Anti-Debugging | Windows | Patches DbgUiRemoteBreakin to block debugger attachment |
| [AD023](anti-debugging/AD023_INT3/) | INT3 (0xC3) | Anti-Debugging | Windows | Uses vectored exception handler with INT3 instruction |
| [AD024](anti-debugging/AD024_INT3_long/) | INT3 Long Form (0xCD03) | Anti-Debugging | Windows | Uses long form of INT3 for debugger detection |
| [AD025](anti-debugging/AD025_INT2D/) | INT 2D | Anti-Debugging | Windows | Kernel debugger interrupt for detection |
| [AD026](anti-debugging/AD026_INT1/) | INT1 ICEBP (0xF1) | Anti-Debugging | Windows | Uses ICEBP instruction for debugger detection |
| [AD027](anti-debugging/AD027_INT1_long/) | INT1 Long Form (0xCD01) | Anti-Debugging | Windows | Two-byte form of INT 1 for detection |
| [AD028](anti-debugging/AD028_popfd_trap/) | POPFD Trap Flag | Anti-Debugging | Windows | Manipulates Trap Flag via POPFD to trigger single-step |
| [AD029](anti-debugging/AD029_INT1_prefix/) | INT1 with Prefixes | Anti-Debugging | Windows | Uses instruction prefixes before ICEBP |
| [AD030](anti-debugging/AD030_self_debugging/) | Self-Debugging | Anti-Debugging | Windows | Attempts to debug itself to detect existing debugger |
| [AD031](anti-debugging/AD031_GenerateConsoleCtrlEvent/) | GenerateConsoleCtrlEvent | Anti-Debugging | Windows | Detects debugger by checking console control event handling |
| [AD032](anti-debugging/AD032_GetShellWindow/) | GetShellWindow | Anti-Debugging | Windows | Compares parent PID against Explorer to detect abnormal execution |
| [AD033](anti-debugging/AD033_FindWindow/) | FindWindow | Anti-Debugging | Windows | Detects debuggers by searching for known window class names |
| [AD034](anti-debugging/AD034_SwitchDesktop/) | SwitchDesktop | Anti-Debugging | Windows | Hides process from debugger by switching to a new desktop |
| [AD035](anti-debugging/AD035_GetLocalTime/) | GetLocalTime | Anti-Debugging | Windows | Detects debugger by measuring elapsed time of a known workload |
| [AD036](anti-debugging/AD036_GetSystemTime/) | GetSystemTime | Anti-Debugging | Windows | Detects debugger via UTC timing analysis of a known workload |
| [AD037](anti-debugging/AD037_GetTickCount/) | GetTickCount | Anti-Debugging | Windows | Detects debugger by comparing millisecond tick counts around a workload |
| [AD038](anti-debugging/AD038_QueryPerformanceCounter/) | QueryPerformanceCounter | Anti-Debugging | Windows | Detects debugger using high-resolution performance counter timing |
| [AD039](anti-debugging/AD039_timeGetTime/) | timeGetTime | Anti-Debugging | Windows | Detects debugger using multimedia timer elapsed time analysis |
| [AD040](anti-debugging/AD040_ProcessDebugFlags/) | ProcessDebugFlags | Anti-Debugging | Windows | Queries ProcessDebugFlags via NtQueryInformationProcess |
| [AD041](anti-debugging/AD041_NtGlobalFlag/) | NtGlobalFlag | Anti-Debugging | Windows | Checks PEB NtGlobalFlag for heap debugging flags set by debugger |
| [AD042](anti-debugging/AD042_HeapFlags/) | HeapFlags | Anti-Debugging | Windows | Inspects heap Flags and ForceFlags for debugger-set values |
| [AD043](anti-debugging/AD043_RDTSC/) | RDTSC | Anti-Debugging | Windows | Detects debugger using CPU timestamp counter cycle measurement |
| [AD044](anti-debugging/AD044_OpenProcess_CSRSS/) | OpenProcess CSRSS | Anti-Debugging | Windows | Detects elevated debugger by attempting to open protected csrss.exe process |
| [AD045](anti-debugging/AD045_CodeChecksum/) | Code Checksum | Anti-Debugging | Windows | Continuously monitors function checksums to detect breakpoints or code patches |
| [AD046](anti-debugging/AD046_CreateFileA_Exclusive/) | CreateFileA Exclusive | Anti-Debugging | Windows | Detects debuggers by attempting exclusive file access on current executable |
| [AD047](anti-debugging/AD047_SystemKernelDebuggerInformation/) | SystemKernelDebuggerInformation | Anti-Debugging | Windows | Detects kernel-mode debuggers by querying system kernel debugger flags |
| [AD048](anti-debugging/AD048_LoadLibrary/) | LoadLibrary | Anti-Debugging | Windows | Detects debugger via file handle behavior after LoadLibraryA on executable |
| [AD049](anti-debugging/AD049_DetectAPIPatch/) | DetectAPIPatch | Anti-Debugging | Windows | Detects debugger by comparing API function bytes across processes |
| [AD050](anti-debugging/AD050_KUSER_SHARED_DATA/) | KUSER_SHARED_DATA | Anti-Debugging | Windows | Reads KdDebuggerEnabled from KUSER_SHARED_DATA to detect kernel debugger |
| [AD051](anti-debugging/AD051_HEAP_TAIL_CHECKING_ENABLED/) | HEAP_TAIL_CHECKING_ENABLED | Anti-Debugging | Windows | Detects debugger by checking for 0xABABABAB heap tail sentinel pattern |
| [AD052](anti-debugging/AD052_InstructionCounting/) | Instruction Counting | Anti-Debugging | Windows | Detects debugger by counting hardware breakpoint single-step exceptions |
| [AD053](anti-debugging/AD053_StackSegment/) | Stack Segment Register | Anti-Debugging | Windows | Detects single-stepping debugger via SS register trap inhibit |

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
   cd anti-debugging/AD002_IsDebuggerPresent/
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
