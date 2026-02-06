# Contributing to Anti-Analysis Technique Collection

Thank you for your interest in contributing! This document provides guidelines for contributing new techniques, reporting issues, and improving the project.

## Table of Contents

- [Code of Conduct](#code-of-conduct)
- [How Can I Contribute?](#how-can-i-contribute)
- [Submitting New Techniques](#submitting-new-techniques)
- [Reporting Issues](#reporting-issues)
- [Improving Documentation](#improving-documentation)
- [Development Guidelines](#development-guidelines)

## Code of Conduct

This project follows a Code of Conduct to ensure a welcoming environment for all contributors. Please read and follow [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md).

## How Can I Contribute?

There are several ways to contribute:

1. **Submit new anti-analysis techniques** - Share techniques you've discovered in malware analysis
2. **Report issues** - Found a bug or compatibility issue? Let us know
3. **Improve documentation** - Help make the documentation clearer and more comprehensive
4. **Fix bugs** - Submit patches for issues
5. **Enhance existing techniques** - Improve code quality, add tests, or update documentation

## Submitting New Techniques

### Before You Start

1. **Search existing techniques** - Check if the technique already exists
2. **Verify the technique** - Ensure it works as expected in a test environment
3. **Research references** - Gather documentation, blog posts, or papers about the technique

### Technique Requirements

Each technique submission must include:

#### 1. Directory Structure

Create a new numbered directory following the existing pattern:

```
XXX_TechniqueName/
├── README.md           # Detailed explanation
├── main.c             # Source code
├── build.sh           # Build script (if applicable)
└── output.png         # Screenshot (optional but recommended)
```

#### 2. Source Code (`main.c`)

- **Clean, readable code** with appropriate comments
- **Error handling** where appropriate
- **Clear variable names** that explain purpose
- **Platform compatibility** - Specify Windows version requirements
- **No malicious payload** - Techniques should only demonstrate detection, not actual harm

Example structure:
```c
#include <windows.h>
#include <stdio.h>

// Function that implements the anti-analysis technique
BOOL DetectDebugger() {
    // Clear comments explaining the technique
    // ...
}

int main() {
    printf("[*] Anti-Analysis Technique: Your Technique Name\n");

    if (DetectDebugger()) {
        printf("[!] Debugger detected!\n");
        return 1;
    }

    printf("[+] No debugger detected\n");
    return 0;
}
```

#### 3. README.md

Each technique must have a comprehensive README including:

- **Title** - Clear, descriptive name
- **Description** - What the technique does and how it works
- **Technical Details** - Detailed explanation of the mechanism
- **Code Walkthrough** - Explanation of key code sections
- **Testing** - How to test the technique
- **Limitations** - Known limitations or compatibility issues
- **References** - Links to documentation, research papers, or blog posts

Example template:

```markdown
# [XXX] Technique Name

## Description

Brief description of what this technique does.

## How It Works

Detailed explanation of the mechanism behind the technique.

## Technical Details

- **API Calls Used**: List relevant API calls
- **Data Structures**: Describe key structures (PEB, TEB, etc.)
- **Detection Method**: Explain what the technique looks for

## Building

```bash
./build.sh
```

Or manually:
```bash
gcc -o technique.exe main.c
```

## Testing

Steps to test the technique:
1. Build the executable
2. Run normally: `./technique.exe`
3. Run with debugger: `x64dbg technique.exe`
4. Observe the different behavior

## Compatibility

- **Windows Version**: Specify tested versions
- **Debuggers**: Which debuggers it detects (x64dbg, OllyDbg, WinDbg, etc.)
- **Architecture**: x86, x64, or both

## Limitations

- Known bypasses
- Versions where it doesn't work
- Specific debugger behaviors

## References

- [Link 1](url)
- [Link 2](url)
```

#### 4. Build Script

Provide a build script (`build.sh` or `build.bat`) for easy compilation:

```bash
#!/bin/bash
# Build script for XXX_TechniqueName

echo "[*] Building XXX_TechniqueName..."

# For Windows with MinGW
x86_64-w64-mingw32-gcc -o technique.exe main.c -lpsapi

# Or for Linux
# gcc -o technique main.c

echo "[+] Build complete: technique.exe"
```

Make the script executable:
```bash
chmod +x build.sh
```

### Submission Process

1. **Fork the repository**
2. **Create a feature branch**
   ```bash
   git checkout -b technique/new-technique-name
   ```
3. **Add your technique** following the structure above
4. **Update main README.md** - Add your technique to the index table
5. **Test thoroughly** - Verify compilation and functionality
6. **Commit with clear message**
   ```bash
   git commit -m "Add technique XXX: TechniqueName"
   ```
7. **Push to your fork**
   ```bash
   git push origin technique/new-technique-name
   ```
8. **Open a Pull Request** with:
   - Clear title describing the technique
   - Summary of what the technique does
   - Test results (which debuggers it detects, OS versions tested)
   - References to research or malware samples where seen

## Reporting Issues

### Bug Reports

When reporting bugs, include:

- **Technique number and name**
- **Operating System** (version, architecture)
- **Compiler version** (gcc, mingw, MSVC)
- **Expected behavior**
- **Actual behavior**
- **Steps to reproduce**
- **Error messages or screenshots**

Use the GitHub issue template for bug reports.

### Feature Requests

For feature requests or technique suggestions:

- **Describe the technique** you'd like to see added
- **Provide references** if available
- **Explain the use case** or malware families using it

Use the GitHub issue template for technique requests.

## Improving Documentation

Documentation improvements are always welcome:

- **Fix typos or grammatical errors**
- **Clarify confusing explanations**
- **Add diagrams or screenshots**
- **Improve code comments**
- **Update outdated links**

For documentation changes:
1. Make your changes
2. Verify markdown renders correctly
3. Submit a pull request with "docs:" prefix
   ```bash
   git commit -m "docs: clarify explanation in technique 005"
   ```

## Development Guidelines

### Code Style

- **Indentation**: 4 spaces (no tabs)
- **Naming**: Clear, descriptive variable names
- **Comments**: Explain non-obvious logic
- **Error handling**: Check return values of API calls
- **Format**: Follow existing code style in the repository

### Commit Messages

Use clear, descriptive commit messages:

- **Format**: `type: brief description`
- **Types**:
  - `feat:` - New technique
  - `fix:` - Bug fix
  - `docs:` - Documentation changes
  - `refactor:` - Code refactoring
  - `test:` - Adding tests
  - `chore:` - Maintenance tasks

Examples:
```
feat: add technique 040 - ProcessHollowing detection
fix: correct API signature in technique 012
docs: update README with compatibility notes
```

### Testing

Before submitting:

- **Build successfully** on target platform
- **Test without debugger** - Verify normal execution
- **Test with debugger** - Verify detection works
- **Document results** - Note which debuggers were tested

### Pull Request Guidelines

- **One technique per PR** - Makes review easier
- **Clear description** - Explain what the technique does
- **Link issues** - Reference related issues if applicable
- **Pass CI/CD** - Ensure automated builds pass (once implemented)
- **Update documentation** - Keep README.md index current

## Questions?

If you have questions:

- **GitHub Discussions** - For general questions
- **GitHub Issues** - For bug reports or feature requests
- Check existing issues/discussions first

## Recognition

All contributors will be acknowledged in the project. Thank you for helping improve this resource for the security community!

---

By contributing, you agree that your contributions will be licensed under the project's MIT License.
