CC=gcc
CCFLAGS=-Wall -Wextra -Wpedantic
BUILD_DIR=mkdir -p ../build

all: 1.out 2.out
1.out:
	$(BUILD_DIR) && $(CC) $(CCFLAGS) 1.c -o ../build/1.out
2.out:
	$(BUILD_DIR) && $(CC) $(CCFLAGS) 2.c -o ../build/2.out
clean:
	rm -rf ../build
