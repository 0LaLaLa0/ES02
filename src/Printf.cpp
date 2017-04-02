//
// Created by eric on 31.03.17.
//

#include "../include/Printf.h"
#include <stdarg.h>
#include <cstdio>

char hex[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

extern char *itoa(int, char *, int);

void integer_to_bin(int integer, char *string)
{
	// Write 0b
	int index = 0;
	string[index++] = '0';
	string[index++] = 'b';
	int temp = integer;

	while (temp > 0) {
		temp /= 2;
		index++;
	}
	while (integer > 0) {
		string[index--] = static_cast<char>(integer % 2);
		integer /= 2;
	}
}

void integer_to_hex(int integer, char string[])
{
	// Write 0x
	int index = 0;
	string[index++] = '0';
	string[index++] = 'x';
	int temp = integer;

	while (temp > 0) {
		temp /= 16;
		index++;
	}

	while (integer > 0) {
		string[index--] = hex[(integer % 16)];
		integer /= 16;
	}
}

void integer_to_dec(int integer, char *string)
{
	int index = 0;
	int temp = integer;

	while (temp > 0) {
		temp /= 10;
		index++;
	}

	while (integer > 0) {
		string[index--] = static_cast<char>(integer % 10);
		integer /= 10;
	}
}

char *Printf(char *destination, const void *end, const char *formatstring, ...)
{
	const char *format;
	va_list argp;
	int i;
	char *s;
	char fmtbuf[256];

	va_start(argp, formatstring);

	for (format = formatstring; *format != '\0' && format != end; format++) {
		if (*format != '%') {
			putchar(*format);
			continue;
		}

		switch (*++format) {
		case 'c':
			i = va_arg(argp, int);
			putchar(i);
			break;

		case 'd':
			i = va_arg(argp, int);
			integer_to_dec(i, destination);
			fputs(s, stdout);
			break;

		case 's':
			s = va_arg(argp, char *);
			fputs(s, stdout);
			break;

		case 'x':
			i = va_arg(argp, int);
			s = itoa(i, fmtbuf, 16);
			fputs(s, stdout);
			break;

		case '%':
			putchar('%');
			break;
		}
	}

	va_end(argp);

	return destination;
}