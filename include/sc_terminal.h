#ifndef SC_TERMINAL_H
#define SC_TERMINAL_H

/* BASE functions */

enum Colors {
	black = 0,
	red = 1,
	green = 2,
	yellow = 3,
	blue = 4,
	pink = 5,
	paleblue = 6,
	white = 7,
};

int mt_clrscr (void);

int mt_gotoXY (int, int);

int mt_getscreensize (int*, int*);

int mt_restorecolors (void);

int mt_setfgcolor (enum Colors);

int mt_setbgcolor (enum Colors);

#endif
