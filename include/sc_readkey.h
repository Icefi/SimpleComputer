#ifndef SC_READKEY_H
#define SC_READKEY_H

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

enum keys
{
    rk_l,
    rk_s,
    rk_e,
    rk_r,
    rk_t,
    rk_i,
    
    rk_space,
    rk_enter,

    rk_f5,
    rk_f6,
    rk_up,
    rk_down,
    rk_left,
    rk_right,

    rk_other,
};

int rk_readkey       (enum keys *);

int rk_mytermsave    (const char*);

int rk_mytermrestore (const char*);

int rk_mytermregime  (int regime, int vtime, int vmin, int echo, int sigint);

#endif
