CC=gcc
CCFLAGS=-Wall -Wextra -Wpedantic
BUILD_DIR=mkdir -p ../bin
OUT=1.out 2.out 3.out 4.out 5.out 6.out 7.out 8.out

all: $(OUT)
1.out:
	$(BUILD_DIR) && $(CC) $(CCFLAGS) 1.c -o ../bin/1.out
2.out:
	$(BUILD_DIR) && $(CC) $(CCFLAGS) 2.c -o ../bin/2.out
3.out:
	$(BUILD_DIR) && $(CC) $(CCFLAGS) 3.c -o ../bin/3.out
4.out:
	$(BUILD_DIR) && $(CC) $(CCFLAGS) 4.c -o ../bin/4.out
5.out:
	$(BUILD_DIR) && $(CC) $(CCFLAGS) 5.c -o ../bin/5.out
6.out:
	$(BUILD_DIR) && $(CC) $(CCFLAGS) 6.c -o ../bin/6.out
7.out:
	$(BUILD_DIR) && $(CC) $(CCFLAGS) 7.c -o ../bin/7.out
8.out:
	$(BUILD_DIR) && $(CC) $(CCFLAGS) 8.c -o ../bin/8.out
clean:
	rm -rf ../bin
