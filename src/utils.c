#include "../include/utils.h"
#include <ctype.h>

BOOL is_letter(char ch) {
  if (isalpha(ch) || ch == '_') {
    return TRUE;
  }
  return FALSE;
}

BOOL is_number(char ch) { return isdigit(ch) ? TRUE : FALSE; }
