#include "shell.h"

#include "display/display.h"
#include "drivers/keyboard.h"
#include "drivers/rtc.h"
#include "fs/ramfs.h"
#include "io/hal.h"
#include "memory.h"
#include "stdio.h"
#include "string.h"

#define COMMAND_MAX_SIZE 512

int _shell_command_getdisplay() {
	printf("X: %d, Y: %d\n", display_get_x(), display_get_y());

	return 0;
}

int _shell_command_clear() {
	display_clear(0, 0);

	return 0;
}

int _shell_command_time() {
	rtc_date();

	return 0;
}

int _shell_command_echo(int argc, char *argv) {
	printf("ARGC: %d\n", argc);
	printf("ARGV: %s\n", argv);

	return 0;
}

char *_shell_get_command(char *command, int len) {
	if (len <= 0)
		return "";

	char *ret = 0;
	int ret_len = 0;

	for (int i = 0; i < len; ++i) {
		if (command[i] == ' ')
			break;

		ret[i] = command[i];
		ret_len += 1;
	}

	ret[ret_len] = '\0';

	return ret;
}

// rfs commands
int _shell_command_ls() {
	struct st_ramfs_entry* files = rfs_list();

	for (int i = 0; i < rfs_count(); ++i) {
		printf("%s ", files[i].name);
	}
	putch('\n');

	return 0;
}

int _shell_command_read(char* name) {
	struct st_ramfs_entry file = { 0 };

	int ret = rfs_read(name, &file);

	if (ret == RFS_FILE_NOT_EXISTS) {
		printf("File doesnt exists\n");
		return -1;
	}

	printf("%s\n", file.content);
	printf("\n-- EOF --\n");

	return 0;
}
//
void shell_loop() {
	char command[COMMAND_MAX_SIZE];
	char c = 0;

	int cmd_len = 0;
	int argc = 1;

	printf("Welcome to shell\n");

	display_write_string("shell>", D_LIGHT_CYAN);

	while (1) {
		c = keyboard_get_key();

		if (c == KEY_ENTER) {
			command[cmd_len] = '\0';

			char *command_name = _shell_get_command(command, cmd_len);

			putch('\n');
			if (strcmp(command_name, "clear") == 0) {
				_shell_command_clear();
			} else if (strcmp(command_name, "date") == 0) {
				_shell_command_time();
			} else if (strcmp(command_name, "echo") == 0) {
				_shell_command_echo(argc, command);
			} else if (strcmp(command_name, "display") == 0) {
				_shell_command_getdisplay();
			} else if (strcmp(command_name, "ls") == 0) {
				_shell_command_ls();
			} else if (strcmp(command_name, "read") == 0) {
				_shell_command_read("TEST_1");
			}

			memset(&command, 0, COMMAND_MAX_SIZE);
			c = 0;
			cmd_len = 0;

			display_write_string("shell>", D_LIGHT_CYAN);

			continue;
		}

		if (c == KEY_BACKSPACE) {
			if (cmd_len == 0) {
				continue;
			}

			cmd_len -= 1;

			if (command[cmd_len] == ' ') {
				argc -= 1;
			}

			command[cmd_len] = 0;

			display_clear_row(display_get_y());

			display_write_string("shell>", D_LIGHT_CYAN);
			printf("%s", command);

			continue;
		}

		if (c > 0) {
			putch(keyboard_key2ascii(c));

			command[cmd_len] = keyboard_key2ascii(c);
			c = 0;
			cmd_len += 1;
			continue;
		}
	}
}