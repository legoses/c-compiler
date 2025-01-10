#include <ast_parser.h>


int check_for_data_type(Token *token) { //checks for type and iterates token position
    if(Token_inc(token) == 0) {
        if((*token->pos)->name == INT_TYPE || (*token->pos)->name == CHAR_TYPE) { //check for data type
            return 0;
        }
    }
    return -1;
}


int check_for_identifier(Token *token) {
    if(Token_inc(token) == 0) {
        if((*token->pos)->name == IDENTIFIER) { //check for data type
            return 0;
        }
    }
    return -1;
}


struct AST_FUNCTION_PARAMS* get_single_parameter(Token *token) {
    struct AST_FUNCTION_PARAMS *a = (struct AST_FUNCTION_PARAMS*)malloc(sizeof(struct AST_FUNCTION_PARAMS));

    int typeSize = strlen((*token->pos)->contents->string);
    a->type = (char*)malloc(sizeof(char) * typeSize);
    strncpy(a->type, (*token->pos)->contents->string, typeSize);

    Token_inc(&(*token));
    int nameSize = strlen((*token->pos)->contents->string);
    a->name = (char*)malloc(sizeof(char) * nameSize);
    strncpy(a->name, (*token->pos)->contents->string, nameSize);

    Token_inc(token);
    return a;
}


int parse_parameter(Token *token, struct AST_FUNCTION_PARAMS **ast, int len) {
    struct AST_FUNCTION_PARAMS **a = (struct AST_FUNCTION_PARAMS**)malloc(sizeof(struct AST_FUNCTION_PARAMS*) * len);
    Token_inc(token); // iterate so loop will start on first parameter
    for(int i = 0; i < len; i++) {
        a[i] = get_single_parameter(token);     
    }

    return 0;
}


//dont worry about figuring out syntax yet, only count
// for now, will just count semi colons, later will also watch for if statments, loops, anyting that doesnt end with semicolon
int count_ast_func_contents(Token *token) {
    int count = 0; //number of function contents
    int itr = 0; //total iterations

    while(Token_inc(token) != -1) {
        enum token_names n = (*token->pos)->name;
        if(n == SEMICOLON) {
            count++;
        }
        itr++;

    }

    Token_dec_num(token, itr);

    return count;
}


int get_num_function_params(Token *token) {
    Token_inc(token); //iterate token. Make sure it lands on an opening paramenesis for function parameters
    int num = 0; // number of parameters found
    int count = 0; //total number of iterations, so it can be undone before returning

    if((*token->pos)->name == OPEN_PARANTHESIS) {
        count++;
        while(Token_inc(token) != -1) {
            count++;
            if((*token->pos)->name != CLOSE_PARANTHESIS) { // only iterate through if ther are parameters
                // each of these should only be a single type, so its okay to iterate after checking
                if(check_for_data_type(token) == 0 && check_for_identifier(token) == 0) { //check for data type, and iterate paramater count
                    count += 2;
                    num++;
                }
                else {
                    return -1;
                }

                //next value could be multiple different types, so manually iterate and check against each
                Token_inc(token);
                count++;

                // should have a comma seperator type, but for now just check for stored comma char
                if((*token->pos)->name == COMMA) {
                    Token_inc(token);
                    count++;
                }
                else if ((*token->pos)->name == CLOSE_PARANTHESIS) { //
                    Token_dec_num(token, count);
                    return num;
                }
                else { // if an improper value is detected, return error
                    return -1;
                }
            }
            else {
                Token_dec_num(token, count);
                return num;
            }
            
        }
    }
    else {
        return -1;
    }

    return num;
}



// whhle interpreting lines, it may be important to read until logical conclusion (like semicolon, or closing bracker/ paranthese)
// instead of having rigid definition of what everything should be
AST create_ast_main_function(Token *token) {
    //AST *a = NULL;
    int numParam = get_num_function_params(token);
    int numContent = count_ast_func_contents(token);

    //get number of parameters
    //figure out how many items are in the function
    //allocate memory

    if (numParam >= 0) {
        AST *a = (AST*)malloc(sizeof(AST));
        //a->type = MAIN_FUNCTION;
        a = {
            MAIN_FUNCTION,
            {
                .AST_FUNCTION = (struct AST_FUNCTION) {
                    .param_count = numParam,
                    .content_count = numContent
                    .type = (char*)malloc(sizeof(char)*4), // int + null terminator
                    .name = (char*)malloc(sizeof(char)*5),  //main + null terinator
                    .parameters = (struct AST_FUNCTION_PARAMS**)malloc(sizeof(struct AST_FUNCTION_PARAMS*)),
                    .contents = (AST**)malloc(sizeof(AST*) * numContent),
                }
            }
        }

        strncpy(a->data.AST_FUNCTION->type, "int\0", 4);
        strncpy(a->data.AST_FUNCTION->name, "name\0", 5);
        
        parse_parameter(token, a->data.AST_FUNCTION.parameters, numParam);

        do {
            switch((*token->pos)->name) {
                case COMMA:
                    
                    break;
            }

        } while(Token_inc(token) != -1);

    }
     
}


int create_ast(struct token *token_arr[], int len) {
    const int AST_LEN = 100;
    AST *ast_arr[AST_LEN];

    Token *tokenObj = Token_new(token_arr, len);
    printf("Token arr len: %i\n", len);

    do {
        switch((*tokenObj->pos)->name) {
            case MAIN_IDENTIFIER:
                create_ast_main_function(tokenObj);
                break;
        }

    } while(Token_inc(tokenObj) != -1);

    return 0;
}
