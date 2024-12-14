#include <ast_parser.h>


int check_type(enum type t, enum type t1) {
    if(t == t1) {
        return 0;
    }

    return 1;
}


AST *ast_new(AST ast) { // nested struct will be passed as the argument
    AST *ptr = (AST*)malloc(sizeof(AST*));

    if(ptr) {
        *ptr = ast;
    }

    return ptr;
}


AST *create_main_function(struct token *token_arr[], int pos) {
    AST *ast;
    // need to make sure pos is not the first or last index position
    if(check_type(token_arr[pos-1]->name) && check_type(token_arr[pos+1], OPEN_PARANTHESIS)) {
        ast = ast_new((AST){
            MAIN_FUNCTION, //set enum tag
            .AST_FUNCTION = (struct AST_FUNCTION) { 
                .type = ast_new((AST){
                    RETURN_VALUE,
                    {.STRING = (struct STRING) {
                        .string = (char*)malloc(sizeof(char)*3); // remember to copy in str to this value later
                    }}
                }), 
            }
        });
    }
    else {
        printf("Error creating main function\n");
    }
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
            case FUNCTION:
                break;
            case RETURN_KEYWORD:
                break;
            case IDENTIFIER:
                break;
            case STRING:
                break;
            case MAIN_IDENTIFIER: //create root struct, and assign to current level
                root = create_main_function(token_arr, i);
                currentLevel = root;
                break;
        }
        
    }

    return 0;
}
