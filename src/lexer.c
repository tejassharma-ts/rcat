#include "../include/lexer.h"
#include "../include/token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TokenList *tail_ptr = NULL;
TokenList *ll_head = NULL;

void init(char *input) {
  Lexer l = {input, -1, 0, 0};
  Token tok;

  read_char(&l);

  while ((tok = next_token(&l)).type != EOF) {
    if (tok.type == ILLEGAL) {
      printf("%s\n", tok.literal);
      fprintf(stderr, "ILLEGAL token detected");
      exit(1);
    }

    store_token(&tail_ptr, tok);
  }
}

void read_char(Lexer *l) {
  l->curr_position = l->peek;
  l->peek++;
  if (l->curr_position >= (int)strlen(l->input)) {
    l->ch = 0;
  } else {
    l->ch = l->input[l->curr_position];
  }
};

void skip_whitespaces(Lexer *l) {
  while (l->ch == ' ' || l->ch == '\n' || l->ch == '\t' || l->ch == '\r') {
    read_char(l);
  }
}
