CC=gcc
CCFLAGS=-Wall -Wextra -Wpedantic
BUILD_DIR=mkdir -p ../bin

all: main
main:
	$(BUILD_DIR) && $(CC) $(CCFLAGS) main.c -o ../bin/main
clean:
	rm -rf ../bin
