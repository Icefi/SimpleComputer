#include <stdio.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "sc_terminal.h"

int mt_clrscr (void)
{
    printf ("\E[H\E[J");
    return 1;
}

int mt_gotoXY (int X, int Y)
{
    printf ("\E[%d;%dH", Y, X);
    return 1;
}

int mt_getscreensize (int* rows, int* cols)
{
    if ((rows == NULL) || (cols == NULL)) return 0;

	struct winsize ws;

    if (!ioctl (1, TIOCGWINSZ, &ws)) {
        *rows = ws.ws_row;
        *cols = ws.ws_col;
        return 1;
    } else {
        return 0;
    }
}

int mt_restorecolors (void)
{
    printf ("\E[39;49m");
    return 1;
}

int mt_setfgcolor (enum Colors color)
{
    printf ("\033[3%dm", color);
    return 1;
}

int mt_setbgcolor (enum Colors color)
{
    printf ("\033[4%dm", color);
    return 1;
}


