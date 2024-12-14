compiler: ./src/main.c ./src/lexer.c ./src/token_types.c ./src/ast_parser.c
	gcc ./src/main.c ./src/lexer.c ./src/token_types.c ./src/ast_parser.c -o compiler -I./include

clean:
	rm ./compiler
