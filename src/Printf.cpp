//
// Created by eric on 31.03.17.
//

#include "../include/Printf.h"
#include <stdarg.h>
#include <cstdio>

char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
char dec[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
char bin[] = {'0', '1'};


char *intToBaseString(char *destination, const void *end, int value, unsigned int base, bool prefix) {
    if (destination >= end) return nullptr;

    if (value < 0) {
        *destination = '-';
        destination++;
        value = 0 - value;
    }

    if (prefix) {
        if (2 == base) {
            *destination = '0';
            destination++;
            *destination = 'b';
            destination++;
        }
        if(16 == base){
            *destination = '0';
            destination++;
            *destination = 'x';
            destination++;
        }
    }


    if (destination >= end) return nullptr;

    char digit = digits[value % base];    //get char from array "digits"
    value = value / base;                 //shift the value by the amount of base

    //recursion if the there are still digits left
    if (value) {
        destination = intToBaseString(destination, end, value, base, false);
        destination++;
    }

    *destination = digit;    //write the digit
    return destination;    //increase and return the pointer
}

char *Printf(char *destination, const void *end, const char *formatstring, ...) {
    const char *format;
    va_list argp;
    int i;
    char *s;
    //char fmtbuf[256];

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
                intToBaseString(destination, end, i, 10, false);
                fputs(s, stdout);
                break;

            case 's':
                s = va_arg(argp, char *);
                fputs(s, stdout);
                break;

            case 'x':
                i = va_arg(argp, int);
//			s = itoa(i, fmtbuf, 16);
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