# Comparative Analysis: Anti-Analysis Projects

This report compares three anti-analysis technique collections:

1. **This project** (`anti`) - 53 techniques
2. **Al-Khaser** (`github.com/LordNoteworthy/al-khaser`) - ~200+ techniques
3. **Check Point Anti-Debug Encyclopedia** (`anti-debug.checkpoint.com`) - 62 techniques

**Date**: 2026-02-06

---

## 1. Project Overview

| Aspect | This Project | Al-Khaser | Check Point |
| -------- | ------------- | ----------- | ------------- |
| **Type** | PoC collection | Monolithic test tool | Reference encyclopedia |
| **Language** | C (C99) | C++ / C / ASM | C/C++ snippets + ASM |
| **License** | MIT | GPL-2.0 | Proprietary (Check Point) |
| **Architecture** | Standalone executables (1 per technique) | Single binary (all-in-one) | Code snippets (reference) |
| **Build System** | Docker + MinGW (cross-compilation) | Visual Studio solution | N/A (documentation site) |
| **Platform** | Windows | Windows | Windows |
| **Anti-Debugger** | 45 techniques | ~34 techniques | 62 techniques |
| **Anti-Sandbox/VM** | 8 techniques | ~90+ techniques | N/A |
| **Anti-Disassembly** | 0 | 6 techniques | N/A |
| **Anti-Dumping** | 0 | 2 techniques | N/A |
| **Code Injection** | 0 | 7 techniques | N/A |
| **Timing Attacks** | 6 (in anti-debugger) | 12 techniques | 7 techniques |
| **Companion tool** | N/A | N/A | ShowStopper |

---

## 2. Scope Comparison

```[text]
                        Anti-Debug    Anti-Sandbox/VM    Anti-Disasm    Other
This Project            ████████████  ███
Al-Khaser               ████████████  █████████████████  ██             █████
Check Point             ██████████████████
```

- **This project** focuses on anti-debugger and anti-sandbox with clean, isolated implementations.
- **Al-Khaser** is the broadest: anti-debug, anti-VM (per-hypervisor), anti-disassembly, anti-dumping, code injection, DLL injection detection, and Office macro simulation.
- **Check Point** is the deepest on anti-debugging specifically, with 62 techniques and detailed explanations, but does not cover anti-sandbox or anti-VM.

---

## 3. Anti-Debugger Technique Coverage Matrix

This matrix maps each anti-debug technique across all three projects. A checkmark indicates the technique is present.

### 3.1 PEB & Process Info

| Technique | This Project | Al-Khaser | Check Point |
| ----------- | :---: | :---: | :---: |
| IsDebuggerPresent | AD002 | Yes | Yes |
| CheckRemoteDebuggerPresent | AD003 | Yes | Yes |
| NtQueryInformationProcess (ProcessDebugPort) | AD001 | Yes | Yes |
| NtQueryInformationProcess (ProcessDebugFlags) | AD040 | Yes | Yes |
| NtQueryInformationProcess (ProcessDebugObjectHandle) | AD004 | Yes | Yes |
| PEB BeingDebugged (manual) | AD005 | Yes | Yes |
| PEB NtGlobalFlag | AD041 | Yes | Yes |
| NtQueryObject (DebugObject) | AD015 | Yes | Yes |
| NtQuerySystemInformation (KernelDebugger) | - | - | Yes |
| KUSER_SHARED_DATA | - | - | Yes |

### 3.2 Heap Inspection

| Technique | This Project | Al-Khaser | Check Point |
| ----------- | :---: | :---: | :---: |
| RtlQueryProcessHeapInformation | AD009 | - | Yes |
| RtlQueryProcessDebugInformation | AD010 | - | Yes |
| Heap Flags (direct PEB inspection) | AD042 | Yes | Yes |
| Heap ForceFlags | AD042 | Yes | Yes |
| Heap Protection (sentinel patterns) | - | - | Yes |
| Low Fragmentation Heap | - | Yes | - |

### 3.3 Exception-Based

| Technique | This Project | Al-Khaser | Check Point |
| ----------- | :---: | :---: | :---: |
| SetUnhandledExceptionFilter | AD006 | Yes | Yes |
| CloseHandle / NtClose (invalid handle) | AD007 | Yes | Yes |
| SetHandleInformation | AD008 | Yes | - |
| DbgPrint exception | AD011 | - | Yes |
| RaiseException (DBG_CONTROL_C) | AD016 | - | Yes |
| OutputDebugString | AD011 | Yes | Yes |

