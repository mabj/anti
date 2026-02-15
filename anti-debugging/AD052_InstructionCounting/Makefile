MAIN_NAME=anti_debug_instruction_counting

CC32 = i686-w64-mingw32-gcc -m32
CC64 = x86_64-w64-mingw32-gcc -m64
AR = ar
CFLAGS = -Wall -Wextra -std=c99 -static -Wno-missing-field-initializers -Wno-cast-function-type -Wno-unused-label -Wno-unused-parameter -masm=intel -Wa,--no-warn
OPTIMIZATION_FLAGS = -Os -s -ffunction-sections -fdata-sections -fno-ident
# -Wl -fgc-sections
LDFLAGS = #-lshlwapi -lpsapi -lws2_32
SRCS = src/main.c src/hwbrk.c

all: clean build-x86 build-amd64

build-image:
	docker build . -t ${MAIN_NAME}

build:
	docker run -it -m 4g --rm -v .:/experiment -w /experiment ${MAIN_NAME} make

build-amd64:
	$(CC64) -o bin/AD052_InstructionCounting_amd64.exe $(SRCS) $(CFLAGS) ${OPTIMIZATION_FLAGS} $(LDFLAGS)

build-x86:
	$(CC32) -o bin/AD052_InstructionCounting_x86.exe $(SRCS) $(CFLAGS) ${OPTIMIZATION_FLAGS} $(LDFLAGS)

enter:
	docker run -it -m 4g --rm -v .:/experiment -w /experiment --entrypoint /bin/bash ${MAIN_NAME}

clean:
	rm -rf bin/AD052_InstructionCounting_*.exe
