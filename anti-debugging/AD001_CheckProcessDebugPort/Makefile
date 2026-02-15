MAIN_NAME=anti_check_process_debug_port

CC32 = i686-w64-mingw32-gcc -m32
CC64 = x86_64-w64-mingw32-gcc -m64
AR = ar
CFLAGS = -Wall -Wextra -std=c99 -static -Wno-missing-field-initializers -Wno-cast-function-type -Wno-unused-label -Wno-unused-parameter -masm=intel -Wa,--no-warn
OPTIMIZATION_FLAGS = -Os -s -ffunction-sections -fdata-sections -fno-ident
# -Wl -fgc-sections
LDFLAGS = -lntdll #-lshlwapi -lpsapi -lws2_32 



all: clean build-x86 build-amd64

build-image:
	docker build . -t ${MAIN_NAME}

build:
	docker run -it -m 4g --rm -v .:/experiment -w /experiment ${MAIN_NAME} make

build-amd64:
	$(CC64) -o bin/sample_CheckProcessDebugPort_amd64.exe src/main.c $(CFLAGS) ${OPTIMIZATION_FLAGS} $(LDFLAGS)

build-x86:
	$(CC32) -o bin/sample_CheckProcessDebugPort_x86.exe src/main.c $(CFLAGS) ${OPTIMIZATION_FLAGS} $(LDFLAGS)

enter:
	docker run -it -m 4g --rm -v .:/experiment -w /experiment --entrypoint /bin/bash ${MAIN_NAME}

clean:
	rm -rf bin/sample_CheckProcessDebugPort_*.exe
