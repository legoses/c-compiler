#include <ast_parser.h>


// Iterate through the array, return NULL when end is reached
struct token *consume_token(struct token *token_arr[], int len) {
    static int pos = 0;
    
    if(pos < len) {
        struct token *t = token_arr[pos];
        pos++;

        return t;
    }

    return NULL;
}


AST create_ast_main_function(struct token *token, int pos, int len) {
    
     
}




int create_ast(struct token *token_arr[], int len) {
    struct token *cur_token = NULL;
    struct token **token_arr_end_addr = &token_arr[len-1];

    const int AST_LEN = 100;
    AST *ast_arr[AST_LEN];


    printf("Token end addr test: %p\n", token_arr_end_addr);
    printf("Value of addr end ptr: %c\n", (*token_arr_end_addr)->contents->character);


    cur_token = consume_token(token_arr, len);

    while(cur_token != NULL) {
        switch(cur_token->name) {
            case MAIN_IDENTIFIER:
                break;
        }

        cur_token = consume_token(token_arr, len);
    }

    return 0;
}
