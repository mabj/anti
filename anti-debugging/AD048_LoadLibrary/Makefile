# Makefile for AD048_LoadLibrary

# Compiler settings
CC_x86 = i686-w64-mingw32-gcc
CC_x64 = x86_64-w64-mingw32-gcc
CFLAGS = -std=c99 -Wall -Wextra -O2 -static
LDFLAGS = -luser32

# Directories
SRC_DIR = src
BIN_DIR = bin

# Source files
SOURCES = $(SRC_DIR)/main.c

# Output binaries
TARGET_x86 = $(BIN_DIR)/AD048_LoadLibrary_x86.exe
TARGET_x64 = $(BIN_DIR)/AD048_LoadLibrary_x64.exe

# Default target
all: $(TARGET_x86) $(TARGET_x64)

# Create bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Build x86 binary
$(TARGET_x86): $(SOURCES) | $(BIN_DIR)
	$(CC_x86) $(CFLAGS) $(SOURCES) -o $(TARGET_x86) $(LDFLAGS)

# Build x64 binary
$(TARGET_x64): $(SOURCES) | $(BIN_DIR)
	$(CC_x64) $(CFLAGS) $(SOURCES) -o $(TARGET_x64) $(LDFLAGS)

# Clean build artifacts
clean:
	rm -rf $(BIN_DIR)

# Build using Docker
build-image:
	docker build -t ad048-loadlibrary-builder .

build: build-image
	docker run --rm -v $(shell pwd):/work ad048-loadlibrary-builder

.PHONY: all clean build-image build
