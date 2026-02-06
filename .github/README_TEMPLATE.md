# Standard README Template for Techniques

All technique READMEs should follow this standardized format with three main sections: Context, Build, and References.

## Template Structure

```markdown
# Context

[Description of what the technique does and how it works. Include key characteristics, mechanisms, and technical details.]

Key aspects/characteristics:
- [Bullet point 1]
- [Bullet point 2]
- [Bullet point 3]

## Build

Build instructions using Docker + MinGW (recommended) or alternative methods.

### Using Docker (Recommended)

\`\`\`bash
make build-image  # First time only
make build
\`\`\`

### Alternative: MinGW

\`\`\`bash
make
\`\`\`

### Alternative: Visual C++

\`\`\`bash
cl /Fe:technique.exe src/main.c
\`\`\`

## References

- [Reference 1 with description](URL)
- [Reference 2 with description](URL)
```

## Guidelines

### Context Section
- **First paragraph**: Clear explanation of what the technique does
- **Key aspects/characteristics**: Bullet list of important technical details
- **Keep it focused**: Technical but accessible
- **No badges or metadata**: Save for future enhancements

### Build Section
- **Docker first**: Primary build method
- **Alternatives**: MinGW and VC++ when applicable
- **Simple format**: No excessive explanation, just commands
- **Consistent**: Same structure across all techniques

### References Section
- **Quality over quantity**: Only include relevant, authoritative sources
- **Descriptive links**: Use descriptive link text, not bare URLs
- **Official docs prioritized**: Microsoft docs, research papers, reputable security blogs

## Example: Anti-Sandbox Technique

```markdown
# Context

This technique detects sandbox environments by inspecting SetErrorMode behavior for hooks. It uses the Windows API `SetErrorMode()` function to check if error mode settings persist as expected.

Key aspects:
- Uses `SetErrorMode()` with `0x400` (SEM_FAILCRITICALERRORS) flag
- Immediately checks if the setting persists using `SetErrorMode(0)`
- Relies on the fact that debuggers/sandboxes often modify error mode settings
- Specifically detects environments that reset SEM_FAILCRITICALERRORS
- The value `0x400` prevents system modal dialogs for critical errors

## Build

### Using Docker (Recommended)

\`\`\`bash
make build-image  # First time only
make build
\`\`\`

### Alternative: MinGW

\`\`\`bash
make
\`\`\`

## References

- [Microsoft: SetErrorMode function](https://docs.microsoft.com/en-us/windows/win32/api/errhandlingapi/nf-errhandlingapi-seterrormode)
- [Cyberbit: Formbook Research](https://www.cyberbit.com/formbook-research-hints-large-data-theft-attack-brewing/)
```

## Example: Anti-Debugger Technique

```markdown
# Context

This technique checks if the current process is attached to a debugger by calling the IsDebuggerPresent API from Kernel32. The function checks the BeingDebugged flag in the Process Environment Block (PEB).

Key aspects:
- Calls `IsDebuggerPresent()` from kernel32.dll
- Checks the BeingDebugged flag at PEB offset 0x02
- Returns TRUE (non-zero) if debugger is present
- Returns FALSE (zero) if no debugger is attached
- One of the most well-known but easily bypassed techniques
- Can be defeated by PEB flag manipulation or debugger plugins

## Build

### Using Docker (Recommended)

\`\`\`bash
make build-image  # First time only
make build
\`\`\`

### Alternative: MinGW

\`\`\`bash
make
\`\`\`

## References

- [Microsoft: IsDebuggerPresent function](https://learn.microsoft.com/en-us/windows/win32/api/debugapi/nf-debugapi-isdebuggerpresent)
- [Windows Internals: PEB Structure](https://learn.microsoft.com/en-us/windows/win32/api/winternl/ns-winternl-peb)
```

## Implementation Strategy

1. **Read existing README**: Extract context and references
2. **Preserve content**: Keep all technical details
3. **Restructure**: Apply standard template
4. **Simplify Build**: Use consistent build instructions
5. **Clean References**: Format as descriptive links

## What to Remove

- Extended sections like "Overview", "How It Works", "Technical Details", "Effectiveness", "Limitations", "Bypasses" - consolidate into Context
- Screenshot placeholders - remove for now
- Badges - remove for consistency
- Metadata footers - remove

## What to Keep

- All technical explanations
- Key characteristics and mechanisms
- All reference links
- Build instructions

---

**Purpose**: Consistency across all 39 technique READMEs
**Sections**: Context, Build, References
**Format**: Clean, focused, technical
