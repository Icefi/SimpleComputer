#include <stdio.h>
#include <stdlib.h>
#include "sc_memory_reg.h"

/* MEMORY CONTROLLER */

int sc_mem [100];

int sc_memory_init ()
{
	for (int i = 0; i < 100; i++) sc_mem[i] = 0;

	return 1;
}

int sc_memory_set (int address, int value)
{
	if ((address > 100) || (address < 0)) {
		printf ("\nError: address %d is not available\n", address);
		return 0;
	} else {
		*(sc_mem + address) = value;
		return 1;
	}
}

int sc_memory_get (int address, int* value)
{
	if ((address > 100) || (address < 0)) {
		printf ("Error: address %d is not available\n", address);
		return 0;
	} else {
		if (value != NULL) *value = *(sc_mem + address);
		return 1;
	}
}

int sc_memory_save (const char* file_name)
{
	FILE* file = fopen (file_name, "w");

	if (!file) return 0;

	int res = fwrite (sc_mem, sizeof(int), 100, file);

	fclose (file);

	if (res != 100) {
		sc_reg_set (E, 1);
		return 0;
	} else {
		return 1;
	}
}

int sc_memory_load (const char* file_name)
{
	FILE* file = fopen (file_name, "rb");

	if (!file) return 0;

	int res = fread (sc_mem, sizeof (int), 100, file);

	fclose (file);

	if (res != 100) {
		sc_reg_set (M, 1);
		return 0;
	} else {
		return 1;
	}
}



/* REGISTER CONTROLLER */

__uint32_t sc_reg;

#define REG_SET(a) (1 << (a - 1))

int sc_reg_init ()
{
	sc_reg = 0;
	return 1;
}

int sc_reg_set (int address, unsigned int value)
{
	if (address < 0 || address > 32) return 0;
	
	sc_reg = (value == 0) ? (sc_reg & ~REG_SET(address)) : (sc_reg | REG_SET(address));
	
	return 1;
}

int sc_reg_get (int address, int* value)
{
	if (address < 0 || address > 32) return 0;
		
	*value = (sc_reg >> (address - 1)) & 0x1;
	return 1;
}

int sc_reg_print ()
{
	printf ("REGISTER is ");
	int temp = 0;

	for (int i = 1; i <= 8; i++) {
		sc_reg_get (8 - i + 1, &temp);
		printf ("%d ", temp);
	}

	printf ("\n");

	return 1;
}


/* COMMAND CONTROLLER */

int sc_command_encode (int command, int operand, int* value)
{
	if (value == NULL) {
		sc_reg_set (E, 1);
		return 0;
	}

	*value = ((command & 127) << 7) | (operand & 127);

	return 1;
}

int sc_command_decode (int value, int* command, int* operand)
{
	if ((command == NULL) || (operand == NULL)) {
		sc_reg_set (E, 1);
		return 0;
	}

	*command = (value >> 7) & 127;
	*operand = (value       & 127);

	return 1;
}