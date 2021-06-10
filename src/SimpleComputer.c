#include "SimpleComputer.h"

/* application functions */

struct SimpleComputer SC;

int bc_num [10][2];
int bc_plus    [2];

void SimpleComputer_print ()
{
	int temp;
	for (int i = 0; i < 10; ++i) {
		for (int j = 0; j < 10; ++j) {

			sc_memory_get (i * 10 + j, &temp);

			mt_gotoXY (2 + j * 6, 2 + i);

			if (SC.instruction_counter == (i * 10 + j)) {

				mt_setfgcolor (black);
				mt_setbgcolor (white);
				printf ("+%d%d%d%d ", temp / 1000 % 10, temp / 100 % 10, temp / 10 % 10, temp % 10);
				mt_restorecolors ();

			} else {
				printf ("+%d%d%d%d ", temp / 1000 % 10, temp / 100 % 10, temp / 10 % 10, temp % 10);
			}
		}

		printf ("\n");
	}

	printf ("\n");
}

void SimpleComputer_load ()
{
	SC.instruction_counter = 0;

	int cur; sc_reg_get (T, &cur);
	sc_reg_set (T, 1);

	char file_name [255];

	mt_gotoXY (1, 23); printf ("Enter file address:\n");

	fflush (stdin);
	fgets (file_name, 255, stdin);

	for (int i = 0; i < 255; i++)
		if (file_name[i] == '\n') file_name[i] = '\0';

	if (sc_memory_load (file_name))
		printf ("Loading...\n");
	else
		printf ("File does not exist!\n");

	sleep (1);

	sc_reg_set (T, cur);
}

void SimpleComputer_save ()
{	
	SC.instruction_counter = 0;

	int cur; sc_reg_get (T, &cur);
	sc_reg_set (T, 1);

	char file_name [255];

	rk_mytermregime (1, 0, 1, 1, 1);
	mt_gotoXY (1, 23); printf ("\nEnter file address: ");

	fflush (stdin);
	fgets (file_name, 255, stdin);

	for (int i = 0; i < 255; i++)
		if (file_name[i] == '\n') file_name[i] = '\0';

	sc_memory_save (file_name);

	if (sc_memory_save (file_name))
		printf ("Saving...\n");
	else
		printf ("File does not exist!\n");

	sleep (1);

	sc_reg_set (T, cur);
}

int SimpleComputer_init ()
{
	/* Loading bigchars */
	bc_read (open ("res/bigchar/bc_0.bin", O_RDONLY), bc_num [0], 1, NULL);
	bc_read (open ("res/bigchar/bc_1.bin", O_RDONLY), bc_num [1], 1, NULL);
	bc_read (open ("res/bigchar/bc_2.bin", O_RDONLY), bc_num [2], 1, NULL);
	bc_read (open ("res/bigchar/bc_3.bin", O_RDONLY), bc_num [3], 1, NULL);
	bc_read (open ("res/bigchar/bc_4.bin", O_RDONLY), bc_num [4], 1, NULL);
	bc_read (open ("res/bigchar/bc_5.bin", O_RDONLY), bc_num [5], 1, NULL);
	bc_read (open ("res/bigchar/bc_6.bin", O_RDONLY), bc_num [6], 1, NULL);
	bc_read (open ("res/bigchar/bc_7.bin", O_RDONLY), bc_num [7], 1, NULL);
	bc_read (open ("res/bigchar/bc_8.bin", O_RDONLY), bc_num [8], 1, NULL);
	bc_read (open ("res/bigchar/bc_9.bin", O_RDONLY), bc_num [9], 1, NULL);
	bc_read (open ("res/bigchar/bc_plus.bin", O_RDONLY), bc_plus, 1, NULL);

	/* initialising memory */
	if (!sc_memory_init ()) {
		printf ("SimpleComputer error: memory cannot be set\n");
		return 0;
	}

	/* initialising register */
	if (!sc_reg_init ()) {
		printf ("SimpleComputer error: register cannot be set\n");
		return 0;
	}

	sc_reg_set (T, 1);

	/* set default variables */
	SC.accumulator         = 0;
	SC.instruction_counter = 0;
	SC.should_close        = 0;
	SC.to_update           = 1;

	return 1;
}

