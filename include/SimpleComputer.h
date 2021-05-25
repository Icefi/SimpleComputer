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
	int to_update;
};

int SimpleComputer_init  ();

void SimpleComputer_print ();

void SimpleComputer_load ();
void SimpleComputer_save ();
void SimpleComputer_exit ();
void SimpleComputer_move (enum keys direction);
void SimpleComputer_accumulator ();
void SimpleComputer_instrCounter ();

void SimpleComputer_show ();
void SimpleComputer_do   ();

void SimpleComputer_run ();

void SimpleComputer_reset  (int signo);
void timer (int signo);

void SimpleComputer_runapp ();

/*** Simple Computer Commands ***/

/** input/output **/

int sc_READ (int);

int sc_WRITE (int);

/** load/store **/

int sc_LOAD (int);

int sc_STORE (int);
/** arithmetic **/

int sc_ADD (int);

int sc_ADDC (int);

int sc_SUB (int);

int sc_SUBC (int);

int sc_DIVIDE (int);

int sc_MUL (int);

int sc_NEG (int);

/** Leaps **/

int sc_JUMP (int);

int sc_JNEG (int);

int sc_JZ (int);

int sc_JNS (int);
int sc_JC (int);

int sc_JNC (int);

int sc_JP (int);

int sc_JNP (int);
/** Stop **/

int sc_HALT ( );

/** Logic **/

int sc_NOT (int);
int sc_AND (int);

int sc_OR  (int);

int sc_XOR (int);

/** Logic and ciclyc shifts **/

/* logic shift */
int sc_CHL (int);

int sc_SHR (int);

/* Ciclyc shift */

int sc_RCL (int);

int sc_RCR (int);

/* Logic value shift */

int sc_LOGLC (int);

int sc_LOGRC (int);

/*  Ciclyc value shift */

int sc_RCCL (int);

int sc_RCCR (int);

/** Replacing **/

int sc_MOVA (int);

int sc_MOVR (int);

int sc_MOVCA (int);

int sc_MOVCR (int);

/** Processor Units **/

int sc_ALU (int, int);

void sc_CU ( void );
