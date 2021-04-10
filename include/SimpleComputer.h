#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/time.h>

#include "sc_memory_reg.h"
#include "sc_terminal.h"
#include "sc_bigchar.h"
#include "sc_readkey.h"


struct SimpleComputer
{
	int accumulator;
	int instruction_counter;
	
	int should_close;

	int cursor_x;
	int cursor_y;
};

int SimpleComputer_init  ();

void SimpleComputer_print ();

void SimpleComputer_load ();
void SimpleComputer_save ();
void SimpleComputer_exit ();
void SimpleComputer_move (enum keys direction);

void SimpleComputer_show ();
void SimpleComputer_do   ();

void SimpleComputer_run ();

void SimpleComputer_reset  (int signo);
void instructionCounterAdd (int signo);

void SimpleComputer_runapp ();