void SimpleComputer_exit ()
{
	int cur; sc_reg_get (T, &cur);
	sc_reg_set (T, 1);

	char key;

	mt_gotoXY (1, 25); printf ("Quit [y / n] ? ");
	scanf ("%c", &key);

	if (key == 'y') SC.should_close = 1;
	if (key == 'n') SC.should_close = 0;

	sc_reg_set (T, cur);
}

void SimpleComputer_reset (int signo)
{
	if (!sc_memory_init ()) return;
	if (!sc_reg_init    ()) return;

	sc_reg_set (T, 1);

	SC.accumulator         = 0;
	SC.instruction_counter = 0;
}

void SimpleComputer_run ()
{
	int key;
	sc_reg_get (T, &key);
	sc_reg_set (T, key == 0 ? 1 : 0);
}

void SimpleComputer_show ()
{
	/* preparing to printing */

	mt_clrscr ();

	/* printing memory */

	bc_box (1, 1, 62, 12);
	mt_gotoXY (2, 2);
	SimpleComputer_print ();

	/* printing menu widgets */

	bc_box (63, 1,  85, 3);
	bc_box (63, 4,  85, 6);
	bc_box (63, 7,  85, 9);
	bc_box (63, 10, 85, 12);

	/* printing menu Labels*/

	mt_gotoXY (68, 1);  printf (" accumulator ");
	mt_gotoXY (64, 4);  printf (" instruction counter ");
	mt_gotoXY (69, 7);  printf (" operation ");
	mt_gotoXY (71, 10); printf (" flags ");

	/* printing menu values */

	mt_gotoXY (64, 2); printf ("%20d", SC.accumulator);
	mt_gotoXY (64, 5); printf ("%20d", SC.instruction_counter);

	/* printing flags */

	int SC_P = 0, SC_O = 0, SC_M = 0, SC_T = 0, SC_E = 0;

	sc_reg_get (P, &SC_P);
	sc_reg_get (O, &SC_O);
	sc_reg_get (M, &SC_M);
	sc_reg_get (T, &SC_T);
	sc_reg_get (E, &SC_T);


	mt_gotoXY (70, 11); printf ("%d %d %d %d %d", SC_P, SC_O, SC_M, SC_T, SC_E);

	/* printing screen widget */

	bc_box (1, 13, 46, 22);
	bc_box (47, 13, 85, 22);

	/* printing screen's bigchars */

	int temp = 0;
	sc_memory_get (SC.instruction_counter, &temp);

	bc_print (bc_plus, 2,  14, red, blue);
	bc_print (bc_num [temp / 1000 % 10], 11, 14, red, blue);
	bc_print (bc_num [temp / 100 % 10], 20, 14, red, blue);
	bc_print (bc_num [temp / 10 % 10], 29, 14, red, blue);
	bc_print (bc_num [temp % 10], 38, 14, red, blue);

	/* printing keys */

	mt_gotoXY (52, 13); printf (" keys: ");
	mt_gotoXY (50, 14); printf ("l  - load");
	mt_gotoXY (50, 15); printf ("s  - save");
	mt_gotoXY (50, 16); printf ("r  - run");
	mt_gotoXY (50, 17); printf ("t  - step");
	mt_gotoXY (50, 18); printf ("i  - reset");
	mt_gotoXY (50, 19); printf ("e  - exit");
	mt_gotoXY (50, 20); printf ("f5 - accumulator");
	mt_gotoXY (50, 21); printf ("f6 - instruction counter");

	mt_gotoXY (1, 23);

	printf ("\n");
}

void SimpleComputer_accumulator ()
{
	printf ("Enter new value of accumulator >> ");
	scanf ("%d", &SC.accumulator);
	fflush (stdin);
}

void SimpleComputer_instrCounter ()
{
	printf ("Enter new value of Instruction Counter >> ");
	scanf ("%d", &SC.instruction_counter);
	fflush (stdin);
}

void SimpleComputer_step ()
{
	sc_CU ();
	SC.instruction_counter ++;
}

void SimpleComputer_do ()
{
	enum keys K;
	int key;
	sc_reg_get (T, &key);

	rk_readkey (&K);

	switch (K) {
		case rk_r:
			SimpleComputer_run  ();
			break;
			
		case rk_t:
			SimpleComputer_step ();
			break;

		case rk_e:
			SimpleComputer_exit ();
			break;

	}

	if (key == 0) return;

	switch (K) {
		case rk_l:
			SimpleComputer_load  ();
			break;

		case rk_s:
			SimpleComputer_save  ();
			break;

		case rk_f5:
			SimpleComputer_accumulator ();
			break;

		case rk_f6:
			SimpleComputer_instrCounter ();
			break;

		case rk_i:
			raise (SIGUSR1);
			break;
	}
	
	SimpleComputer_show ();
}

