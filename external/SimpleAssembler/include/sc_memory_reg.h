#ifndef SC_MEMORY_REG_H
#define SC_MEMORY_REG_H

#define P 1 // Переполнение
#define O 2 // Деление на 0
#define M 3 // Выход за память
#define T 4 // Игнорирование импульсов
#define E 5 // неверная команда

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
