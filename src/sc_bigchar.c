#include "sc_bigchar.h"

int bc_printA (const char* str)
{
    printf ("\e(0%s\e(B", str);
    return 1;
}

int bc_box (int x, int y, int width, int height)
{
    int tmp;
	int screen_max_x, screen_max_y;
	int i, j;
	
	if (x > width) {
		tmp = x;
		x = width;
		width = tmp;
	}

	if (y > height) {
		tmp = y;
		y = height;
		height = tmp;
	}

	mt_getscreensize(&screen_max_y, &screen_max_x);

	if ((x < 0) || (y < 0) || (width > screen_max_x) || (height > screen_max_y) || (width - x < 2) || (height - y < 2))
		return -1;

	mt_gotoXY(x, y);
	bc_printA(TL);

	for (i = x + 1; i < width; i++) {
        mt_gotoXY (i, y);
		bc_printA(HOR);

        mt_gotoXY (i, height);
        bc_printA (HOR);
    }

	mt_gotoXY (width, y     ); bc_printA (TR);
    mt_gotoXY (width, height); bc_printA (BR);

	for (i = y + 1; i < height; i++) {
		mt_gotoXY(x, i);
		bc_printA(VERT);

		mt_gotoXY(width, i);
		bc_printA(VERT);
	}

	mt_gotoXY (x, height);
	bc_printA (BL);

	return 1;
}

int bc_print (int* big_char, int x, int y, enum Colors fg_color, enum Colors bg_color)
{
    int screen_max_x, screen_max_y;
    int sym;
    int i, j;
    char row [9];
    row[8] = '\0';

    mt_getscreensize (&screen_max_y, &screen_max_x);

    if ((x < 0) || (y < 0) || (x + 8 > screen_max_x) || (y + 8 > screen_max_y))
        return 0;

    mt_setbgcolor (bg_color);
    mt_setfgcolor (fg_color);

    
    for (i = 0; i < 8; i++) {
        for (j = 7; j >= 0; j--) {
            //sym = big_char[i > 3] & (1 << ( (32 - (i % 4) * 8) + j));
            bc_get_pos (big_char, j, i, &sym);
            row[8 - j - 1] = (sym != 0) ? REC : ' ';
        }

        mt_gotoXY (x, y + i);
        bc_printA (row);
    }

    mt_restorecolors ();

    return 1;
}

int bc_set_pos (int* big_char, int x, int y, int value)
{

    if ((x < 0) || (y < 0) || (x > 7) || (y > 7) || (value < 0) || (value > 1))
        return 0;
    
    if (big_char == NULL)
        return 0;

    if (value == 0) big_char[y > 3] &= ~(1 << ( (24 - (y % 4) * 8) + x));
    else big_char[y > 3] |= (1 << ( (24 - (y % 4) * 8) + x));

    return 1;
}

int bc_get_pos (int* big_char, int x, int y, int* value)
{
    if ((x < 0) || (y < 0) || (x > 7) || (y > 7))
        return 0;

    if ((value == NULL) || (big_char == NULL))
        return 0;

    int sym = big_char[y > 3] & (1 << ( (24 - (y % 4) * 8) + x));
    *value = sym != 0 ? 1 : 0;

    return 1; 
}

int bc_write (int fd, int* big_char, int count)
{
    if (big_char == NULL) return 0;
    if (fd == -1) return 0;
    if (write (fd, &count, sizeof (count)) == -1) return 0;
    if (write (fd, big_char, 2 * sizeof (int) * count) == -1) return 0;

    return 1;
}

int bc_read (int fd, int* big_char, int need_count, int* count)
{   
    int n, cnt;
    if (big_char == NULL) return 0;
    if (fd == -1) return 0;
    if (read (fd, &n, sizeof (int)) == -1) return 0;
    
    cnt = read (fd, big_char, 2 * need_count * sizeof (int));
    if (cnt == -1) return 0;

    if (count != NULL)
        *count = cnt / (2 * sizeof(int));

    return 1;
}