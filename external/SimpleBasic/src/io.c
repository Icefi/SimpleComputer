#include <stdio.h>
#include <stdlib.h>

#include "io.h"

char * get_content (const char * path)
{
	FILE * file = fopen (path, "rb");

	char * buffer = NULL;
	long int length;

	if (file) {
		fseek (file, 0, SEEK_END);

		length = ftell (file);

		fseek (file, 0, SEEK_SET);

		buffer = malloc (length * length * sizeof (char));

		if (buffer) fread (buffer, 1, length, file);

		fclose (file);

		return buffer;
	} else {
		printf ("Unexisting file with name \"%s\"\n", path);
		exit (2);
	}
}