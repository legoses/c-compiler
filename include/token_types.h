#ifndef TOKEN_TYPES_H
#define TOKEN_TYPES_H

#define NUM_TYPES 3
#define NUM_TOKEN_NAMES 3

// token type identifier
enum token_names {
    OPEN_CURLY_BRACKET,
    CLOSE_CURLY_BRACKET,
    OPEN_PARANTHESIS,
    CLOSE_PARANTHESIS,
    SEMICOLON,
    INT_TYPE,
    RETURN_KEYWORD,
    IDENTIFIER,
    MAIN_IDENTIFIER,
    INTEGER_LITERAL,
    STRING
};

extern const char *TYPES[NUM_TYPES]; // = {"int", "return", "main"};
extern const enum token_names ENUM_TYPE_LIST[NUM_TOKEN_NAMES]; // = {INT_TYPE, RETURN_KEYWORD, IDENTIFIER};
//const char *TYPES[NUM_TYPES];// = {"int", "return", "main"};
//const enum token_names ENUM_TYPE_LIST[NUM_TOKEN_NAMES];// = {INT_TYPE, RETURN_KEYWORD, IDENTIFIER};

#endif
