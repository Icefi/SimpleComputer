#include "sc_readkey.h"

int rk_readkey (enum keys* key)
{
	  rk_mytermsave ("res/Terminal/term.bin");

    struct termios option;
    char buf [ ] = " \0";

	  if (key == NULL)                                 return 0;
    if ( tcgetattr (STDIN_FILENO, &option))          return 0;
    if ( !rk_mytermregime (0, 0, 1, 0, 1))           return 0;
    if ( read (STDIN_FILENO, buf, 1) < 0)            return 0;
    if ( tcsetattr (STDIN_FILENO, TCSANOW, &option)) return 0;

  	if      (strcmp (buf , "q"    ) == 0) *key = rk_q;
  	else if (strcmp (buf , "w"    ) == 0) *key = rk_w;
  	else if (strcmp (buf , "e"    ) == 0) *key = rk_e;
  	else if (strcmp (buf , "r"    ) == 0) *key = rk_r;
  	else if (strcmp (buf , "t"    ) == 0) *key = rk_t;
  	else if (strcmp (buf , "y"    ) == 0) *key = rk_y;
  	else if (strcmp (buf , "u"    ) == 0) *key = rk_u;
  	else if (strcmp (buf , "i"    ) == 0) *key = rk_i;
  	else if (strcmp (buf , "o"    ) == 0) *key = rk_o;
  	else if (strcmp (buf , "p"    ) == 0) *key = rk_p;
  	else if (strcmp (buf , "a"    ) == 0) *key = rk_a;
  	else if (strcmp (buf , "s"    ) == 0) *key = rk_s;
  	else if (strcmp (buf , "d"    ) == 0) *key = rk_d;
  	else if (strcmp (buf , "f"    ) == 0) *key = rk_f;
  	else if (strcmp (buf , "g"    ) == 0) *key = rk_g;
  	else if (strcmp (buf , "h"    ) == 0) *key = rk_h;
  	else if (strcmp (buf , "j"    ) == 0) *key = rk_j;
  	else if (strcmp (buf , "k"    ) == 0) *key = rk_k;
  	else if (strcmp (buf , "l"    ) == 0) *key = rk_l;
  	else if (strcmp (buf , "z"    ) == 0) *key = rk_z;
  	else if (strcmp (buf , "x"    ) == 0) *key = rk_x;
  	else if (strcmp (buf , "c"    ) == 0) *key = rk_c;
  	else if (strcmp (buf , "v"    ) == 0) *key = rk_v;
  	else if (strcmp (buf , "b"    ) == 0) *key = rk_b;
  	else if (strcmp (buf , "n"    ) == 0) *key = rk_n;
  	else if (strcmp (buf , "m"    ) == 0) *key = rk_m;

  	else if (strcmp (buf , " "    ) == 0) *key = rk_space;
  	else if (strcmp (buf , "\n"   ) == 0) *key = rk_enter;

    else if (strcmp (buf, "\e[15~") == 0) *key = rk_f5;
    else if (strcmp (buf, "\e[17~") == 0) *key = rk_f6;

    else if (strcmp (buf, "\e[A"  ) == 0) *key = rk_up;
    else if (strcmp (buf, "\e[B"  ) == 0) *key = rk_down;
    else if (strcmp (buf, "\e[C"  ) == 0) *key = rk_left;
    else if (strcmp (buf, "\e[D"  ) == 0) *key = rk_right;

    else                                  *key = rk_other;

    rk_mytermrestore ("res/Terminal/term.bin");

    return 1;
}

int rk_mytermregime  (int regime, int vtime, int vmin, int echo, int sigint)
{
    struct termios options;

    if (tcgetattr (STDIN_FILENO, &options)) return 0;

	/* non-canonic mode */
    if (regime == 0) {
    	  options.c_lflag &= ~ICANON;

        options.c_cc [VTIME] = vtime;
        options.c_cc [VMIN]  = vmin;

        if      (echo == 1)   options.c_lflag |=  ECHO;
        else if (echo == 0)   options.c_lflag &= ~ECHO;
        else                  return 0;

        if      (sigint == 1) options.c_lflag |=  ISIG;
        else if (sigint == 0) options.c_lflag &= ~ISIG;
        else                  return 0;

    /* canonic mode */
    } else if (regime == 1) {
    	options.c_lflag |= ICANON;
    } else {
    	return 0;
    }

    tcsetattr (STDIN_FILENO, TCSANOW, &options);

    return 1;
}

int rk_mytermsave    (const char* file_name)
{
    struct termios options;
    FILE* file = fopen (file_name, "wb");

    if (tcgetattr (STDIN_FILENO, &options)) return 0;

    if (!file) {
        printf ("Simple Computer Error: File \"%s\" does not exist!\n", file_name);
        return 0;
    }

    fwrite (&options, sizeof (struct termios), 1, file);
    fclose (file);

    return 1;
}

int rk_mytermrestore (const char* file_name)
{
    FILE* file = fopen (file_name, "rb");

    if (!file) {
        printf ("Simple Computer Error: File \"%s\" does not exist!\n", file_name);
        return 0;
    }

    struct termios options;
    int cnt = fread (&options, sizeof (struct termios), 1, file);
    fclose (file);

    if (cnt > 0) return !tcsetattr (STDIN_FILENO, TCSAFLUSH, &options);
    else         return 0;
}
