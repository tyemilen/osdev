CC = gcc
AS = as
CFLAGS = -m32 -c -I./include -std=c99 -fno-stack-protector -ffreestanding -O2 -Wall -Wextra

build:
	$(AS) --32 ./src/boot.asm -o ./bin/boot.o
	
	$(CC) $(CFLAGS) ./src/stdio.c -o ./bin/stdio.o
	$(CC) $(CFLAGS) ./src/string.c -o ./bin/string.o
	$(CC) $(CFLAGS) ./src/stdlib.c -o ./bin/stdlib.o
	$(CC) $(CFLAGS) ./src/memory.c -o ./bin/memory.o

	$(CC) $(CFLAGS) ./src/kernel.c -o ./bin/kernel.o
	$(CC) $(CFLAGS) ./src/shell.c -o ./bin/shell.o

	$(CC) $(CFLAGS) ./src/display/display.c -o ./bin/display_vga.o

	$(CC) $(CFLAGS) ./src/io/hal.c -o ./bin/io_hal.o

	$(CC) $(CFLAGS) ./src/drivers/keyboard.c -o ./bin/keyboard.o
	$(CC) $(CFLAGS) ./src/drivers/rtc.c -o ./bin/rtc.o

	$(CC) $(CFLAGS) ./src/fs/ramfs.c -o ./bin/ramfs.o

	ld -m elf_i386 -T link.ld -o ./bin/kernel.bin ./bin/boot.o ./bin/stdlib.o ./bin/stdio.o ./bin/memory.o ./bin/string.o \
		./bin/display_vga.o ./bin/io_hal.o ./bin/keyboard.o ./bin/rtc.o ./bin/kernel.o ./bin/shell.o ./bin/ramfs.o

test:
	$(CC) ./test/args.c -o ./test/args.out
	./test/args.out

run:
	qemu-system-i386 -kernel ./bin/kernel.bin

clean:
	rm ./bin/*