void timer (int signo)
{
	int temp = 0;
	sc_reg_get (T, &temp);

	if (temp == 0) {
		sc_CU ();
   		SC.instruction_counter++;
   		SimpleComputer_show ();
  	}
}

void SimpleComputer_runapp ()
{
	struct itimerval nval;
	signal (SIGALRM, timer);
	signal (SIGUSR1, SimpleComputer_reset);

	nval.it_interval.tv_sec = 0;
	nval.it_interval.tv_usec = 50000;
	nval.it_value.tv_sec = 1;
	nval.it_value.tv_usec = 0;

	setitimer (ITIMER_REAL, &nval, NULL);
	
	SimpleComputer_show ();
	while (SC.should_close == 0) {
		//SimpleComputer_show ();
		if (SC.to_update) SimpleComputer_do ();
	}
}

/*** Simple Computer Commands ***/

/** input/output **/

int sc_READ (int address)
{
	int upt;
	sc_reg_get (T, &upt);
	
	SC.to_update = 0;
	sc_reg_set (T, 1);
	
	int temp = 0;
	printf ("INPUT >> ");
	
	scanf ("%d", &temp);
	
	SC.to_update = 1;
	sc_reg_set (T, upt);
	
	if (temp > 0x7FFF) {
		sc_reg_set (P, 1);
		return 0;
	} else {
		sc_memory_set (address, temp);
		return 1;
	}
}

int sc_WRITE (int address)
{
	int temp = 0;
	sc_memory_get (address, &temp);

	printf ("%d", temp);
	return 1;
}

/** load/store **/

int sc_LOAD (int address)
{
	int temp = 0;
	if (sc_memory_get (address, &temp) == 0) return 0;

	SC.accumulator = temp;
	return 1;
}

int sc_STORE (int address)
{
	return sc_memory_set (address, SC.accumulator);
}

/** arithmetic **/

int sc_ADD (int address)
{
	int temp = 0;
	sc_memory_get (address, &temp);

	temp = SC.accumulator + temp;

	if (temp > 0x7FFF) {
		sc_reg_set (P, 1);
		return 0;
    }

    SC.accumulator = temp;

	return 1;
}

int sc_ADDC (int address)
{
	int temp1 = 0;
	sc_memory_get (address, &temp1);

	int temp2 = 0;
	sc_memory_get (SC.accumulator, &temp2);

	temp1 = temp1 + temp2;

	if (temp1 > 0x7FFF) {
		sc_reg_set (P, 1);
		return 0;
	}

	SC.accumulator = temp1;

	return 1;
}

int sc_SUB (int address)
{
	int temp = 0;
	sc_memory_get (address, &temp);

	temp = SC.accumulator - temp;

	if (temp > 0x7FFF) {
		sc_reg_set (P, 1);
		return 0;
    }

    SC.accumulator = temp;

	return 1;
}

int sc_SUBC (int address)
{
	int temp1 = 0;
	sc_memory_get (address, &temp1);

	int temp2 = 0;
	sc_memory_get (SC.accumulator, &temp2);

	temp1 = temp1 - temp2;

	if (temp1 > 0x7FFF) {
		sc_reg_set (P, 1);
		return 0;
    }

    SC.accumulator = temp1;

	return 1;
}

int sc_DIVIDE (int address)
{
	int temp = 0;
	sc_memory_get (address, &temp);

	if (temp == 0){
		sc_reg_set (O, 1);
		SC.should_close = 1;
		return 0;
	}

	temp = SC.accumulator / temp;

	return 1;
}

int sc_MUL (int address)
{
	int temp = 0;
	sc_memory_get (address, &temp);

	temp = SC.accumulator * temp;

	if (temp > 0x7FFF) {
		sc_reg_set (P, 1);
		return 0;
	}

	SC.accumulator = temp;

	return 1;
}

int sc_NEG (int address)
{
	int temp = 0;
	sc_memory_get (address, &temp);

	SC.accumulator = 1 + ~temp;
}

/** Leaps **/

int sc_JUMP (int address)
{
	SC.instruction_counter = address;
	return 1;
}

int sc_JNEG (int address)
{
	if (SC.accumulator < 0)
		return sc_JUMP (address);

	return 1;
}