### 3.4 Assembly / Interrupt-Based

| Technique | This Project | Al-Khaser | Check Point |
| ----------- | :---: | :---: | :---: |
| INT3 (0xCC) | AD023 | - | Yes |
| INT3 long form (0xCD03) | AD024 | - | Yes |
| INT 2D | AD025 | Yes | Yes |
| INT1 / ICEBP (0xF1) | AD026 | Yes | Yes |
| INT1 long form (0xCD01) | AD027 | - | - |
| POPFD Trap Flag | AD028 | Yes | Yes |
| INT1 with prefixes | AD029 | - | Yes |
| Stack Segment Register (push ss/pop ss) | - | - | Yes |
| Instruction Counting (HW BP) | - | - | Yes |
| DebugBreak | AD023 | - | Yes |

### 3.5 Memory & Breakpoint Detection

| Technique | This Project | Al-Khaser | Check Point |
| ----------- | :---: | :---: | :---: |
| Software breakpoint scan (0xCC) | AD017 | Yes | Yes |
| Anti-Step-Over | AD018 | - | Yes (4 variants) |
| Guard page / memory breakpoint | AD019 | Yes | Yes |
| Hardware breakpoint (GetThreadContext) | AD013 | Yes | Yes |
| NtQueryVirtualMemory (working set) | AD020 | - | Yes |
| GetWriteWatch | AD012 | Yes | Yes |
| Code checksum monitoring | AD045 | - | Yes |
| Detecting function patches | - | - | Yes |

### 3.6 Self-Protection / Anti-Attach

| Technique | This Project | Al-Khaser | Check Point |
| ----------- | :---: | :---: | :---: |
| NtSetInformationThread (HideFromDebugger) | AD014 | Yes | Yes |
| DbgBreakPoint patch | AD021 | - | Yes |
| DbgUiRemoteBreakin hook | AD022 | - | Yes |
| Self-Debugging | AD030 | - | Yes |
| SwitchDesktop | AD034 | - | Yes |

### 3.7 Timing-Based

| Technique | This Project | Al-Khaser | Check Point |
| ----------- | :---: | :---: | :---: |
| GetLocalTime | AD035 | - | Yes |
| GetSystemTime | AD036 | - | Yes |
| GetTickCount | AD037 | - | Yes |
| QueryPerformanceCounter | AD038 | - | Yes |
| timeGetTime | AD039 | - | Yes |
| RDTSC / RDPMC | AD043 | Yes | Yes |
| ZwGetTickCount / KiGetTickCount | - | - | Yes |
| Sleep acceleration detection | - | Yes | - |
| NtDelayExecution | - | Yes | - |
| SetTimer + message loop | - | Yes | - |
| WaitForSingleObject | - | Yes | - |
| IcmpSendEcho | - | Yes | - |
| CreateWaitableTimer | - | Yes | - |
| CreateTimerQueueTimer | - | Yes | - |

### 3.8 Behavioral / Other Detection

| Technique | This Project | Al-Khaser | Check Point |
| ----------- | :---: | :---: | :---: |
| FindWindow (debugger windows) | AD033 | - | Yes |
| Parent process check (GetShellWindow) | AD032 | Yes | Yes |
| GenerateConsoleCtrlEvent | AD031 | - | Yes |
| OpenProcess (csrss / SeDebugPrivilege) | AD044 | Yes | Yes |
| CreateFile (exclusive open) | - | - | Yes |
| LoadLibrary (file handle) | - | - | Yes |
| SwitchToThread / NtYieldExecution | - | Yes | Yes |
| TLS callbacks | - | Yes | - |
| Process jobs | - | Yes | - |
| API hook detection | - | Yes | - |
| EnumWindows + SuspendThread | - | - | Yes |
| WudfIsAnyDebuggerPresent | - | Yes | - |
| DbgSetDebugFilterState | - | - | Yes |
| Selectors | - | - | Yes |

---

## 4. Anti-Sandbox / Anti-VM Coverage

Check Point does not cover anti-sandbox. This comparison is between this project and Al-Khaser only.

