#ifndef AST_PARSER_H
#define AST_PARSER_H

#include <ast_structure.h>
#include <token_type.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int check_type(int t, int t1);
int get_num_parameters(struct token *token_arr[], int pos, int len);
int str_len(const char *str);
int count_func_contents(struct token *token_arr[], int pos, int len);
int populate_ast_function(struct token *token_arr[], int pos, AST *ast, int contents);
AST* create_string(char *w, int len);
AST* create_return();
AST* create_ast_identifier(struct token *token);
AST *ast_new(AST ast);
int recurse_ast(struct token *token_arr[], int len, int count);
AST* create_return_keyword(char *w, int len);
AST *create_main_function(struct token *token_arr[], int pos, int len);
int add_ast_contents(AST **ast_arr, AST *ast, int *pos, int len); // add contents to array. Makes sure position is within arr length
int create_ast(struct token *token_arr[], int len);


#endif
