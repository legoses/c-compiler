#ifndef TOKEN_H
#define TOKEN_H

#include <token_type.h>
#include <stdlib.h>

typedef struct {
    struct token **beg;
    struct token **end;
    struct token **arr;
    struct token **pos;
} Token;

void Token_init(Token *token, struct token **arr, int len);
Token *Token_new(struct token **arr, int len);
int Token_inc(Token *token);
int Token_dec(Token *token);

#endif
