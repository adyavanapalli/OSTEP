CC=gcc
CCFLAGS=-Wall -Wextra -Wpedantic
BUILD_DIR=mkdir -p ../bin

all: main
main:
	$(BUILD_DIR) && $(CC) $(CCFLAGS) time_system_call.c -o ../bin/time_system_call
clean:
	rm -rf ../bin
