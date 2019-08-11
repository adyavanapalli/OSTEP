CC=gcc
CCFLAGS=-Wall -Wextra -Wpedantic
BUILD_DIR=mkdir -p ../bin

all: time_system_call time_context_switch
time_system_call:
	$(BUILD_DIR) && $(CC) $(CCFLAGS) time_system_call.c -o ../bin/time_system_call
time_context_switch:
	$(BUILD_DIR) && $(CC) $(CCFLAGS) time_context_switch.c -o ../bin/time_context_switch
clean:
	rm -rf ../bin
