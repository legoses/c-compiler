#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

/*
 * TODO:
 * Currently, a struct is being allocated for each charatcter instead of each token
 * assign token when string is identified as a data type
*/

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
    INTEGER_LITERAL,
    STRING
};

const char *TYPES[] = {"int", "return", "main"};
const enum token_names ENUM_TYPE_LIST[] = {INT_TYPE, RETURN_KEYWORD, IDENTIFIER};
const int NUM_TYPES = 3;

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

//const char *tokens_types[] = {"{", "}", "(", ")", ";", "int", "return"}; // Dont think i need this. Remove later


int check_for_type(char *buf, int it, struct token *t) { // recursive function to check for a data type
    regex_t re;
    int re_cmp = regcomp(&re, TYPES[it], 0);
    re_cmp = regexec(&re, buf, 0, NULL, 0);
    
    if(re_cmp == 0) {
        union token_contents *c = (union token_contents*)malloc(sizeof(union token_contents*));

        int len = strlen(buf);
        //alloc space for union and string, and copy buf contents to string
        c->string = (char*)malloc(sizeof(char*) * len);
        strcpy(c->string, buf);
        t->contents = c;
        t->name = ENUM_TYPE_LIST[it];
        //printf("Buf %s is of type %s\n", buf, TYPES[it]);

        return it;
    }

    if(it+1 < NUM_TYPES) {
        //printf("%i\n", it);
        it++;
        return check_for_type(buf, it, t);
    }

    return -1;
}


int fpeek(FILE **fd) {
    int c = fgetc(*fd);
    ungetc(c, *fd);

    return c;
}


int is_char_or_num(char c) {
    int ch = (int)c;
    printf("Char dec val: %i. Char val: %c\n", ch, c);
    if((ch >= 48 && ch <= 57) //ch is a number between 0-9
    || (ch >= 65 && ch <= 90) // ch is an upper chase chharachter
    || (ch >= 97 && ch <= 122) // ch is a lower chase number
    || (ch == 95)) { // c is an underscore
        return 0;
    }

    return 1;
}


int parse_string(FILE **fd, char *buf, const int len) { //parse string token. returns string length
    int it = 0;
    while(!feof(*fd)) {
        int c = fgetc(*fd);
        //if((isalpha(c) != 0) || isdigit(c) != 0) { this will work for user defined strings, but not identifiers
        if(is_char_or_num(c) == 0) {
            buf[it] = c;
            it++;
        }
        else {
            ungetc(c, *fd);
            buf[it+1] = '\0'; // add null terminator for regex
            break;
        }
    }

    return it+1;
}


int parse_int(FILE **fd) { // parse integer token. Return integer
    int num = 0;

    while(!feof(*fd)) {
        char c = fgetc(*fd);

        if(isdigit(c)) {
            printf("number found: %c\n", c);
            int ch = (int)c - 48;
            num = num * 10;
            num += ch; // convert to integer
        }
        else {
            ungetc(c, *fd); // backspace cursor
            printf("Returning %i\n", num);
            return num;
        }
    }


    return num; // probably switch to error code 
}


struct token* parse_char(FILE **fd, struct token *token) {
    int c = fgetc(*fd);
    struct token *t = NULL;
    union token_contents *content = NULL; // 
    switch(c) {
        case '{':
            t = (struct token*)malloc(sizeof(struct token*));
            t->contents = (union token_contents*)malloc(sizeof(union token_contents*));

            token->name = OPEN_CURLY_BRACKET;
            t->contents->character = '{';
            break;
        case '}':
            t = (struct token*)malloc(sizeof(struct token*));
            t->contents = (union token_contents*)malloc(sizeof(union token_contents*));

            token->name = CLOSE_CURLY_BRACKET;
            t->contents->character = '}';
            break;
        case '(':
            t = (struct token*)malloc(sizeof(struct token*));
            t->contents = (union token_contents*)malloc(sizeof(union token_contents*));
            
            token->name = OPEN_PARANTHESIS;
            t->contents->character = '(';
            break;
        case ')':
            t = (struct token*)malloc(sizeof(struct token*));
            t->contents = (union token_contents*)malloc(sizeof(union token_contents*));

            token->name = CLOSE_PARANTHESIS;
            t->contents->character = ')';
            break;
        case ';':
            t = (struct token*)malloc(sizeof(struct token*));
            t->contents = (union token_contents*)malloc(sizeof(union token_contents*));

            token->name = SEMICOLON;
            t->contents->character = ';';
            break;
    }
    token->contents = content;

    return t;
}


int begin_parse(FILE **fd, struct token *tokenArr[], const int len) {
    int it = 0; // file position iterator
    const int BUF_LEN = 100;
    char buf[BUF_LEN]; //hold token while processing 
    int arr_pos = 0; // iterator for buffer location

    while(!feof(*fd)) {
        struct token *t = NULL; // only allocate storage if valid token is found
        if(isalpha(fpeek(fd)) != 0) { //check if this is a string
            arr_pos++;
            t = (struct token*)malloc(sizeof(struct token*));
        
            int bufLen = parse_string(fd, buf, BUF_LEN);
            int token_data_type = check_for_type(buf, 0, t); // check if string is data type. Seperate string and data type parsing later
            if(token_data_type == -1) {
                printf("Regular string identified\n");
                t->name = STRING;
                t->contents = (union token_contents*)malloc(sizeof(union token_contents*));
                t->contents->string = (char*)malloc(sizeof(bufLen));
                printf("Regular string parsed\n");
                strcpy(t->contents->string, buf);
                printf("String contents:  %s\n", t->contents->string);
                
            }
        }
        else if(isdigit(fpeek(fd)) != 0) { //check if token is int
            arr_pos++;
            printf("DIGIT IDENTIFIED\n");
            
            //allocate memory for struct and union
            t = (struct token*)malloc(sizeof(struct token*));
            t->contents = (union token_contents*)malloc(sizeof(union token_contents*));

            t->contents->integer = parse_int(fd);
            printf("post int parse\n");
            t->name = INTEGER_LITERAL;
        }
        else { // for now, everything else should be single character
            //arr_pos++;
            t = parse_char(fd, t);
            if(t != NULL) {
                arr_pos++;
            }
        }

        if(t != NULL && arr_pos < len) {
            tokenArr[arr_pos] = t;
        }
    } 

    return arr_pos;
}


void print_tokens(struct token **arr, int len) {
    for(int i = 0; i < len; i++) {
        switch(arr[i]->name) {
            case OPEN_CURLY_BRACKET:
            case CLOSE_CURLY_BRACKET:
            case OPEN_PARANTHESIS:
            case CLOSE_PARANTHESIS:
                printf("Character token: %c\n", arr[i]->contents->character);
                break;
            case INT_TYPE:
            case RETURN_KEYWORD:
            case IDENTIFIER:
                printf("String token: %s\n", arr[i]->contents->string);
                break;
            case INTEGER_LITERAL:
                printf("Integer token: %i\n", arr[i]->contents->integer);
                break;
        }
    }
}


int main(int argc, char **argv) {
    const int LEN = 1000;
    if(argc <= 1) {
        printf("Error: Input Recieved\n");
        return -1;
    }

    FILE *file = fopen(argv[1], "r");
    struct token *tokenArr[LEN];


    if(file == NULL) {
        printf("Error: Provided file path does not exist. Exiting...\n");
        return -1;
    }
    
    int num_tokens = begin_parse(&file, tokenArr, LEN);

    printf("Number of Tokens found: %i\n", num_tokens);
    print_tokens(tokenArr, num_tokens);
    fclose(file);

return 0;
}
