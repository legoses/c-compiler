#include <ast_parser.h>


AST *create_function(struct token *token_arr[], int pos) {
    AST *ast = (AST*)malloc(sizeof(AST*));

    return ast;
}


int recurse_ast(struct token *token_arr[], int len, int count) {
    return 0;
}

// goign to try a recursive function for this
int create_ast(struct token *token_arr[], int len) {
    AST *root = NULL;
    AST *prevLevel = NULL;
    AST *currentLevel = NULL;



    for(int i = 0; i < len; i++) {
        switch(token_arr[i]->name) {
            case RETURN_KEYWORD:
            case IDENTIFIER:
            case STRING:
            case MAIN_IDENTIFIER:
                root = create_function(token_arr, i);
                root->type = MAIN_FUNCTION; 
        }
        
    }

    return 0;
}