int sc_JZ (int address)
{
	if (SC.accumulator == 0)
		return sc_JUMP (address);

	return 1;
}

int sc_JNS (int address)
{
	if (SC.accumulator > 0)
		return sc_JUMP (address);

	return 1;
}

int sc_JC (int address)
{
	if (SC.accumulator > 0x7FFF)
		return sc_JUMP (address);

	return 1;
}

int sc_JNC (int address)
{
	if (SC.accumulator < 0x7FFE)
		return sc_JUMP (address);

	return 1;
}

int sc_JP (int address)
{
	if (SC.accumulator % 2 == 0)
		return sc_JUMP (address);

	return 1;
}

int sc_JNP (int address)
{
	if (SC.accumulator % 2 == 1)
		return sc_JUMP (address);

	return 1;
}

/** Stop **/

int sc_HALT ( )
{
	
	sc_reg_set (T, 1);
	SC.instruction_counter = -1;
	
	return 1;
}

/** Logic **/

int sc_NOT (int address)
{
	return sc_memory_set (address, SC.accumulator == 0);
}

int sc_AND (int address)
{
	int temp = 0;

	if (sc_memory_get (address, &temp) == 0) return 0;

	SC.accumulator = SC.accumulator && temp;

	return 1;
}

int sc_OR  (int address)
{
	int temp = 0;

	if (sc_memory_get (address, &temp) == 0) return 0;

	SC.accumulator = SC.accumulator || temp;

	return 1;
}

int sc_XOR (int address)
{
	int temp = 0;

	if (sc_memory_get (address, &temp) == 0) return 0;

	SC.accumulator = (SC.accumulator != 0) ^ (temp != 0);

	return 1;
}

/** Logic and ciclyc shifts **/

/* logic shift */
int sc_CHL (int address)
{
	int temp = 0;

	if (sc_memory_get (address, &temp) == 0) return 0;

	SC.accumulator = 0x7FFF & ( temp << SC.accumulator );

	return 1;
}

int sc_SHR (int address)
{
	int temp = 0;

	if (sc_memory_get (address, &temp) == 0) return 0;

	SC.accumulator = 0x7FFF & ( temp >> SC.accumulator );

	return 1;
}

/* Ciclyc shift */

int sc_RCL (int address)
{
	int temp1 = 0;
	if (sc_memory_get (address, &temp1) == 0) return 0;

	int temp2 = 0;
	if (sc_memory_get (SC.accumulator, &temp2) == 0) return 0;

	SC.accumulator = (temp1 << temp2) | (temp1 >> (15 - temp2));

	return 1;
}

int sc_RCR (int address)
{
	int temp1 = 0;
	if (sc_memory_get (address, &temp1) == 0) return 0;

	int temp2 = 0;
	if (sc_memory_get (SC.accumulator, &temp2) == 0) return 0;

	SC.accumulator = (temp1 >> temp2) | (temp1 << (15 - temp2));

	return 1;
}

/* Logic value shift */

int sc_LOGLC (int address)
{
	int temp = 0;
	sc_memory_get (address, &temp);

	SC.accumulator = temp << SC.accumulator;

	return 1;
}

int sc_LOGRC (int address)
{
	int temp = 0;
	sc_memory_get (address, &temp);

	SC.accumulator = temp >> SC.accumulator;

	return 1;
}

/*  Ciclyc value shift */

int sc_RCCL (int address)
{
	int temp = 0;
	sc_memory_get (address, &temp);

	SC.accumulator = (temp << SC.accumulator) | (temp >> (15 - SC.accumulator));

	return 1;
}

int sc_RCCR (int address)
{
	int temp = 0;
	sc_memory_get (address, &temp);

	SC.accumulator = (temp >> SC.accumulator) | (temp << (15 - SC.accumulator));

	return 1;
}

/** Replacing **/

int sc_MOVA (int address)
{
	int source_val = 0;
	if (sc_memory_get (address, &source_val) == 0) return 0;

	if (sc_memory_set (SC.accumulator, source_val) == 0) return 0;

	return 1;
}

int sc_MOVR (int address)
{
	int source_val = 0;
	if (sc_memory_get (SC.accumulator, &source_val) == 0) return 0;

	if (sc_memory_set (address, source_val) == 0) return 0;

	return 1;
}

