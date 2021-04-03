#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

#include "sc_memory_reg.h"
#include "sc_terminal.h"
#include "sc_bigchar.h"
#include "sc_readkey.h"

int memory_print (int width)
{
		int temp;
		for (int i = 0; i < 100; ++i) {
				sc_memory_get (i, &temp);
				if (i % width == 0) printf ("\n");

				printf (" %4d", temp);
		}

		printf ("\n");

		return 1;
}

int main ()
{
		enum keys k;

		rk_readkey (&k);

		printf ("key is %d\n", k);
	
    return 0;
}
