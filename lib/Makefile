CFLAGS=-Wno-builtin-declaration-mismatch
BITS=64 # change during make

TARGET=../lib.s

.PHONY: lib
lib: lib.c
	$(CC) $(CFLAGS) -DBITS=$(BITS) lib.c -S -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)
