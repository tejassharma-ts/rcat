#include "../include/lexer.h"
#include "../include/utils.h"
#include "../include/token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *FILE_PATH = "./example";

typedef struct LexerObj {
  Lexer data;
  struct LexerObj *next;
} LexerObj;

int main(int argc, char *argv[]) {
  size_t read;
  char *line = NULL;
  size_t len = 0;
  char **tokens;

  if (argc < 2) {
    fprintf(stderr, "Usage: rcat [file]\n");
    exit(0);
  }

  char *file_name;
  if (argv[1]) {
    file_name = argv[1];
  } else {
    file_name = FILE_PATH;
  }

  FILE *file = fopen(file_name, "r");
  if (file == NULL) {
    fprintf(stderr, "Failed to open the file");
    exit(0);
  }

  char ch;
  int i = 0;

  TokenList *p;

  while ((read = getline(&line, &len, file)) != -1) {
    // create token from the current line
    init(line);
  }


  // print all the tokens
  while (ll_head) {
    printf("type: %s, literal %s\n", getTokenTypeName(ll_head->data.type), ll_head->data.literal);
    p = ll_head;
    ll_head = ll_head->next;
    free(p->data.literal);
    free(p);
  }

  free(line);

  return 0;
}
