SD = src/
ID = include/
BD = build/

OF = bin/sjs

OBJS = $(BD)main.o $(BD)lexer.o $(BD)AST.o $(BD)scope.o $(BD)parser.o

.PHONY: all clean re

all: $(OF)

re: clean all

$(BD)main.o: $(SD)main.c
	gcc $^ -I include -c -o $@

$(BD)lexer.o: $(SD)lexer.c
	gcc $^ -I include -c -o $@

$(BD)AST.o: $(SD)AST.c
	gcc $^ -I include -c -o $@

$(BD)scope.o: $(SD)scope.c
	gcc $^ -I include -c -o $@

$(BD)parser.o: $(SD)parser.c
	gcc $^ -I include -c -o $@

$(OF): $(OBJS)
	gcc $^ -o $@

clean:
	rm -f $(OBJS) $(OF)
