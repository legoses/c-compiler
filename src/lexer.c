#include <lexer.h>

void println(const char *s) {
    printf("%s\n", s);
}


int check_for_type(char *buf, int it, struct token *t) { // recursive function to check for a data type
    regex_t re;
    int re_cmp = regcomp(&re, TYPES[it], 0);
    re_cmp = regexec(&re, buf, 0, NULL, 0);
    
    if(re_cmp == 0) {
        union token_contents *c = (union token_contents*)malloc(sizeof(union token_contents*));

        int len = strlen(buf);
        //alloc space for union and string, and copy buf contents to string
        c->string = (char*)malloc(sizeof(char*) * len);
        strcpy(c->string, buf);
        t->contents = c;
        t->name = ENUM_TYPE_LIST[it];

        return it;
    }

    if(it+1 < NUM_TYPES) {
        //printf("%i\n", it);
        it++;
        return check_for_type(buf, it, t);
    }

    return -1;
}


int fpeek(FILE **fd) {
    int c = fgetc(*fd);
    ungetc(c, *fd);

    return c;
}


int is_char_or_num(char c) {
    int ch = (int)c;
    //printf("Char dec val: %i. Char val: %c\n", ch, c);
    if((ch >= 48 && ch <= 57) //ch is a number between 0-9
    || (ch >= 65 && ch <= 90) // ch is an upper chase chharachter
    || (ch >= 97 && ch <= 122) // ch is a lower chase number
    || (ch == 95)) { // c is an underscore
        return 0;
    }

    return 1;
}


int parse_string(FILE **fd, char *buf, const int len) { //parse string token. returns string length
    int it = 0;
    while(!feof(*fd)) {
        int c = fgetc(*fd);
        //if((isalpha(c) != 0) || isdigit(c) != 0) { this will work for user defined strings, but not identifiers
        if(is_char_or_num(c) == 0) {
            buf[it] = c;
            it++;
        }
        else {
            ungetc(c, *fd);
            buf[it+1] = '\0'; // add null terminator for regex
            break;
        }
    }

    return it+1;
}


int parse_int(FILE **fd) { // parse integer token. Return integer
    int num = 0;

    while(!feof(*fd)) {
        char c = fgetc(*fd);

        if(isdigit(c)) {
            //printf("number found: %c\n", c);
            int ch = (int)c - 48;
            num = num * 10;
            num += ch; // convert to integer
        }
        else {
            ungetc(c, *fd); // backspace cursor
            //printf("Returning %i\n", num);
            return num;
        }
    }


    return num; // probably switch to error code 
}


struct token* parse_char(FILE **fd) {
    int c = fgetc(*fd);
    struct token *t = NULL;
    union token_contents *content = NULL; // 
   
    //printf("Printing char test: %c\n", c);
    switch(c) {
        case '{':
            t = (struct token*)malloc(sizeof(struct token*));
            t->contents = (union token_contents*)malloc(sizeof(union token_contents*));

            t->name = OPEN_CURLY_BRACKET;
            t->contents->character = '{';
            break;
        case '}':
            t = (struct token*)malloc(sizeof(struct token*));
            t->contents = (union token_contents*)malloc(sizeof(union token_contents*));

            t->name = CLOSE_CURLY_BRACKET;
            t->contents->character = '}';
            break;
        case '(':
            println("Pre alloc test");
            t = (struct token*)malloc(sizeof(struct token*));
            t->contents = (union token_contents*)malloc(sizeof(union token_contents*));
            println("post alloc test");
            
            t->name = OPEN_PARANTHESIS;
            println("post name assign test");
            t->contents->character = '(';
            break;
        case ')':
            t = (struct token*)malloc(sizeof(struct token*));
            t->contents = (union token_contents*)malloc(sizeof(union token_contents*));

            t->name = CLOSE_PARANTHESIS;
            t->contents->character = ')';
            break;
        case ';':
            println("Found semicolon");
            t = (struct token*)malloc(sizeof(struct token*));
            t->contents = (union token_contents*)malloc(sizeof(union token_contents*));

            t->name = SEMICOLON;
            t->contents->character = ';';
            break;
    }

    return t;
}


int begin_parse(FILE **fd, struct token *tokenArr[], const int len) {
    int it = 0; // file position iterator
    const int BUF_LEN = 100;
    char buf[BUF_LEN]; //hold token while processing 
    int arr_pos = 0; // iterator for buffer location

    while(!feof(*fd)) {
        struct token *t = NULL; // only allocate storage if valid token is found
        if(isalpha(fpeek(fd)) != 0) { //check if this is a string
            t = (struct token*)malloc(sizeof(struct token*));
        
            int bufLen = parse_string(fd, buf, BUF_LEN);
            int token_data_type = check_for_type(buf, 0, t); // check if string is data type. Seperate string and data type parsing later

            if(token_data_type == -1) {
                t->name = STRING;
                t->contents = (union token_contents*)malloc(sizeof(union token_contents*));
                t->contents->string = (char*)malloc(sizeof(bufLen));
                strcpy(t->contents->string, buf);
            }
        }
        else if(isdigit(fpeek(fd)) != 0) { //check if token is int
            //allocate memory for struct and union
            t = (struct token*)malloc(sizeof(struct token*));
            t->contents = (union token_contents*)malloc(sizeof(union token_contents*));

            t->contents->integer = parse_int(fd);
            t->name = INTEGER_LITERAL;
        }
        else { // for now, everything else should be single character
            t = parse_char(fd);
        }

        // if a token was generated, and buffer is not full, add new token to buffer
        if(t != NULL && arr_pos < len) {
            tokenArr[arr_pos] = t;
            arr_pos++;
        }

        it++;
    } 

    return arr_pos;
}