| Technique | This Project | Al-Khaser |
| ----------- | :---: | :---: |
| SetErrorMode hook detection | AS001 | - |
| Sleep race condition | AS002 | Yes (variant) |
| Process list scanning | AS003 | Yes (49+ tools) |
| Loaded module (DLL) detection | AS004 | Yes (11 DLLs) |
| Registry key / device name check | AS005 | Yes (extensive) |
| Clean ntdll.dll copy | AS006 | - |
| Window enumeration | AS007 | - |
| BlockInput hook detection | AS008 | - |
| CPUID hypervisor bit | - | Yes |
| CPUID hypervisor vendor string | - | Yes |
| IDT/GDT/LDT/STR location | - | Yes |
| Processor/core count | - | Yes |
| Physical memory check | - | Yes |
| Disk size check | - | Yes (3 methods) |
| MAC address prefix | - | Yes (per-hypervisor) |
| WMI queries (BIOS, model, etc.) | - | Yes (20+ queries) |
| SMBIOS firmware tables | - | Yes |
| ACPI table inspection | - | Yes |
| VirtualBox-specific artifacts | - | Yes (23 checks) |
| VMware-specific artifacts | - | Yes (12 checks) |
| Hyper-V-specific artifacts | - | Yes (3 checks) |
| QEMU-specific artifacts | - | Yes (6 checks) |
| KVM-specific artifacts | - | Yes (4 checks) |
| Wine detection | - | Yes (2 checks) |
| Xen / Parallels / Virtual PC | - | Yes |
| Mouse movement detection | - | Yes |
| Suspicious filename detection | - | Yes |
| Known sandbox usernames/hostnames | - | Yes |
| Cloud hosting detection | - | Yes |
| NtQueryLicenseValue (VM detection) | - | Yes |
| Power capabilities | - | Yes |
| Thermal zone temperature | - | Yes |

**Key gap**: This project's anti-sandbox coverage is minimal (8 generic techniques) compared to Al-Khaser's 90+ checks with per-hypervisor detection. However, this project includes unique techniques like SetErrorMode hook detection (AS001) and clean ntdll.dll copy loading (AS006) that Al-Khaser does not implement.

---

## 5. Techniques Unique to Each Project

### 5.1 Unique to This Project (not in Al-Khaser or Check Point)

| ID | Technique | Notes |
| ---- | ----------- | ------- |
| AS001 | SetErrorMode hook detection | Unique sandbox evasion approach |
| AS006 | Clean ntdll.dll copy | Bypasses API hooks by loading fresh copy |
| AS007 | EnumWindowsProc (sandbox tools) | Window-based sandbox tool detection |
| AD027 | INT1 long form (0xCD01) | Specific opcode variant |

### 5.2 In Check Point but NOT in This Project (candidates for future techniques)

| Technique | Check Point Category | Priority |
| ----------- | --------------------- | ---------- |
| NtQuerySystemInformation (KernelDebugger) | Debug Flags | Medium |
| DebugBreak | Assembly | Medium |
| Stack Segment Register | Assembly | Low |
| Instruction Counting | Assembly | Low |
| KUSER_SHARED_DATA | Debug Flags | Low |
| Heap Protection (sentinel patterns) | Debug Flags | Low |
| Selectors | Misc | Low |
| DbgSetDebugFilterState | Misc | Low |
| EnumWindows + SuspendThread | Interactive | Low |

### 5.3 In Al-Khaser but NOT in This Project (candidates for future techniques)

| Technique | Category | Priority |
| ----------- | ---------- | ---------- |
| CPUID hypervisor detection | Anti-VM | High |
| WMI-based VM detection | Anti-VM | High |
| VirtualBox artifact checks | Anti-VM | Medium |
| VMware artifact checks | Anti-VM | Medium |
| Anti-disassembly tricks | Anti-Disassembly | Medium |
| Anti-dumping (PE header erase) | Anti-Dumping | Medium |
| Analysis tool process scanning | Anti-Analysis | Medium |
| Code injection techniques | Code Injection | Low |

---

## 6. Architectural Comparison

### Design Philosophy

| Aspect | This Project | Al-Khaser | Check Point |
| -------- | ------------- | ----------- | ------------- |
| **Isolation** | Each technique is standalone | All techniques in one binary | Code snippets in docs |
| **Reproducibility** | Docker builds ensure consistency | Requires Visual Studio | Copy-paste from website |
| **Cross-compilation** | MinGW (Linux/Mac to Windows) | Windows-only build | N/A |
| **Documentation** | Per-technique README | Single README + comments | Rich per-technique pages |
| **Extensibility** | Add new directory + files | Modify C++ source + project | N/A (read-only site) |
| **Testing** | Run individual technique | Run binary with `--check` flag | Use ShowStopper tool |

