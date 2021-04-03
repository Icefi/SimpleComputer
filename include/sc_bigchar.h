#ifndef SC_BIGCHAR_H
#define SC_BIGCHAR_H

#include <stdio.h>
#include <unistd.h>
#include "sc_terminal.h"

#define REC 'a'
#define BR "j"
#define BL "m"
#define TR "k"
#define TL "l"
#define VERT "x"
#define HOR "q"

int bc_printA (const char*);

int bc_box (int, int, int, int);

int bc_print (int [2], int, int, enum Colors, enum Colors);

int bc_set_pos (int*, int, int, int);

int bc_get_pos (int*, int, int, int*);

int bc_write (int, int*, int);

int bc_read (int, int*, int, int*);

#endif