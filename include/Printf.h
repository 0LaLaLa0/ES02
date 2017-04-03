//
// Created by eric on 31.03.17.
//

#ifndef ES02_PRINT_H
#define ES02_PRINT_H

char *Printf(char *dst, const void *end, const char *formatstring, ...);
char *intToBaseString(char *destination, const void *end, int value, unsigned int base, bool prefix);

#endif //ES02_PRINT_H
