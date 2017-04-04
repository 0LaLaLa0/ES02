//
// Created by eric on 31.03.17.
//

#include "../include/Printf.h"
#include <stdarg.h>

char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

char *intToBaseString(char *destination, const void *end, unsigned int value)
{
	if (destination > end) return destination;

	if (destination == end) {   // Return if we are at the end
		*destination = 0;
		return destination;
	}

	char digit = digits[value % 10];    //get char from array "digits"
	value = value / 10;                 //shift the value by the amount of base

	//recursion if the there are still digits left
	if (value) {
		destination = intToBaseString(destination, end, value);
		if (!destination) return nullptr;
		if (destination < end) destination++;
		if (destination == end) {   // Return, if we are at the end
			*destination = 0;
			return destination;
		}
	}
	*destination = digit;   // Write digits into destination
	return destination;     //increase and return the pointer
}

char *intToBaseString(char *destination, const void *end, int value, unsigned int base, bool prefix)
{
	if (destination > end) return destination;

	if (destination == end) {   // Return if we are at the end
		*destination = 0;
		return destination;
	}

	if (value < 0) {    // Minus for negative number
		*destination = '-';
		destination++;
		value = 0 - value;
	}

	if (prefix && destination < end) {  // Write prefixes for binary and hex
		if (2 == base) {
			*destination++ = '0';
			*destination++ = 'b';
		}
		if (16 == base) {
			*destination++ = '0';
			*destination++ = 'x';
		}
	}

	if (destination == end) {   // If we are at the end, return destination
		*destination = 0;
		return destination;
	}

	char digit = digits[value % base];    //get char from array "digits"
	value = value / base;                 //shift the value by the amount of base

	//recursion if the there are still digits left
	if (value && destination < end) {
		destination = intToBaseString(destination, end, value, base, false);
		if (!destination) return nullptr;
		if (destination < end)
			destination++;
		if (destination == end) {   // Return if we are at the end
			*destination = 0;
			return destination;
		}
	}
	*destination = digit;   //write the digit
	return destination;    //increase and return the pointer
}

char *Printf(char *destination, const void *end, const char *formatstring, ...)
{
	const char *format;
	va_list argp;
	int i;
	unsigned int ui;
	char *s;

	va_start(argp, formatstring);

	if(*formatstring == 0){
		*destination = 0;
		return destination;
	}

	for (format = formatstring; *format != '\0' && destination < end; format++) {
		if (*format != '%') {
			*destination = *format;
			destination++;
			if (destination == end) {
				*destination = 0;
				return destination;
			}
			continue;
		}

		switch (*++format) {
		case 'c':
			i = va_arg(argp, int);
			*destination++ = i;
			if (destination == end) {   // Return if we are at the end
				*destination = 0;
				return destination;
			}
			break;

		case 'd':
			i = va_arg(argp, int);
			destination = intToBaseString(destination, end, i, 10, false);
			if (destination == end) {   // Return if we are at the end
				*destination = 0;
				return destination;
			}
			destination++;
			break;

		case 'u':
			ui = va_arg(argp, unsigned
					int);
			destination = intToBaseString(destination, end, ui);
			if (destination == end) {   // Return if we are at the end
				*destination = 0;
				return destination;
			}
			destination++;
			break;

		case 's':
			s = va_arg(argp, char *);
			while (*s && destination < end) {
				*destination = *s;
				s++;
				destination++;
			}
			if (destination == end) {   // Return if we are at the end
				*destination = 0;
				return destination;
			}
			break;

		case 'x':
			i = va_arg(argp, int);
			destination = intToBaseString(destination, end, i, 16, true);
			if (destination == end) {   // Return if we are at the end
				*destination = 0;
				return destination;
			}
			break;

		case 'b':
			i = va_arg(argp, int);
			destination = intToBaseString(destination, end, i, 2, true);
			if (destination == end) {   // Return if we are at the end
				*destination = 0;
				return destination;
			}
			break;

		case '%':
			*destination++ = '%';
			if (destination == end) {   // Return if we are at the end
				*destination = 0;
				return destination;
			}
			break;

		default:
			*destination++ = '%';

			if (destination == end) {   // Return if we are at the end
				*destination = 0;
				return destination;
			}

			*destination++ = *format;
			if (destination == end) {   // Return if we are at the end
				*destination = 0;
				return destination;
			}
		}
		if (destination && destination < end) {
			*destination = 0;
		}
	}
	va_end(argp);
	return destination;
}