### Strengths

**This Project**:

- Clean isolation (one technique = one executable = one directory)
- Cross-platform build system (Docker + MinGW)
- Easy to understand individual techniques in isolation
- MIT license (maximum reuse freedom)
- Well-organized documentation with taxonomy diagrams

**Al-Khaser**:

- Most comprehensive coverage (~200+ techniques)
- Deep anti-VM detection (per-hypervisor checks)
- Includes offensive techniques (code injection, anti-disassembly)
- Selective execution via command-line flags
- Active community (~6.8k stars)

**Check Point**:

- Best documentation quality (detailed explanations + mitigations)
- Provides bypass/defense guidance for each technique
- Includes both C/C++ and assembly implementations
- Companion ShowStopper tool for testing
- Professional, curated by a Check Point reverse engineer

### Weaknesses

**This Project**:

- Limited anti-sandbox coverage (8 vs Al-Khaser's 90+)
- No anti-VM, anti-disassembly, or anti-dumping categories
- No kernel-level anti-debug techniques (NtQuerySystemInformation KernelDebugger)

**Al-Khaser**:

- Windows-only build (Visual Studio required)
- Monolithic binary makes it harder to study individual techniques
- GPL-2.0 license restricts commercial reuse
- C++ codebase is more complex than minimal C implementations

**Check Point**:

- Anti-debug only (no anti-sandbox, anti-VM, etc.)
- Read-only reference (no standalone executables)
- Proprietary content
- Not actively maintained (copyright 1994-2022)

---

## 7. Coverage Statistics

| Metric | This Project | Al-Khaser | Check Point |
| -------- | :-----------: | :---------: | :-----------: |
| Total anti-debug techniques | 45 | ~34 | 62 |
| Shared with Check Point | 39 / 62 (63%) | ~25 / 62 (40%) | - |
| Shared with Al-Khaser (anti-debug) | 27 / 34 (79%) | - | ~25 / 34 (74%) |
| Techniques unique to project | ~4 | ~30+ (mostly anti-VM) | ~15 |
| Anti-sandbox/VM techniques | 8 | ~90+ | 0 |

---

## 8. Recommendations

### Completed (previously high-priority)

- ~~NtQueryInformationProcess (ProcessDebugFlags)~~ - Implemented as **AD040**
- ~~PEB NtGlobalFlag (0x70)~~ - Implemented as **AD041**
- ~~Heap Flags / ForceFlags (direct)~~ - Implemented as **AD042**
- ~~RDTSC / RDPMC~~ - Implemented as **AD043**
- ~~OpenProcess on csrss.exe (SeDebugPrivilege)~~ - Implemented as **AD044**
- ~~Code checksum monitoring~~ - Implemented as **AD045**

### Medium-Priority Additions (present in one reference)

1. **NtQuerySystemInformation (KernelDebugger)** - Kernel-level detection (Check Point)
2. **CreateFile (exclusive open)** - Object handle detection (Check Point)
3. **CPUID hypervisor detection** - Essential anti-VM technique (Al-Khaser)
4. **WMI-based VM queries** - Modern anti-VM standard (Al-Khaser)
5. **Anti-disassembly techniques** - New category, 6 techniques from Al-Khaser

### New Category Suggestions

- **Anti-Reversing** (currently empty): Populate with anti-disassembly tricks from Al-Khaser
- **Anti-VM**: Dedicated hypervisor detection (CPUID, WMI, registry, driver artifacts)

---

## 9. References

- [This Project - GitHub](https://github.com/mabj/anti)
- [Al-Khaser - GitHub](https://github.com/LordNoteworthy/al-khaser)
- [Check Point Anti-Debug Encyclopedia](https://anti-debug.checkpoint.com/)
- [ShowStopper - Check Point Companion Tool](https://github.com/CheckPointSW/showstopper)
- [ScyllaHide - Anti-Anti-Debug Plugin](https://github.com/x64dbg/ScyllaHide)
- Peter Ferrie, "The Ultimate Anti-Debugging Reference"
