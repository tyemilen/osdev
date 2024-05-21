#include "stdio.h"

#include "stdlib.h"
#include <stdarg.h>

#include "display/display.h"

int printf(char *msg, ...)
{
	char curchar = *msg;
	char *ch = 0;
	char *str;

	va_list args;
	va_start(args, msg);

	while (curchar != '\0') {
		if (curchar >= ' ' && curchar != '%') {
			putch(curchar);
		} else if (curchar == '%') {
			++msg;
			curchar = *msg;
			if (curchar == '%') {
				putch('%');
			} else {
				switch (curchar) {
				case 'c':
					*ch = (unsigned char)va_arg(args, int);
					putch(*ch);

					break;

				case 's':
					str = va_arg(args, char *);
					printf(str);

					break;

				case 'd':
					char* number = 0;

					int d = va_arg(args, int);
					
					itoa(d, number, 10);

					printf(number);
					break;

				default:
					putch('%');
					break;
				}
			}
		} else if (curchar == 0x08 || curchar == 0x09 || curchar == '\r' || curchar == '\n') {
			putch(curchar);
		}

		++msg;
		curchar = *msg;
	}

	va_end(args);

	return 0;
}