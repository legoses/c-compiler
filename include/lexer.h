#ifndef LEXER_H
#define LEXER_H

#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <token_type.h>

void println(const char *s);
int check_for_type(char *buf, int it, struct token *t);
int fpeek(FILE **fd);
int is_char_or_num(char c);
int parse_string(FILE **fd, char *buf, const int len);
int parse_int(FILE **fd);
struct token* parse_char(FILE **fd);
int begin_parse(FILE **fd, struct token *tokenArr[], const int len);

#endif
