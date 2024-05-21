#include "display/display.h"

#include <stdint.h>

#include "types.h"
#include "io/hal.h"

struct _display display = {
	.x = 0,
	.y = 0,
	.lines = 0
};

void display_disable_cursor() {

	io_write8(0x3D4, 0x0A);
	io_write8(0x3D5, 0x20);
}

void display_enable_cursor() {
	io_write8(0x3D4, 0x0A);
	io_write8(0x3D5, (io_read8(0x3D5) & 0xC0) | display.x);
 
	io_write8(0x3D4, 0x0B);
	io_write8(0x3D5, (io_read8(0x3D5) & 0xE0) | display.y);
}

void display_init() {
	display_disable_cursor();

    volatile char* video = (volatile char*)0xB8000;

    for (int i = 0; i < VGA_WIDTH; ++i) {
        *video++ = 0;

        for (int j = 0; j < VGA_HEIGHT; ++j) {
            *video++ = 0;
        }
    }
}

void display_update_cursor(int x, int y) {
	uint16_t pos = y * VGA_WIDTH + x;
 
	io_write8(0x3D4, 0x0F);
	io_write8(0x3D5, (uint8_t) (pos & 0xFF));
	io_write8(0x3D4, 0x0E);
	io_write8(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void display_putch(unsigned char c, unsigned char forecolour, unsigned char backcolour, int x, int y) {
	uint16_t attrib = (backcolour << 4) | (forecolour & 0x0F);
	volatile uint16_t* where = (volatile uint16_t *)0xB8000 + (y * VGA_WIDTH + x);
	
	*where = c | (attrib << 8);

	display_update_cursor(x, y);
}

void display_write_string(const char* string, int color) {
    while (*string != 0) {
		char ch = *string++;

		if (ch == '\n') {
			display.lines += 1;
			display.y += 1;
			display.x = 0;

			continue;
		}

		display_putch(ch, color, 0, display.x, display.y);
		display.x += 1;
    }
}

void putch(unsigned char c) {
	if (c == '\n') {
		display.lines += 1;
		display.y += 1;
		display.x = 0;
		return;
	}

	display_putch(c, 14, 0, display.x, display.y);

	display.x += 1;
}