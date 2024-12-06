#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

#include <token_types.h>

// contents of token
union token_contents {
    char character;
    int integer;
    char *string;
};

// full token item
struct token {
    enum token_names name;
    union token_contents *contents;
};

#endif
