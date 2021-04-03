#ifndef SC_MEMORY_REG_H
#define SC_MEMORY_REG_H

#define P 1
#define O 2
#define M 3
#define T 4
#define E 5

/* MEMORY CONTROLLER */

int sc_memory_init ();

int sc_memory_set (int, int);

int sc_memory_get (int, int*);

int sc_memory_save (const char*);

int sc_memory_load (const char*);

/* REGISTER CONTROLLER */

int sc_reg_init ();

int sc_reg_set (int, unsigned int);

int sc_reg_get (int, int*);

int sc_reg_print ();

/* COMMAND CONTROLLER */

int sc_command_encode (int, int, int*);

int sc_command_decode (int, int*, int*);

#endif