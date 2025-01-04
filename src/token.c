#include <token.h>


void Token_init(Token *token, struct token **arr, int len) {
    token->beg = &arr[0];
    token->end = &arr[len-1];
    token->arr = arr;
}


Token *Token_new(struct token **arr, int len) {
    Token *token = (Token*)malloc(sizeof(Token));
    
    Token_init(token, arr, len);
    return token;
}
