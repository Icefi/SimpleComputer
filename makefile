SD = src/
ID = include/
BD = build/

OF = bin/sc

OBJS = $(BD)main.o $(BD)sc_memory_reg.o $(BD)sc_terminal.o $(BD)sc_bigchar.o $(BD)sc_readkey.o

.PHONY: all clean re

all: $(OF)

re: clean all

$(BD)main.o: $(SD)main.c
	gcc $^ -I include -c -o $@

$(BD)sc_memory_reg.o: $(SD)sc_memory_reg.c
	gcc $^ -I include -c -o $@

$(BD)sc_terminal.o: $(SD)sc_terminal.c
	gcc $^ -I include -c -o $@

$(BD)sc_bigchar.o: $(SD)sc_bigchar.c
	gcc $^ -I include -c -o $@

$(BD)sc_readkey.o: $(SD)sc_readkey.c
	gcc $^ -I include -c -o $@

$(OF): $(OBJS)
	gcc $^ -o $@

clean:
	rm -f $(OBJS) $(OF)
