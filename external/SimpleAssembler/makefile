SD = src/
ID = include/
BD = build/

OF = bin/sambr

OBJS = $(BD)main.o $(BD)sc_memory_reg.o $(BD)sc_simple_assembler.o

.PHONY: all clean re

all: $(OF)

re: clean all

$(BD)main.o: $(SD)main.c
	gcc $^ -I include -c -o $@

$(BD)sc_memory_reg.o: $(SD)sc_memory_reg.c
	gcc $^ -I include -c -o $@

$(BD)sc_simple_assembler.o: $(SD)sc_simple_assembler.c
	gcc $^ -I include -c -o $@

$(OF): $(OBJS)
	gcc $^ -o $@

clean:
	rm -f $(OBJS) $(OF)
