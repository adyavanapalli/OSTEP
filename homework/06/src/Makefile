CC=gcc
CCFLAGS=-Wall -Wextra -Wpedantic
BUILD_DIR=mkdir -p ../build

all: main
main:
	$(BUILD_DIR) && $(CC) $(CCFLAGS) main.c -o ../build/main
clean:
	rm -rf ../build
