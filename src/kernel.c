#include "stdio.h"

#include "display/display.h"
#include "drivers/rtc.h"
#include "drivers/keyboard.h"

#include "fs/ramfs.h"

#include "shell.h"

void test_rfs() {
	printf("[RAMFS] Trying to create files...\n");

	int test_1_ret = rfs_create("TEST_1", "TEST_1_CONTENT");
	int test_2_ret = rfs_create("TEST_2", "TEST_2_CONTENT");

	if (test_1_ret == RFS_OK) {
		printf("[RAMFS] TEST_1: OK\n");
	} else printf("[RAMFS] TEST_1: ERROR, %d\n", test_1_ret);
	if (test_2_ret == RFS_OK) {
		printf("[RAMFS] TEST_2: OK\n");
	} else printf("[RAMFS] TEST_2: ERROR, %d\n", test_2_ret);

	printf("[RAMFS] Files count: %d\n", rfs_count());
}

void kernel_main(void) {
	display_init();
	
	display_write_string("--------------------\n", D_LIGHT_GREEN);

	rtc_date();

	test_rfs();

	display_write_string("+ Done!\n", D_LIGHT_GREEN);
	display_enable_cursor();

	shell_loop();
}