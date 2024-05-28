#include "display/display.h"

#include <stdint.h>

#include "io/hal.h"
#include "types.h"

struct _display display = {
	.x = 0,
	.y = 0};

int display_get_y() {
	return display.y;
}

int display_get_x() {
	return display.x;
}

void display_clear_row(int y) {
	for (int x = 0; x < VGA_WIDTH; ++x) {
		display_putch(0, 0, 0, x, y);
	}

	display.x = 0;
}

void display_clear(int x, int y) {
	if (x == VGA_WIDTH && y == VGA_HEIGHT) {
		display.x = 0;
		display.y = 0;

		return;
	}

	display_putch(0, 0, 0, x, y);

	if (x == VGA_WIDTH) {
		display_clear(0, y + 1);
	} else {
		display_clear(x + 1, y);
	};
}

void display_disable_cursor() {
	io_write8(0x3D4, 0x0A);
	io_write8(0x3D5, 0x20);
}

void display_enable_cursor() {
	uint16_t pos = display.y * VGA_WIDTH + display.x;

	io_write8(0x3D4, 0x0A);
	io_write8(0x3D5, (uint8_t)(pos & 0xFF));

	io_write8(0x3D4, 0x0B);
	io_write8(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void display_init() {
	display_disable_cursor();
	display_clear(0, 0);
}

void display_update_cursor(int x, int y) {
	uint16_t pos = y * VGA_WIDTH + x;

	io_write8(0x3D4, 0x0F);
	io_write8(0x3D5, (uint8_t)(pos & 0xFF));
	io_write8(0x3D4, 0x0E);
	io_write8(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void display_putch(unsigned char c, unsigned char forecolour, unsigned char backcolour, int x, int y) {
	uint16_t attrib = (backcolour << 4) | (forecolour & 0x0F);
	volatile uint16_t *where = (volatile uint16_t *)0xB8000 + (y * VGA_WIDTH + x);

	*where = c | (attrib << 8);
}

void display_write_string(const char *string, int color) {
	while (*string != 0) {
		char ch = *string++;

		if (ch == '\n') {
			display.y += 1;
			display.x = 0;

			display_putch(0, 0, 0, display.x, display.y);
			continue;
		}

		display_putch(ch, color, 0, display.x, display.y);
		display.x += 1;
	}
}

void putch(unsigned char c) {
	if (display.y >= VGA_HEIGHT) {
		display.y = 0;
		display_clear(0, 0);
	}

	if (c == '\n') {
		display.y += 1;
		display.x = 0;
		display_update_cursor(display.x, display.y);
		return;
	}

	display.x += 1;

	display_putch(c, 15, 0, display.x, display.y);
	display_update_cursor(display.x, display.y);
}