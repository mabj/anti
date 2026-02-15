# Screenshot Placeholder Guide

This guide explains how to add screenshot placeholders to technique READMEs for future population.

## Standard Screenshot Section

Add this section to each technique's README after the main description and before the References section:

```markdown
## Example Output

### Normal Execution (No Debugger)

> 📸 **Screenshot placeholder**: Add screenshot showing normal execution without debugger

Expected output:
```
[*] Anti-Analysis Technique: [Technique Name]
[+] No debugger detected
[+] Execution completed successfully
```

### Debugger Detected

> 📸 **Screenshot placeholder**: Add screenshot showing debugger detection

Expected output:
```
[*] Anti-Analysis Technique: [Technique Name]
[!] Debugger detected!
[!] Terminating execution
```

### Visual Comparison

> 📸 **Screenshot placeholder**: Add side-by-side comparison of both scenarios
```

## Alternative: Using Image Placeholders

You can also create placeholder image files:

```markdown
## Example Output

### Normal Execution (No Debugger)
![Normal execution](screenshots/normal.png)
*Screenshot showing execution without debugger present*

### Debugger Detected
![Debugger detected](screenshots/detected.png)
*Screenshot showing debugger detection in action*

### Debugger Comparison
![Side by side comparison](screenshots/comparison.png)
*Visual comparison: Normal execution (left) vs Debugger detected (right)*
```

## Creating Placeholder Images

If you want to create placeholder images now:

1. Create a `screenshots/` directory in the technique folder
2. Add placeholder images (1280x720 or 1920x1080)
3. Use a simple text editor or screenshot tool with text:
   - `normal.png`: "Screenshot: Normal Execution - Coming Soon"
   - `detected.png`: "Screenshot: Debugger Detected - Coming Soon"
   - `comparison.png`: "Screenshot: Comparison - Coming Soon"

## Batch Update Script

To add placeholders to all techniques, you can use this approach:

### For techniques 001-039:

```bash
#!/bin/bash

for dir in [0-9][0-9][0-9]_*/; do
    if [ -f "$dir/README.md" ]; then
        echo "Updating $dir/README.md"

        # Check if "Example Output" section already exists
        if ! grep -q "## Example Output" "$dir/README.md"; then
            # Insert before References section
            sed -i '/## References/i\
## Example Output\
\
### Normal Execution (No Debugger)\
\
> 📸 **Screenshot placeholder**: Add screenshot showing normal execution without debugger\
\
Expected output:\
```\
[*] Anti-Analysis Technique: [Technique Name]\
[+] No debugger detected\
[+] Execution completed successfully\
```\
\
### Debugger Detected\
\
> 📸 **Screenshot placeholder**: Add screenshot showing debugger detection\
\
Expected output:\
```\
[*] Anti-Analysis Technique: [Technique Name]\
[!] Debugger detected!\
[!] Terminating execution\
```\
\
### Visual Comparison\
\
> 📸 **Screenshot placeholder**: Add side-by-side comparison of both scenarios\
\
' "$dir/README.md"
        fi
    fi
done
```

## README Template with Placeholders

Here's a complete template for technique READMEs:

```markdown
# [XXX] Technique Name

[![Category: Anti-Debugging](https://img.shields.io/badge/Category-Anti--Debugging-red)]()
[![Platform: Windows](https://img.shields.io/badge/Platform-Windows-blue)]()

## Overview

Brief 1-2 sentence description of what this technique does.

## How It Works

Detailed explanation of the technique mechanism:
- What API calls are used
- What the technique checks
- How detection is performed

## Technical Details

### API Calls Used
- `ApiFunction1()` - Purpose and behavior
- `ApiFunction2()` - Purpose and behavior

### Detection Method
Explain what exactly triggers the detection:
- Specific flags or values checked
- Conditions for detection
- Why this indicates a debugger/sandbox

## Building

```bash
# Using Docker
make build-image
make build

# Or with MinGW
make
```

## Example Output

### Normal Execution (No Debugger)

> 📸 **Screenshot placeholder**: Add screenshot showing normal execution

Expected output:
```
[*] Anti-Analysis Technique: Technique Name
[+] No debugger detected
[+] Execution completed successfully
```

### Debugger Detected

> 📸 **Screenshot placeholder**: Add screenshot showing detection

Expected output:
```
[*] Anti-Analysis Technique: Technique Name
[!] Debugger detected!
[!] Terminating execution
```

### Visual Comparison

> 📸 **Screenshot placeholder**: Side-by-side comparison

## Effectiveness

| Debugger/Tool | Detection Success | Notes |
|---------------|-------------------|-------|
| x64dbg | ✓ | Reliable detection |
| OllyDbg | ✓ | Works on all versions |
| WinDbg | ✓ | Detected in user-mode |
| IDA Pro | ? | Not tested |

## Limitations

- Known issues or version-specific problems
- Platforms where it doesn't work
- Known bypasses

## References

- [Reference 1](url) - Description
- [Reference 2](url) - Description

---

**Category**: Anti-Debugging / Anti-Sandbox / Anti-Reversing
**Last Updated**: YYYY-MM-DD
```

## Capturing Screenshots Later

When you're ready to capture actual screenshots:

### Tools Needed
- **Debugger**: x64dbg, OllyDbg, WinDbg, etc.
- **Screenshot tool**: Snipping Tool, ShareX, Greenshot
- **Optional**: Video capture for GIF animations

### Process
1. **Normal execution**:
   - Run technique without debugger
   - Capture terminal/console output
   - Save as `screenshots/normal.png`

2. **Debugger detection**:
   - Attach debugger to process
   - Run technique
   - Capture detection message
   - Save as `screenshots/detected.png`

3. **Comparison** (optional):
   - Create side-by-side layout
   - Show both scenarios
   - Save as `screenshots/comparison.png`

### Image Guidelines
- **Format**: PNG for screenshots, GIF for animations
- **Size**: 1280x720 or 1920x1080 recommended
- **Text**: Ensure text is readable
- **Highlighting**: Use red boxes/arrows to highlight important parts
- **Dark mode**: Consider using dark terminal theme for consistency

## Future Automation

Consider creating a testing framework that:
1. Runs each technique normally
2. Runs each technique with debugger
3. Captures output automatically
4. Generates comparison images
5. Updates README files

---

**Last Updated**: 2026-02-06
**Status**: Placeholders ready for future screenshots
