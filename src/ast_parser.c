#include <ast_parser.h>


AST create_ast_main_function(struct token *token, int pos, int len) {
    
     
}


int create_ast(struct token *token_arr[], int len) {
    const int AST_LEN = 100;
    AST *ast_arr[AST_LEN];

    Token *tokenObj = Token_new(token_arr, len);
    printf("Token arr len: %i\n", len);

    do {
        switch((*tokenObj->pos)->name) {
            case MAIN_IDENTIFIER:
                printf("Main identifier found\n");
                break;
        }

    } while(Token_inc(tokenObj) != -1);

    return 0;
}