int sc_MOVCA (int address)
{
	int source_val = 0;
	if (sc_memory_get (address, &source_val) == 0) return 0;

	int dest_ptr = 0;
	if (sc_memory_get (SC.accumulator, &dest_ptr) == 0) return 0;

	int dest_add = 0;
	if (sc_memory_get (dest_add, &dest_ptr) == 0) return 0;

	return sc_memory_set (dest_add, source_val);
}

int sc_MOVCR (int address)
{
	int dest_add = 0;
	if (sc_memory_get (address, &dest_add) == 0) return 0;

	int source_add = 0;
	if (sc_memory_get (SC.accumulator, &source_add) == 0) return 0;

	int source_val = 0;
	if (sc_memory_get (source_add, &source_add) == 0) return 0;

	return sc_memory_set (dest_add, source_val);
}

/** Processor Units **/

int sc_ALU (int command, int operand)
{
	switch (command) {
		/* command 'ADD' */
		case 30:
			sc_ADD (operand);
			break;

		/* command 'SUB' */
		case 31:
			sc_SUB (operand);
			break;

		/* command 'DIVIDE' */
		case 32:
			sc_DIVIDE (operand);
			break;

		/* command 'MUL' */
		case 33:
			sc_MUL (operand);
			break;

		/* command 'NOT' */
		case 51:
			sc_NOT (operand);
			break;

		/* command 'AND' */
		case 52:
			sc_AND (operand);
			break;

		/* command 'OR' */
		case 53:
			sc_OR (operand);
			break;

		/* command 'XOR' */
		case 54:
			sc_XOR (operand);
			break;

		/* command 'CHL' */
		case 60:
			sc_CHL (operand);
			break;

		/* command 'SHR' */
		case 61:
			sc_SHR (operand);
			break;

		/* command 'RCL' */
		case 62:
			sc_RCL (operand);
			break;

		/* command 'RCR' */
		case 63:
			sc_RCR (operand);
			break;

		/* command 'NEG' */
		case 64:
			sc_NEG (operand);
			break;

		/* command 'ADDC' */
		case 65:
			sc_ADDC (operand);
			break;

		/* command 'SUBC' */
		case 66:
			sc_SUBC (operand);
			break;

		/* command 'LOGLC' */
		case 67:
			sc_LOGLC (operand);
			break;

		/* command 'LOGRC' */
		case 68:
			sc_LOGRC (operand);
			break;

		/* command 'RCCL' */
		case 69:
			sc_RCCL (operand);
			break;

		/* command 'RCCR' */
		case 70:
			sc_RCCR (operand);
			break;
	}
}

void sc_CU ( )
{
	int temp = 0;

	int command = 0, operand = 0;

	if ((SC.instruction_counter < 0) || (SC.instruction_counter > 99)) {
		SC.instruction_counter = 0;
		return;
	}
	sc_memory_get (SC.instruction_counter, &temp);
	sc_command_decode (temp, &command, &operand);

	switch (command) {
		case 10:
			sc_READ (operand);
			break;
			
		case 11:
			sc_WRITE (operand);
			break;
			
		case 20:
			sc_LOAD (operand);
			break;
			
		case 21:
			sc_STORE (operand);
			break;
	
		/* command 'JUMP' */
		case 40:
			sc_JUMP (operand - 1);
			break;

		/* command 'JNEG' */
		case 41:
			sc_JNEG (operand - 1);
			break;

		/* command 'JZ' */
		case 42:
			sc_JZ (operand - 1);
			break;

        /* command 'HALT' */
		case 43:
			sc_HALT ();
			break;

		/* command 'JNS' */
		case 55:
			sc_JNS (operand - 1);
			break;

		/* command 'JC' */
		case 56:
			sc_JC (operand - 1);
			break;

		/* command 'JNC' */
		case 57:
			sc_JNC (operand - 1);
			break;

		/* command 'JP' */
		case 58:
			sc_JP (operand - 1);
			break;

		/* command 'JNP' */
		case 59:
			sc_JNP (operand - 1);
			break;

		/* command 'MOVA' */
		case 71:
			sc_MOVA (operand);
			break;

		/* command 'MOVR' */
		case 72:
			sc_MOVR (operand);
			break;

		/* command 'MOVCA' */
		case 73:
			sc_MOVCA (operand);
			break;

		/* command 'MOVCR' */
		case 74:
			sc_MOVCR (operand);
			break;

		default:
			sc_ALU (command, operand);
	}
}
