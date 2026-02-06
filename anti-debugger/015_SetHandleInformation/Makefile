MAIN_NAME=anti_debug_closehandle

# Visual Studio compiler commands
# Use short path to avoid space issues
CC = C:\Progra~1\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.50.00000\bin\Hostx64\x64\cl.exe /nologo

# Architecture-specific compiler flags
CFLAGS_X86 = /W4 /std:c11 /MT /D_CRT_SECURE_NO_WARNINGS /EHa /D_X86_ /arch:SSE2 /Os /GL /Gy
CFLAGS_AMD64 = /W4 /std:c11 /MT /D_CRT_SECURE_NO_WARNINGS /EHa /D_AMD64_ /fp:fast /Os /GL /Gy /wd4312

# Architecture-specific linker flags
LDFLAGS_X86 = /link /LTCG:OFF /MACHINE:X86 kernel32.lib user32.lib legacy_stdio_definitions.lib
LDFLAGS_AMD64 = /link /LTCG:OFF /MACHINE:X64 kernel32.lib user32.lib legacy_stdio_definitions.lib

all: build-x86 build-amd64

# Create build directories
build_dirs:
	@if not exist build\x86 mkdir build\x86
	@if not exist build\amd64 mkdir build\amd64

# Ensure bin directory exists
bin: build_dirs
	@if not exist bin mkdir bin

# Build targets using PowerShell script
build-amd64: bin
	powershell -ExecutionPolicy Bypass -File build.ps1 amd64
	@echo Built 64-bit executable: bin/sample_SetHandleInformation_amd64.exe

build-x86: bin
	powershell -ExecutionPolicy Bypass -File build.ps1 x86
	@echo Built 32-bit executable: bin/sample_SetHandleInformation_x86.exe

clean:
	if exist bin\sample_SetHandleInformation_*.exe del /Q bin\sample_SetHandleInformation_*.exe
	if exist build rmdir /S /Q build
	if exist bin rmdir /S /Q bin