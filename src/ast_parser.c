#include <ast_parser.h>


int check_type(int t, int t1) {
    if(t == t1) {
        return 0;
    }

    return 1;
}


// requires string to have nulll terminator to accuratly determine length
int str_len(const char *str) {
    int i = 0;
    while(str[i] != '\0') {
        i++;
    }

    return i;
}


int get_num_parameters(struct token *token_arr[], int pos, int len) {
    int i = pos+2;

    if(check_type(token_arr[pos+1]->name, OPEN_PARANTHESIS) == 0) {

        while(i < len && check_type(token_arr[i]->name, CLOSE_PARANTHESIS) != 0) {
            i++;
        }
    }
    
    return (i - pos) - 2; // probably correct
}


AST *ast_new(AST ast) { // turns passed AST into pointer
    AST *ptr = malloc(sizeof(AST));

    if(ptr) {
        *ptr = ast;
    }

    printf("AST NEW CALLED\n");
    return ptr;
}


AST* create_return_keyword(char *w, int len) {
    AST *ast;

    ast = ast_new((AST) {
        RETURN_VALUE,
        {.STRING = (struct STRING) {
            .string = (char*)malloc(sizeof(char)*7),
        }}
    });

    strncpy(ast->data.STRING.string, "return", 6);
    ast->data.STRING.string[6] = '\0'; // add null terminator to keep inline with the rest of my string formatting
    // oh man
    return ast;
}



// make memory allocared more dynamic to allow for differenct length of strings. If token does not have string length, either go backa and implement in the lexer, or do it here
AST* create_string(char *w, int len) {
    AST *ast;
    int strLen = str_len(w);

    ast = ast_new((AST) {
        RETURN_VALUE,
        {.STRING = (struct STRING) {
            .string = (char*)malloc(sizeof(char)*(strLen+1)),
        }}
    });

    strncpy(ast->data.STRING.string, w, strLen);
    ast->data.STRING.string[strLen+1] = '\0';

    return ast;
}


int count_func_contents(struct token *token_arr[], int pos, int len) { // get the amount of tokens stored in function
    int num = 0;
    int i = pos;
    
    // for now, just count lines ending with semicolon until the next closing curley bracket is found
    while(token_arr[i]->name != CLOSE_CURLY_BRACKET && i < len) {
        if (token_arr[i]->name == SEMICOLON) {
            num++;
        }
        i++;
    }

    return num;
}

/*
AST *create_function(struct token *token_arr[], int pos, int len) { //create a regular function
    AST *ast;
    get_num_parameters(token_arr, pos, len);
    
    if((token_arr[pos-1]->name == INT_TYPE) && (token_arr[pos+1]->name == OPEN_PARANTHESIS)) { // ERROR CHECK, no open paranthesis
        printf("Creating function\n"); // test
        //this initializes return type, name, and parameters, leaving the actual function for later
        ast = ast_new((AST){
            FUNCTION, //set enum tag
            {
                .AST_FUNCTION = (struct AST_FUNCTION) {
                    .type = ast_new((AST){
                        RETURN_VALUE,
                        {.STRING = (struct STRING) {
                            .string = (char*)malloc(sizeof(char)*3), // remember to copy in str to this value later
                        }}
                    }),
                    .name = ast_new((AST) {
                        FUNCTION_NAME,
                        {.STRING = (struct STRING) {
                            .string = (char*)malloc(sizeof(char)*4),
                        }}
                    }),
                    .parameters = NULL,
                }
            }
        });
    }
    else {
        printf("Error creating main function\n");
    }
    
    return ast;
}
*/


void create_function(struct token *token_arr[], int pos, int len) { //create a regular function
    AST *ast;
    get_num_parameters(token_arr, pos, len);
    
    if((token_arr[pos-1]->name == INT_TYPE) && (token_arr[pos+1]->name == OPEN_PARANTHESIS)) { // ERROR CHECK, no open paranthesis
        printf("Creating function\n"); // test
        //this initializes return type, name, and parameters, leaving the actual function for later
        ast = ast_new((AST){
            FUNCTION, //set enum tag
            {
                .AST_FUNCTION = (struct AST_FUNCTION) {
                    .type = ast_new((AST){
                        RETURN_VALUE,
                        {.STRING = (struct STRING) {
                            .string = (char*)malloc(sizeof(char)*3), // remember to copy in str to this value later
                        }}
                    }),
                    .name = ast_new((AST) {
                        FUNCTION_NAME,
                        {.STRING = (struct STRING) {
                            .string = (char*)malloc(sizeof(char)*4),
                        }}
                    }),
                    .parameters = NULL,
                }
            }
        });
    }
    else {
        printf("Error creating main function\n");
    }
    
    return ast;
}

AST *create_main_function(struct token *token_arr[], int pos, int len) { // ERROR CHECK, no open paranthesis
    AST *ast;
    get_num_parameters(token_arr, pos, len);
    // need to make sure pos is not the first or last index position
    if((token_arr[pos-1]->name == INT_TYPE) && (token_arr[pos+1]->name == OPEN_PARANTHESIS)) {
        printf("Creating main function\n"); // test
        //this initializes return type, name, and parameters, leaving the actual function for later
        ast = ast_new((AST){
            MAIN_FUNCTION, //set enum tag
            {
                .AST_FUNCTION = (struct AST_FUNCTION) {
                    .type = ast_new((AST){
                        RETURN_VALUE,
                        {.STRING = (struct STRING) {
                            .string = (char*)malloc(sizeof(char)*3), // remember to copy in str to this value later
                        }}
                    }),
                    .name = ast_new((AST) {
                        FUNCTION_NAME,
                        {.STRING = (struct STRING) {
                            .string = (char*)malloc(sizeof(char)*4),
                        }}
                    }),
                    .parameters = NULL,
                }
            }
        });
    }
    else {
        printf("Error creating main function\n");
    }
    return ast;
}


// goign to try a recursive function for this
int create_ast(struct token *token_arr[], int len) {
    AST *root = NULL;
    AST *prevLevel = NULL;
    AST *currentLevel = NULL;


    for(int i = 0; i < len; i++) {
        switch(token_arr[i]->name) {
            case FUNCTION:
                prevLevel = currentLevel;
                currentLevel = create_function(token_arr, i, len);
                prevLevel->data
                break;
            case RETURN_KEYWORD:
                break;
            case IDENTIFIER:
                break;
            case STRING:
                break;
            case MAIN_IDENTIFIER: //create root struct, and assign to current level
                root = create_main_function(token_arr, i, len);
                currentLevel = root;
                break;
        }
        
    }

    return 0;
}
