#include "sc_bigchar.h"

int main ()
{
    int bc_0    [2] = { 255 << 24 + 129 << 16 + 129 << 8 + 129,   129 << 24 + 129 << 16 + 129 << 8 + 255 };
    int bc_1    [2] = {   1 << 24 + 1   << 16 +   1 << 8 +   1,     1 << 24 + 1   << 16 + 1   << 8 +   1 };
    int bc_2    [2] = { 255 << 24 + 1   << 16 +   1 << 8 + 255,   128 << 24 + 128 << 16 + 128 << 8 + 255 };
    int bc_3    [2] = { 255 << 24 + 1   << 16 +   1 << 8 + 255,     1 << 24 + 1   << 16 + 1   << 8 + 255 };
    int bc_4    [2] = { 129 << 24 + 129 << 16 + 129 << 8 + 255,     1 << 24 + 1   << 16 + 1   << 8 +   1 };
    int bc_5    [2] = { 255 << 24 + 128 << 16 + 128 << 8 + 255,     1 << 24 + 1   << 16 + 1   << 8 + 255 };
    int bc_6    [2] = { 255 << 24 + 128 << 16 + 128 << 8 + 255,   129 << 24 + 129 << 16 + 129 << 8 + 255 };
    int bc_7    [2] = { 255 << 24 + 1   << 16 +   1 << 8 +  16,     1 << 24 + 1   << 16 + 1   << 8 +   1 };
    int bc_8    [2] = { 255 << 24 + 129 << 16 + 129 << 8 + 255,   129 << 24 + 129 << 16 + 129 << 8 + 255 };
    int bc_9    [2] = { 255 << 24 + 129 << 16 + 129 << 8 + 255,     1 << 24 + 1   << 16 + 1   << 8 +   1 };
    int bc_plus [2] = { 24  << 24 + 24  << 16 +  24 << 8 + 255,   255 << 24 + 24  << 16 +  24 << 8 +  24 };

    bc_write (open ("res/bigchar/bc_0.bin", WRONLY), bc_0, 1);
    bc_write (open ("res/bigchar/bc_1.bin", WRONLY), bc_1, 1);
    bc_write (open ("res/bigchar/bc_2.bin", WRONLY), bc_2, 1);
    bc_write (open ("res/bigchar/bc_3.bin", WRONLY), bc_3, 1);
    bc_write (open ("res/bigchar/bc_4.bin", WRONLY), bc_4, 1);
    bc_write (open ("res/bigchar/bc_5.bin", WRONLY), bc_5, 1);
    bc_write (open ("res/bigchar/bc_6.bin", WRONLY), bc_6, 1);
    bc_write (open ("res/bigchar/bc_7.bin", WRONLY), bc_7, 1);
    bc_write (open ("res/bigchar/bc_8.bin", WRONLY), bc_8, 1);
    bc_write (open ("res/bigchar/bc_9.bin", WRONLY), bc_9, 1);
    bc_write (open ("res/bigchar/bc_plus.bin", WRONLY), bc_plus, 1);

    return 0;
}
