#include <ast_parser.h>


int check_for_data_type(Token *token) { //checks for type and iterates token position
    if(Token_inc(&token) == 0) {
        if((*token->pos)->name == INT_TYPE || (*token->pos)->name == CHAR_TYPE) { //check for data type
            return 0;
        }
    }
    return -1;
}


int check_for_identifier(Token *token) {
    if(Token_inc(&token) == 0) {
        if((*token->pos)->name == IDENTIFIER) { //check for data type
            return 0;
        }
    }
    return -1;
}


int get_num_function_params(Token *token) {
    Token_inc(&token); //iterate token. Make sure it lands on an opening paramenesis for function parameters
    int num = 0; // number of parameters found
    int count = 0; //total number of iterations, so it can be undone before returning

    if((*token->pos)->name == OPEN_PARANTHESIS) {
        count++;
        while(Token_inc(&token) != -1) {
            count++;
            if((*token->pos)->name == CLOSE_PARANTHESIS) { // if close paranthesis is detected, return
                Token_dec_num(&token, count);
                return num;
            }
            
            // each of these should only be a single type, so its okay to iterate after checking
            if(check_for_data_type(&token) == 0 && check_for_identifier(&token) == 0) { //check for data type
                count += 2;
            }
            else {
                return -1;
            }

            //next value could be multiple different types, so manually iterate and check against each
            Token_inc(&token);
            count++;

            // should have a comma seperator type, but for now just check for stored comma char
            if((*token->pos)->name == COMMA)
        }
    }
    else {
        return -1;
    }

    return num;
}


AST create_ast_main_function(Token *token) {
    AST *a = NULL;
    int numParam = get_num_function_params(&token)

    //get number of parameters
    //figure out how many items are in the function
    //allocate memory

    do {
        switch((*token->pos)->name) {
            case MAIN_IDENTIFIER:
                create_ast_main_function()
                break;
        }

    } while(Token_inc(&token) != -1);
     
}


int create_ast(struct token *token_arr[], int len) {
    const int AST_LEN = 100;
    AST *ast_arr[AST_LEN];

    Token *tokenObj = Token_new(token_arr, len);
    printf("Token arr len: %i\n", len);

    do {
        switch((*tokenObj->pos)->name) {
            case MAIN_IDENTIFIER:
                create_ast_main_function(&token);
                break;
        }

    } while(Token_inc(tokenObj) != -1);

    return 0;
}
