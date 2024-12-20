#ifndef AST_PARSER_H
#define AST_PARSER_H

#include <ast_structure.h>
#include <token_type.h>
#include <stdlib.h>
#include <stdio.h>


int check_type(int t, int t1);
int get_num_parameters(struct token *token_arr[], int pos, int len);
AST *ast_new(AST ast);
int recurse_ast(struct token *token_arr[], int len, int count);
AST *create_main_function(struct token *token_arr[], int pos, int len);
int create_ast(struct token *token_arr[], int len);


#endif
