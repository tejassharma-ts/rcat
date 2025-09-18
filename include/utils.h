#ifndef UTILS_H
#define UTILS_H

#include <ctype.h>

typedef enum { TRUE = 1, FALSE = 0 } BOOL;

BOOL is_letter(char ch);

BOOL is_number(char ch);

#endif // !UTILS_H
