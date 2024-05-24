build:
	as --32 ./src/boot.asm -o ./bin/boot.o
	
	gcc -m32 -c -I ./include ./src/stdio.c -o ./bin/stdio.o -std=c99 -ffreestanding -O2 -Wall -Wextra
	gcc -m32 -c -I ./include ./src/string.c -o ./bin/string.o -std=c99 -ffreestanding -O2 -Wall -Wextra
	gcc -m32 -c -I ./include ./src/stdlib.c -o ./bin/stdlib.o -std=c99 -ffreestanding -O2 -Wall -Wextra
	gcc -m32 -c -I ./include ./src/memory.c -o ./bin/memory.o -std=c99 -ffreestanding -O2 -Wall -Wextra

	gcc -m32 -c -I ./include ./src/kernel.c -o ./bin/kernel.o -std=c99 -ffreestanding -O2 -Wall -Wextra

	gcc -m32 -c -I ./include ./src/shell.c -o ./bin/shell.o -std=c99 -ffreestanding -O2 -Wall -Wextra

	gcc -m32 -c -I ./include ./src/display/display.c -o ./bin/display_vga.o -std=c99 -ffreestanding -O2 -Wall -Wextra

	gcc -m32 -c -I ./include ./src/io/hal.c -o ./bin/io_hal.o -std=c99 -ffreestanding -O2 -Wall -Wextra

	gcc -m32 -c -I ./include ./src/drivers/keyboard.c -o ./bin/keyboard.o -std=c99 -ffreestanding -O2 -Wall -Wextra
	gcc -m32 -c -I ./include ./src/drivers/rtc.c -o ./bin/rtc.o -std=c99 -ffreestanding -O2 -Wall -Wextra

	ld -m elf_i386 -T link.ld -o ./bin/kernel.bin ./bin/boot.o ./bin/stdlib.o ./bin/stdio.o ./bin/memory.o ./bin/string.o \
		./bin/display_vga.o ./bin/io_hal.o ./bin/keyboard.o ./bin/rtc.o ./bin/kernel.o ./bin/shell.o

run:
	qemu-system-i386 -kernel ./bin/kernel.bin

clean:
	rm ./bin/*