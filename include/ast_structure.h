#ifndef AST_STRUCTURE
#define AST_STRUCTURE


typedef struct AST AST;


struct STRING { // store values that only require a string
    char *string;
};


struct INTEGER {
    int integer;
};


struct FUNCTION_HEADERS {
    enum {
        RET_VAL,
        PARAMETER,
        NAME
    } type;
   
    union {
        struct STRING RET_VAL;
        struct STRING NAME;
        struct PARAMETER {
            char *left; //type
            char *right; // name
        } PARAMETER;
    } data;
};


/*
struct FUNCTION_BODY {
    enum {
        TYPE,
        INTEGER,
        RETURN
    } type;

    union {
        struct TYPE 
    } data;
};
*/

struct AST {
    enum {
        FUNCTION,
        MAIN_FUNCTION,
        INTEGER,
        FUNCTION_RETURN,
        RETURN_VALUE
    } type;

    union {
        struct AST {
            struct FUNCTION_HEADERS *left; // return type
            struct *right; // name, params, etc
        } AST_FUNCTION;

        struct TYPE {
            char *type;
        } TYPE;

        struct 
    } data;
};


#endif
