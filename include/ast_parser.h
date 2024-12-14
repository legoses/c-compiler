#ifndef AST_PARSER_H
#define AST_PARSER_H

#include <ast_structure.h>
#include <token_type.h>
#include <stdlib.h>

int recurse_ast(struct token *token_arr[], int len, int count);
int create_ast(struct token *token_arr[], int len);


#endif
