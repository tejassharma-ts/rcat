#include "../include/token.h"
#include "../include/utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Token next_token(Lexer *l) {
  Token tok = {0, ""};

  skip_whitespaces(l);
  switch (l->ch) {
  case '+':
    tok = create_token(PLUS, l->ch);
    break;
  case '=':
    tok = create_token(ASSIGN, l->ch);
    break;
  case ';':
    tok = create_token(SEMICOLON, l->ch);
    break;
  case '(':
    tok = create_token(LPAREN, l->ch);
    break;
  case ')':
    tok = create_token(RPAREN, l->ch);
    break;
  case '{':
    tok = create_token(LBRACE, l->ch);
    break;
  case '}':
    tok = create_token(RBRACE, l->ch);
    break;
  case '\0':
    tok = create_token(EOF, l->ch);
    break;
  default:
    // handle other characters
    if (is_letter(l->ch)) {
      char stored_bytes[256];
      memset(&stored_bytes, '\0', sizeof(stored_bytes));

      // if letter is encounter we need to go on until we hit non-letter
      // character
      read_bytes(l, stored_bytes);

      tok.literal = (char *)malloc(strlen(stored_bytes) + 1);
      strcpy(tok.literal, stored_bytes);
      tok.literal[strlen(tok.literal)] = '\0';

      // but the token type could also be a keyword?
      tok.type = IDENT;
      return tok;
    } else if (is_number(l->ch)) {
      tok = create_token(INT, l->ch);

    } else {
      printf("what the fuck?\n");
      tok = create_token(ILLEGAL, '\0');
    }
  }
  read_char(l);

  return tok;
}

// curr_node_pointer is a tail pointer in a linked list
// the head pointer however will be a global variable
void store_token(TokenList **curr_node_pointer, Token tok) {
  // create new node
  TokenList *new_node = (TokenList *)malloc(sizeof(TokenList));
  new_node->data = tok;
  new_node->next = NULL;

  if (ll_head == NULL) {
    // set tail pointer to new node
    *curr_node_pointer = new_node;

    // initialize head of linked list
    ll_head = new_node;
    return;
  }
  // update tail pointer
  (*curr_node_pointer)->next = new_node;
  *curr_node_pointer = new_node;
}

Token create_token(TOKEN_TYPE type, char byte) {
  Token tok;
  char str[2];
  str[1] = '\0';
  str[0] = byte;

  char *str_ptr = (char *)malloc(sizeof(char) * strlen(str));
  strcpy(str_ptr, str);

  tok.type = type;
  tok.literal = str_ptr;
  return tok;
}

void read_bytes(Lexer *l, char *stored_bytes) {
  int position = l->curr_position;
  while (is_letter(l->ch)) {
    read_char(l);
  }

  int i = 0;
  while (position < l->curr_position) {
    stored_bytes[i++] = l->input[position];
    position++;
  }
  stored_bytes[i] = '\0';
}

char *getTokenTypeName(TOKEN_TYPE type) {
  switch (type) {
  case ILLEGAL:
    return "ILLEGAL";
  case EOF:
    return "EOF";

  // Identifiers + literals
  case IDENT:
    return "IDENT";
  case INT:
    return "INT";

  // Operators
  case ASSIGN:
    return "ASSIGN";
  case PLUS:
    return "PLUS";

  // Delimiters
  case COMMA:
    return "COMMA";
  case SEMICOLON:
    return "SEMICOLON";
  case LPAREN:
    return "LPAREN";
  case RPAREN:
    return "RPAREN";
  case LBRACE:
    return "LBRACE";
  case RBRACE:
    return "RBRACE";

  // Keywords
  case FUNCTION:
    return "FUNCTION";
  case LET:
    return "LET";

  default:
    return "UNKNOWN";
  }
}
