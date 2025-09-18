#ifndef LEXER_H
#define LEXER_H

typedef struct {
  char *input; // input will the series of bytes we are processing at the moment
  int curr_position; //  will point to current character we are processing
  int peek;          // point to next character
  char ch;           // will hold the current character
} Lexer;

// initialize a lexer object of processing current input stream
void init(char *input);

// read one character from input stream
void read_char(Lexer *l);


// eat all the whitespaces in input stream until we hit a valid letter
void skip_whitespaces(Lexer *l);
#endif
