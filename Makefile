compiler: src/main.c
	gcc ./src/main.c ./src/lexer.c ./src/token_types.c -o compiler -I/home/legoses/Documents/C/compiler/include

clean:
	rm ./compiler
