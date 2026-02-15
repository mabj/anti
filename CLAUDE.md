# CLAUDE.md - Project Guidelines for Anti-Analysis Technique Collection

## Project Overview

This is an educational research repository documenting Windows anti-analysis techniques (anti-debugging, anti-sandbox, anti-reversing) used in malware. Each technique is a standalone C proof-of-concept for security researchers and malware analysts.

**Owner**: @marcos_alvares
**Primary use case**: Personal malware research reference

## Project Structure

```text
anti/
├── anti-debugging/AD###_TechniqueName/   # Anti-debugger techniques (AD prefix)
├── anti-sandbox/AS###_TechniqueName/    # Anti-sandbox techniques (AS prefix)
├── anti-reversing/                      # Reserved for future techniques (AR prefix)
├── docs/diagrams/taxonomy.md            # Visual taxonomy diagrams (mermaid)
├── website/index.html                   # 90's-hacker-style static site
├── README.md                            # Main project documentation
├── CONTRIBUTING.md                      # Contribution guidelines
└── CLAUDE.md                            # This file
```

Each technique directory follows this layout:

```text
AD###_TechniqueName/
├── src/main.c       # Source code (C, Windows API)
├── Makefile         # Build rules (MinGW cross-compilation, Docker)
├── Dockerfile       # Ubuntu 22.04 + MinGW build environment
├── README.md        # Technique description, build instructions, references
└── bin/             # Compiled binaries (x86 + amd64)
```

## Naming & Numbering Conventions

- **Anti-Debugging**: `AD###` (e.g., AD001, AD039) - sequential, zero-padded to 3 digits
- **Anti-Sandbox**: `AS###` (e.g., AS001, AS008)
- **Anti-Reversing**: `AR###` (reserved, not yet used)
- Directory format: `{prefix}{###}_{TechniqueName}` using PascalCase for technique names (e.g., `AD035_GetLocalTime`, `AS006_CopyOfNtdll`)

## Adding a New Technique

When asked to add or document a new technique, **all of the following files must be updated**:

### 1. Technique README (`anti-{category}/{ID}_{Name}/README.md`)

Must follow this exact format:

```markdown
# Context

[1-3 sentence description of what the technique does and how it works.]

Key characteristics:

- [Bullet points describing the mechanism]
- [Windows APIs used]
- [How detection works]
- [What makes this technique notable]

## Build

### Using Docker (Recommended)

\```bash
make build-image  # First time only
make build
\```

### Alternative: MinGW

\```bash
make
\```

## References

- [Link to References describing the technique]
```

### 2. Main README.md

Update **all 8 locations** when adding a technique:

1. **Badge: total count** - `[![Techniques](https://img.shields.io/badge/Techniques-{N}-brightgreen.svg)]()`
2. **Badge: category count** - `[![Anti-Debugging](https://img.shields.io/badge/Anti--Debugging-{N}-red.svg)]` or Anti-Sandbox equivalent
3. **About section** - "This repository documents {N} real-world anti-analysis techniques"
4. **Technique Breakdown** - `**Anti-Debugging** ({N} techniques)` (under "Technique Breakdown")
5. **Quick Start** - `anti-debugging/ - {N} techniques for detecting debuggers`
6. **Mermaid diagram** - Update total, category count, and percentage in the `graph TB` block
7. **Category Descriptions** - `**Anti-Debugging** ({N} techniques):` (under "Category Descriptions")
8. **Distribution line** - `> **Distribution**: {X}% Anti-Debugging | {Y}% Anti-Sandbox | 0% Anti-Reversing`
9. **Technique Index table** - Add a new row in the correct position (sorted by ID)

**Percentage calculation**: `category_count / total_count * 100`, rounded to 1 decimal place.

### 3. Website (`website/index.html`)

This is a single-page 90's-hacker-style static site listing all techniques. When adding a technique, add a new `<tr>` row to the correct table (Anti-Sandbox or Anti-Debugging) and under the correct subcategory section. Each row must include:

- **ID cell** with a link to the GitHub directory: `<td><a href="https://github.com/mabj/anti/tree/master/anti-{category}/{ID}_{Name}">{ID}</a></td>`
- **Technique name** cell
- **Description** cell

Also update the **stats counters** in the `<div class="stats">` section (total, anti-debug, anti-sandbox numbers).

**GitHub base URL**: `https://github.com/mabj/anti/tree/master/`

### 4. Taxonomy (`docs/diagrams/taxonomy.md`)

This file contains mermaid diagrams and tends to drift out of sync. When adding techniques, update:

- Main Taxonomy diagram (totals + percentages)
- Distribution pie chart
- Anti-Debugging or Anti-Sandbox detail diagram (add the new technique to its subcategory)
- Effectiveness Matrix (technique counts)
- Footer (date + total count)

**Anti-Debugging subcategories** (for classification):

- **PEB & Process Info**: Techniques querying PEB, debug ports, debug objects
- **Exception-Based**: INT instructions, exception filter abuse, handle tricks
- **Memory & Breakpoints**: Memory scanning, guard pages, write watching
- **Self-Protection**: Thread hiding, function patching, desktop switching, self-debugging
- **Timing-Based**: GetLocalTime, GetSystemTime, GetTickCount, QueryPerformanceCounter, timeGetTime
- **Other Detection**: Heap inspection, window enumeration, process parent checks

