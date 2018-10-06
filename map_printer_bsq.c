#include "./map_printer_bsq.h"
#include "./matrix_bsq.h"
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include <stdio.h>
void    construct_matrix_entries(int32_t **mt, map_t *mp);
int32_t convert_character(int8_t ch);
int32_t local_min(int32_t a, int32_t b, int32_t c) ;

void print_map(map_t *mp) {
    for(size_t y = 0; y < mp->y_size; ++y) {
        write(1, mp->data[y], mp->x_size);
        write(1, "\n", 1);
    }
}

int8_t      mark_largest_square(map_t *mp) {
    int32_t **mt=NULL;
    int32_t mm=0;
    size_t  xm=0;
    size_t  ym=0;

    if (!(mt = matrix_new(mp->x_size, mp->y_size))) return 1;
    construct_matrix_entries(mt, mp);
    for(size_t y = 0; y < mp->y_size; y++)  { 
        for(size_t x = 0; x < mp->x_size; x++)  {
            if(mm < mt[y][x])  {
                mm = mt[y][x];
                ym = y;
                xm = x; 
            }         
        }
    }
    for(size_t y = ym; (int32_t) y > (int32_t) ym - mm; --y) {
        for(size_t x = xm; (int32_t) x > (int32_t) xm - mm; --x) {
            mp->data[y][x] = 'x';
        }
    }
    return 0;
}

void construct_matrix_entries(int32_t **mt, map_t *mp) {
    for(size_t y = 0; y < mp->y_size; y++) {
        mt[y][0] = convert_character(mp->data[y][0]);
    }
    for(size_t x = 0; x < mp->x_size; x++) {
        mt[0][x] = convert_character(mp->data[0][x]);
    }
    for(size_t y = 1; y < mp->y_size; y++) {
        for(size_t x = 1; x < mp->x_size; x++) {
            if(convert_character(mp->data[y][x]) == 1) {
                mt[y][x] = local_min(mt[y][x-1], mt[y-1][x], mt[y-1][x-1]) + 1; 
            } else {
                mt[y][x] = 0; 
            }
        }
    }
}

/* ミュセル・フォアラン */

int32_t convert_character(int8_t ch) {
    switch (ch)
    {
        case '0':
            return 0;
        case '1':
            return 1;
        default:
            return 0;
    }
}

int32_t     local_min(int32_t a, int32_t b, int32_t c) 
{ 
    int32_t m=0;

    m=a;
    if (m > b)  
        m = b; 
    if (m > c)  
        m = c; 
    return m; 
}
