#ifndef SC_READKEY_H
#define SC_READKEY_H

#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>

enum keys
{
    rk_q,
    rk_w,
    rk_e,
    rk_r,
    rk_t,
    rk_y,
    rk_u,
    rk_i,
    rk_o,
    rk_p,
    rk_a,
    rk_s,
    rk_d,
    rk_f,
    rk_g,
    rk_h,
    rk_j,
    rk_k,
    rk_l,
    rk_z,
    rk_x,
    rk_c,
    rk_v,
    rk_b,
    rk_n,
    rk_m,
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
