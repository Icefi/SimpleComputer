#include "SimpleComputer.h"

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

			if (((i + 1) == SC.cursor_y) && ((j + 1) == SC.cursor_x)) {

				mt_setfgcolor (white);
				mt_setbgcolor (black);
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
	int cur; sc_reg_get (T, &cur);
	sc_reg_set (T, 1);

	char file_name [255];
	
	mt_gotoXY (1, 23); printf ("Enter file address:\n");
	
	fflush (stdin);
	fgets (file_name, 255, stdin);

	if (sc_memory_load (file_name))
		printf ("Loading...\n");
	else
		printf ("File does not exist!\n");

	sleep (1);

	sc_reg_set (T, cur);
}

void SimpleComputer_save ()
{
	int cur; sc_reg_get (T, &cur);
	sc_reg_set (T, 1);

	char file_name [255];
	
	rk_mytermregime (1, 0, 1, 1, 1);
	mt_gotoXY (1, 23); printf ("\nEnter file address: ");

	fflush (stdin);
	fgets (file_name, 255, stdin);

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
	SC.cursor_x = 1;
	SC.cursor_y = 1;
	SC.accumulator         = 0;
	SC.instruction_counter = 0;
	SC.should_close        = 0;

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

void SimpleComputer_move (enum keys direction)
{
	int d_x = 0, d_y = 0;

	switch (direction) {
		case rk_left:
			d_x = -1;
			break;
		case rk_right:
			d_x =  1;
			break;
		case rk_up:
			d_y = -1;
			break;
		case rk_down:
			d_y =  1;
			break;
	}

	SC.cursor_x += d_x;
	SC.cursor_y += d_y;

	if (SC.cursor_x <  1) SC.cursor_x = 10;
	if (SC.cursor_x > 10) SC.cursor_x =  1;
	if (SC.cursor_y <  1) SC.cursor_y = 10;
	if (SC.cursor_y > 10) SC.cursor_y =  1;
}

void SimpleComputer_ChangeCell ()
{
	int temp = 0;
	printf ("Enter new value >> ");
	scanf ("%d", &temp);
	sc_memory_set ((SC.cursor_y - 1) * 10 + SC.cursor_x - 1, temp);
	fflush (stdin);
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

	int SC_P, SC_O, SC_M, SC_T, SC_E;

	sc_reg_get (P, &SC_P);
	sc_reg_get (O, &SC_O);
	sc_reg_get (M, &SC_M);
	sc_reg_get (T, &SC_T);
	sc_reg_get (E, &SC_T);

	mt_gotoXY (68, 11); if (SC_P) printf ("P\n");
	mt_gotoXY (70, 11); if (SC_O) printf ("O\n");
	mt_gotoXY (72, 11); if (SC_M) printf ("M\n");
	mt_gotoXY (74, 11); if (SC_T) printf ("T\n");
	mt_gotoXY (76, 11); if (SC_E) printf ("E\n");

	/* printing screen widget */

	bc_box (1, 13, 46, 22);
	bc_box (47, 13, 85, 22);

	/* printing screen's bigchars */

	int temp = 0;
	sc_memory_get ((SC.cursor_y - 1) * 10 + SC.cursor_x - 1, &temp);

	bc_print (bc_plus, 2,  14, white, blue);
	bc_print (bc_num [temp / 1000 % 10], 11, 14, white, blue);
	bc_print (bc_num [temp / 100 % 10], 20, 14, white, blue);
	bc_print (bc_num [temp / 10 % 10], 29, 14, white, blue);
	bc_print (bc_num [temp % 10], 38, 14, white, blue);

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

void SimpleComputer_do ()
{
	enum keys K;
	int key;
	sc_reg_get (T, &key);
	
	rk_readkey (&K);
	
	switch (K) {
		case rk_r:
			SimpleComputer_run ();
			break;

		case rk_e:
			SimpleComputer_exit ();
			break;

		case rk_left:
			SimpleComputer_move (rk_left);
			break;

		case rk_right:
			SimpleComputer_move (rk_right);
			break;

		case rk_up:
			SimpleComputer_move (rk_up);
			break;

		case rk_down:
			SimpleComputer_move (rk_down);
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

		case rk_enter:
			SimpleComputer_ChangeCell ();
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
}

void instructionCounterAdd (int signo)
{
	int flag; sc_reg_get (T, &flag);
	if (flag == 0) {
		SC.instruction_counter++;
		SimpleComputer_show ();
	}

}

void SimpleComputer_runapp ()
{
	struct itimerval nval, oval;
	signal (SIGALRM, instructionCounterAdd);
	signal (SIGUSR1, SimpleComputer_reset);

	nval.it_interval.tv_sec = 3;
	nval.it_interval.tv_usec = 500;
	nval.it_value.tv_sec = 1;
	nval.it_value.tv_usec = 0;

	setitimer (ITIMER_REAL, &nval, &oval);

	while (SC.should_close == 0) {
		SimpleComputer_show ();
		SimpleComputer_do ();
	}
	
}