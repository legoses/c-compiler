#include <lexer.h>
#include <ast_structure.h>

/*
 * TODO:
 * Fix make file to properly include header files
 *
*/

void print_tokens(struct token **arr, int len) {
    for(int i = 0; i < len; i++) {
        switch(arr[i]->name) {
            case OPEN_CURLY_BRACKET:
            case CLOSE_CURLY_BRACKET:
            case OPEN_PARANTHESIS:
            case SEMICOLON:
            case CLOSE_PARANTHESIS:
                printf("Character token: %c\n", arr[i]->contents->character);
                break;
            case INT_TYPE:
            case RETURN_KEYWORD:
            case STRING:
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
    printf("Token name print test: %s\n", tokenArr[1]->contents->string);
    print_tokens(tokenArr, num_tokens);
    fclose(file);

    return 0;
}
