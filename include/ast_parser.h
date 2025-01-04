#ifndef AST_PARSER_H
#define AST_PARSER_H

#include <ast_structure.h>
#include <token_type.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct token *consume_token(struct token *token_arr[], int len);
AST create_ast_main_function(struct token *token, int pos, int len);
int create_ast(struct token *token_arr[], int len);


#endif
