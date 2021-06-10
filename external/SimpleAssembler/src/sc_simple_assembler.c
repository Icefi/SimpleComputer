#include "sc_simple_assembler.h"

void encode (char* str)
{
    char* istr = strtok (str, " ;\n");

    int addr;
    int code;
    int operand;

    int i = 0;
    while (istr != NULL) {

        switch (i) {
            case 0:
                addr = atoi (istr);

                if ( (addr < 0) || (addr > 99) ) {
                    fprintf (stderr, "Value Error: address cannot be %d!\n", addr);
                    exit (0);
                }

                break;

            case 1:
                /* input / output */

                if        (strcmp (istr, "READ")  == 0) {
                    code = 10;
                } else if (strcmp (istr, "WRITE") == 0) {
                    code = 11;

                /* load / store */

                } else if (strcmp (istr, "LOAD")  == 0) {
                    code = 20;
                } else if (strcmp (istr, "STORE") == 0) {
                    code = 21;

                /* Arithmetic */

                } else if (strcmp (istr, "ADD")    == 0) {
                    code = 30;
                } else if (strcmp (istr, "SUB")    == 0) {
                    code = 31;
                } else if (strcmp (istr, "DIVIDE") == 0) {
                    code = 32;
                } else if (strcmp (istr, "MUL")    == 0) {
                    code = 33;

				/* Send control operations */

                } else if (strcmp (istr, "JUMP") == 0) {
                    code = 40;
                } else if (strcmp (istr, "JNEG") == 0) {
                    code = 41;
                } else if (strcmp (istr, "JZ")   == 0) {
                    code = 42;
                } else if (strcmp (istr, "HALT") == 0) {
                    code = 43;


				/* Logic */

                } else if (strcmp (istr, "NOT") == 0) {
                    code = 51;
                } else if (strcmp (istr, "AND") == 0) {
                    code = 52;
                } else if (strcmp (istr, "OR")  == 0) {
                    code = 53;
                } else if (strcmp (istr, "XOR") == 0) {
                    code = 54;

                /* New Jumps */
                } else if (strcmp (istr, "JNS") == 0) {
                    code = 55;
                } else if (strcmp (istr, "JC")  == 0) {
                    code = 56;
                } else if (strcmp (istr, "JNC") == 0) {
                    code = 57;
                } else if (strcmp (istr, "JP")  == 0) {
                    code = 58;
                } else if (strcmp (istr, "JNP") == 0) {
                    code = 59;

				/* Shifts */

                } else if (strcmp (istr, "CHL") == 0) {
                    code = 60;
                } else if (strcmp (istr, "SHR") == 0) {
                    code = 61;
                } else if (strcmp (istr, "RCL") == 0) {
                    code = 62;
                } else if (strcmp (istr, "RCR") == 0) {
                    code = 63;
                } else if (strcmp (istr, "NEG") == 0) {
                    code = 64;

				/* Arithmetic 2 */

                } else if (strcmp (istr, "ADDC") == 0) {
                    code = 65;
                } else if (strcmp (istr, "SUBC") == 0) {
                    code = 66;

				/* shifts 2 */

                } else if (strcmp (istr, "LOGLC") == 0) {
                    code = 67;
                } else if (strcmp (istr, "LOGRC") == 0) {
                    code = 68;
                } else if (strcmp (istr, "RCCL")  == 0) {
                    code = 69;
                } else if (strcmp (istr, "RCCR")  == 0) {
                    code = 70;

				/* replace */

                } else if (strcmp (istr, "MOVA")  == 0) {
                    code = 71;
                } else if (strcmp (istr, "MOVR")  == 0) {
                    code = 72;
                } else if (strcmp (istr, "MOVCA") == 0) {
                    code = 73;
                } else if (strcmp (istr, "MOVCR") == 0) {
                    code = 74;

				/* rest */

                } else if (strcmp (istr, "=") == 0) {
                    code = 0;
                } else {
					printf ("Command error: unknown command \"%s\"\n", istr);
					exit (0);
				}

				break;

			case 2:
				operand = atoi (istr);

				if (operand < 0 || operand > 0x7FFF) {
					printf ("Value error: operand \"%d\" incorrect\n", operand);
					exit (0);
				}

				break;

        }

		istr = strtok (NULL, " ;\n");
        i++;
    }

    int val;

	sc_command_encode (code, operand, &val);

    sc_memory_set (addr, val);
}

void translate (const char* file_in, const char* file_out)
{
    /* preparing */

    FILE* fin  = fopen (file_in,  "r");
    if (fin == NULL) {
        printf ("file \"%s\" not found\n", file_in);
        return;
    }

    sc_memory_init ();

    char buf [STR_SIZE];

    for (int i = 0; ; i++) {
        if (fgets (buf, STR_SIZE, fin) == NULL) break;

        encode (buf);
    }

    fclose (fin);

	printf ("Saving memory...\n");

	sc_memory_save (file_out);

	printf ("File \"%s\" translated to \"%s\"\n", file_in, file_out);
}
