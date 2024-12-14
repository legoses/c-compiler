#ifndef AST_STRUCTURE
#define AST_STRUCTURE


typedef struct AST AST;


struct STRING { // store values that only require a string
    char *string;
};


struct INTEGER {
    int integer;
};


struct AST_FUNCTION {
    AST *type; // return type
    AST *name; // name, params, etc
    AST *contents;
};
        
struct TYPE {
    char *type;
};


struct AST {
    enum {
        FUNCTION,
        MAIN_FUNCTION,
        INTEGER,
        FUNCTION_RETURN,
        RETURN_VALUE
    } type;

    union {
        struct AST_FUNCTION AST_FUNCTION;
        struct INTEGER INTEGER;
        struct STRING STRING;
        struct TYPE TYPE;
    } data;
};


#endif
