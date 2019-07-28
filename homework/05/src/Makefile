CC=gcc
CCFLAGS=-Wall -Wextra -Wpedantic
BUILD_DIR=mkdir -p ../build
OUT=1.out 2.out 3.out 4.out 5.out

all: $(OUT)
1.out:
	$(BUILD_DIR) && $(CC) $(CCFLAGS) 1.c -o ../build/1.out
2.out:
	$(BUILD_DIR) && $(CC) $(CCFLAGS) 2.c -o ../build/2.out
3.out:
	$(BUILD_DIR) && $(CC) $(CCFLAGS) 3.c -o ../build/3.out
4.out:
	$(BUILD_DIR) && $(CC) $(CCFLAGS) 4.c -o ../build/4.out
5.out:
	$(BUILD_DIR) && $(CC) $(CCFLAGS) 5.c -o ../build/5.out
clean:
	rm -rf ../build
