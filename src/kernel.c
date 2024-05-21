#include "drivers/rtc.h"
#include "drivers/keyboard.h"
#include "display/display.h"
#include "io/hal.h"
#include "stdio.h"

void kernel_main(void) {
	display_init();
	
	display_write_string("--------------------\n", 10);

	rtc_init();

	display_write_string("+ Done!\n", 10);
	display_enable_cursor();

	char c = 0;

	while (1) {
		c = keyboard_get_key();

		if (c > 0) {
			putch(c);
			c = 0;
			continue;
		}
	}
}