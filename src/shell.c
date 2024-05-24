#include "shell.h"

#include "stdio.h"
#include "string.h"
#include "memory.h"
#include "display/display.h"
#include "drivers/keyboard.h"
#include "drivers/rtc.h"

#define COMMAND_MAX_SIZE 512

int _shell_command_clear() {
    display_clear(0, 0);

    return 0;
}

int _shell_command_time() {
    rtc_date();

    return 0;
}

int _shell_command_echo(int argc, char* argv) {
    printf("ARGC: %d\n", argc);
    printf("ARGV: %s\n", argv);

    return 0;
}

char* _shell_get_command(char* command, int len) {
    if (len <= 0) return "";

    char* ret = 0;
    int ret_len = 0;

    for (int i = 0; i < len; ++i) {
        if (command[i] == ' ') break;

        ret[i] = command[i];
        ret_len += 1;
    }

    ret[ret_len] = '\0';

    return ret;
}

void shell_loop() {
    int argc = 1;
    char command[COMMAND_MAX_SIZE];
    char c = 0;

    int cmd_len = 0;

    printf("Welcome to %s\n", "shell");

    printf("$ ");
    
    while (1) {
		c = keyboard_get_key();

        if (c == KEY_ENTER) {
            char* command_name = _shell_get_command(command, cmd_len);

            printf("\nRun command: %s\n", command_name);

            if (strcmp(command_name, "clear") == 0) {
                _shell_command_clear();
            } else if (strcmp(command_name, "date") == 0) {
                _shell_command_time();
            } else if (strcmp(command_name, "echo") == 0) {
                _shell_command_echo(argc, command);
            } 

            memset(&command, 0, COMMAND_MAX_SIZE);
            c = 0;
            cmd_len = 0;
            argc = 1;

            printf("\n$ ");

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
            printf("$ %s", command);

            continue;
        }

		if (c > 0) {
            if (c == KEY_SPACE) argc += 1;

			putch(keyboard_key2ascii(c));
            command[cmd_len] = keyboard_key2ascii(c);
			c = 0;
            cmd_len += 1;
			continue;
		}
    }
}