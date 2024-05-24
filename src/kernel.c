#include "drivers/rtc.h"
#include "drivers/keyboard.h"
#include "display/display.h"
#include "io/hal.h"
#include "stdio.h"

#include "shell.h"

void kernel_main(void) {
	display_init();
	
	display_write_string("--------------------\n", 10);

	rtc_date();

	display_write_string("+ Done!\n", 10);
	display_enable_cursor();

	shell_loop();
}