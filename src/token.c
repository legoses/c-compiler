#include <token.h>
#include <stdio.h>


void Token_init(Token *token, struct token **arr, int len) {
    token->beg = &arr[0];
    token->end = &arr[len-1];
    token->arr = arr;
    token->pos = &arr[0];
}


Token *Token_new(struct token **arr, int len) {
    Token *token = (Token*)malloc(sizeof(Token));
    
    Token_init(token, arr, len);
    return token;
}


//iterate though token array by navigating through pointer addresses, and avoiding having to keep track of an integer containing position
int Token_inc(Token *token) {
    //int size = sizeof(struct token**);

    printf("Position of current token: %p. Position with size added: %p\n", token->pos, (token->pos + 1));
    printf("Position of end of array: %p\n", token->end);

    //when iterating through an array, do not use sizeof(struct) as the iteration value, use 1
    //compiler knows and will automatically iterate by the size of the struct
    if((token->pos + 1) < token->end) {
        token->pos += 1;
        return 0;
    }

    return -1;
}


int Token_dec(Token *token) {
    //int size = sizeof(struct token*);
    if((token->pos + 1) > token->beg) {
        token->pos -= 1;
        return 0;
    }

    return -1;
}
