#ifndef AST_STRUCTURE
#define AST_STRUCTURE


typedef struct AST AST;


struct STRING { // store values that only require a string
    char *string;
};


struct INTEGER {
    int integer;
};


//store parameter data type and name
struct AST_FUNCTION_PARAMS {
    char *type; 
    char *name;
};


struct AST_FUNCTION {
    int param_count;
    int content_count;
    struct STRING *type; // return type
    struct STRING *name; // name, params, etc
    struct AST_FUNCTION_PARAMS **parameters;
    AST **contents; // look ahead to figure out how many contents are in the function, then alloc memory for array?
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
        RETURN_VALUE,
        FUNCTION_NAME
    } type;

    union {
        struct AST_FUNCTION AST_FUNCTION;
        struct INTEGER INTEGER;
        struct STRING STRING;
        struct TYPE TYPE;
    } data;
};


#endif
