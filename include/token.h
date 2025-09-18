#ifndef TOKEN_H
#define TOKEN_H

#include "lexer.h"

// add new tokens also in 'getTokenTypeName' api if added here
typedef enum {
  ILLEGAL,
  EOF,

  // Identifiers + literals
  IDENT,
  INT,

  // Operators
  ASSIGN,
  PLUS,

  // Delimiters
  COMMA,
  SEMICOLON,

  LPAREN,
  RPAREN,
  LBRACE,
  RBRACE,

  // Keywords
  FUNCTION,
  LET,
} TOKEN_TYPE;

// the token struct will contain type and literal
// type => identifier, keyword, operator and literal being the value itself like
// foo, switch, +,-,/ and so on.
typedef struct {
  TOKEN_TYPE type;
  char *literal;
} Token;

typedef struct TokenList {
  Token data;
  struct TokenList *next;
} TokenList;

extern TokenList *tail_ptr;
extern TokenList *ll_head;

// api for inserting token to TokenList
void store_token(TokenList **curr_node_pointer, Token tok);

// api for getting the next token
Token next_token(Lexer *l);

// api for creating token structure
Token create_token(TOKEN_TYPE type, char byte);

// TODO: add info
void read_bytes(Lexer *l, char *stored_bytes);

char *getTokenTypeName(TOKEN_TYPE type);

#endif
