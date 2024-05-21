#include "drivers/keyboard.h"

#include "stdio.h"
#include "io/hal.h"

const char keycode[] = {
	0, 0, '1', '2',
	'3', '4', '5', '6',
	'7', '8', '9', '0',
	'-', '=', 0, 0,
	'q', 'w', 'e', 'r',
	't', 'y', 'u', 'i',
	'o', 'p', '[', ']',
	0, 0, 'a', 's',
	'd', 'f', 'g', 'h',
	'j', 'k', 'l', ';',
	'\'', '`', 0, '\\',
	'z', 'x', 'c', 'v',
	'b', 'n', 'm', ',',
	'.', '/', 0, '*',
	0, ' '
};

char keyboard_get_key() {
    unsigned char scancode = io_read8(0x60);

    if (scancode & 0x80) {
		return 0;
    } else {
		io_write8(0x60, 3);
		return keycode[scancode];
    }
}