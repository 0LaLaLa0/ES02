//
// Created by eric on 31.03.17.
//

#include "../include/Printf.h"
#include <stdarg.h>
#include <cstdio>

char digits[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

char *intToBaseString(char *destination, const void *end, unsigned int value) {
    if (destination >= end) return nullptr;

    char digit = digits[value % 10];    //get char from array "digits"
    value = value / 10;                 //shift the value by the amount of base

    //recursion if the there are still digits left
    if (value) {
        destination = intToBaseString(destination, end, value);
        destination++;
    }

    *destination = digit;    //write the digit
    return destination;    //increase and return the pointer
}

char *intToBaseString(char *destination, const void *end, int value, unsigned int base, bool prefix) {
    if (destination >= end) return nullptr;

    if (value < 0) {
        *destination = '-';
        destination++;
        value = 0 - value;
    }

    if (prefix && destination + 2) {
        if (2 == base) {
            *destination++ = '0';
            *destination++ = 'b';
        }
        if (16 == base) {
            *destination++ = '0';
            *destination++ = 'x';
        }
    }


    if (destination >= end) return nullptr;

    char digit = digits[value % base];    //get char from array "digits"
    value = value / base;                 //shift the value by the amount of base

    //recursion if the there are still digits left
    if (value && destination < end) {
        destination = intToBaseString(destination, end, value, base, false);
        destination++;
    }
    if (destination) *destination = digit;    //write the digit
    return destination;    //increase and return the pointer
}

char *Printf(char *destination, const void *end, const char *formatstring, ...) {
    const char *format;
    va_list argp;
    int i;
    unsigned int ui;
    char *s;

    va_start(argp, formatstring);

    for (format = formatstring; *format != '\0' && format < end; format++) {
        if (*format != '%') {
            *destination = *format;
            destination++;
            continue;
        }

        switch (*++format) {
            case 'c':
                i = va_arg(argp, int);
                *destination = i;
                break;

            case 'd':
                i = va_arg(argp, int);
                destination = intToBaseString(destination, end, i, 10, false);
                destination++;
                break;

            case 'u':
                ui = va_arg(argp, unsigned
                        int);
                destination = intToBaseString(destination, end, ui, 10, false);
                destination++;
                break;

            case 's':
                s = va_arg(argp, char *);
                while (*s && destination < end) {
                    *destination = *s;
                    s++;
                    destination++;
                }
                break;

            case 'x':
                i = va_arg(argp, int);
                destination = intToBaseString(destination, end, i, 16, true);
                break;

            case 'b':
                i = va_arg(argp, int);
                destination = intToBaseString(destination, end, i, 2, true);
                break;

            case '%':
                *destination = '%';
                break;

            default:
                *destination = *format;
        }
        if (destination < end) {
            *++destination = 0;
        }
    }

    va_end(argp);

    return destination;
}