**Anti-Sandbox subcategories**:

- **Environment Detection**: Process lists, loaded modules, registry keys, window enumeration
- **Hook Detection**: SetErrorMode, ntdll copy, BlockInput
- **Timing Detection**: Sleep-based race conditions

## Code Style

- Language: **C** (C99 standard, `-std=c99`)
- Compiler: **MinGW-w64** cross-compiler (both i686 and x86_64)
- Platform: **Windows only** (uses Windows API, `windows.h`)
- Entry point function pattern: `__is_debugged()`, `__hide_from_debugger()`, or similar with `__` prefix
- MessageBox output pattern: `"[+] The process is in Debug mode."` / `"[+] The process is NOT in Debug mode."`
- No external dependencies beyond Windows system libraries
- Static linking preferred (`-static` flag)

## Build System

- **Docker + MinGW** (primary): `make build-image && make build`
- **Native MinGW** (alternative): `make`
- Outputs both x86 and amd64 binaries to `bin/`
- Dockerfile base: `ubuntu:22.04` with `nasm make mingw-w64`

### Standard Makefile Template

All technique Makefiles **must** follow this format (substitute `{TechniqueName}` and `{category}` accordingly):

```makefile
MAIN_NAME=anti_{category}_{technique_name_snake_case}

CC32 = i686-w64-mingw32-gcc -m32
CC64 = x86_64-w64-mingw32-gcc -m64
AR = ar
CFLAGS = -Wall -Wextra -std=c99 -static -Wno-missing-field-initializers -Wno-cast-function-type -Wno-unused-label -Wno-unused-parameter -masm=intel -Wa,--no-warn
OPTIMIZATION_FLAGS = -Os -s -ffunction-sections -fdata-sections -fno-ident
# -Wl -fgc-sections
LDFLAGS = #-lshlwapi -lpsapi -lws2_32

all: clean build-x86 build-amd64

build-image:
	docker build . -t ${MAIN_NAME}

build:
	docker run -it -m 4g --rm -v .:/experiment -w /experiment ${MAIN_NAME} make

build-amd64:
	$(CC64) -o bin/sample_{TechniqueName}_amd64.exe src/main.c $(CFLAGS) ${OPTIMIZATION_FLAGS} $(LDFLAGS)

build-x86:
	$(CC32) -o bin/sample_{TechniqueName}_x86.exe src/main.c $(CFLAGS) ${OPTIMIZATION_FLAGS} $(LDFLAGS)

enter:
	docker run -it -m 4g --rm -v .:/experiment -w /experiment --entrypoint /bin/bash ${MAIN_NAME}

clean:
	rm -rf bin/sample_{TechniqueName}_*.exe
```

Key conventions:
- **`MAIN_NAME`**: `anti_{category}_{snake_case_name}` (e.g., `anti_debug_is_debugger_present`)
- **Binary naming**: `sample_{TechniqueName}_{x86,amd64}.exe` (PascalCase technique name)
- **`CFLAGS`**: Must include all warning flags, `-masm=intel`, and `-Wa,--no-warn`
- **`OPTIMIZATION_FLAGS`**: Always use `-Os -s -ffunction-sections -fdata-sections -fno-ident`
- **`LDFLAGS`**: Commented-out defaults; uncomment only the libs actually needed
- **`clean`**: Only removes binaries (`bin/sample_*.exe`), never the `bin/` directory itself
- **`enter`** target: Always include for interactive Docker debugging

## Important Rules

- **Never modify source code** in `src/main.c` files unless explicitly asked - these are research artifacts
- **Always keep counts synchronized** across README.md when adding/removing techniques
- **Preserve table formatting** in the Technique Index - columns are: ID, Technique Name, Category, Platform, Description
- **Technique descriptions** in the index table should be concise (under ~80 chars) and start with a verb
- **Percentages** must add up correctly across the distribution line and mermaid diagrams
- **Do not reorder** existing techniques in the index table - new entries go at the end of their category section

## Common Tasks

| Task | Files to update |
| ------ | ---------------- |
| Add new technique | Technique `README.md`, main `README.md` (8 places), `website/index.html`, `docs/diagrams/taxonomy.md` |
| Fill technique context | Only the technique's `README.md` |
| Update counts only | Main `README.md` (8 places), `website/index.html` stats, `docs/diagrams/taxonomy.md` |
| Fix taxonomy drift | `docs/diagrams/taxonomy.md` only |

## Preferred References

- [Check Point Anti-Debug Research](https://anti-debug.checkpoint.com/)
- [Microsoft Win32 API Docs](https://learn.microsoft.com/en-us/windows/win32/api/)
- [Al-Khaser Project](https://github.com/ayoubfaouzi/al-khaser/tree/master/al-khaser)
- [Unprotect Project](https://unprotect.it/)

## Testing Environment

- **Primary OS**: Windows 11 23H2
- **Debuggers tested against**: x64dbg, WinDbg, OllyDbg
- **VM software**: VirtualBox, VMware, Hyper-V
- **Analysis sandboxes**: Any.run, Cuckoo, Joe Sandbox
