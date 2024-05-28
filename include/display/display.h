#ifndef VGA_H_
#define VGA_H_

#include "colors.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

struct _display {
	int x;
	int y;
};

void display_clear(int x, int y);
void display_clear_row(int y);

int display_get_y();
int display_get_x();

void display_enable_cursor();
void display_disable_cursor();

void display_init();
void display_update_cursor(int x, int y);
void display_putch(unsigned char c, unsigned char forecolour, unsigned char backcolour, int x, int y);
void display_write_string(const char *string, int color);

void putch(unsigned char c);

#endif /* VGA_H_ */