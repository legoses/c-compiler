#include <ast_parser.h>


AST create_ast_main_function(struct token *token_arr[], int pos, int len) {
    
}


int create_ast(struct token *token_arr[], int len) {
    for(int i = 0; i < len; i++) {
        switch(token_arr[i]->name) {
            case MAIN_IDENTIFIER:
                
        }
    }
    return 0;
}
