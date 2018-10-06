#pragma once
#include <stdint.h>
#include <stdlib.h>

typedef struct  map_s
{
    size_t      x_size;
    size_t      y_size;
    int8_t      **data;
}               map_t;

map_t   *new_map();
void    free_map(map_t *mp);
int8_t  new_map_line(map_t *mp);
void    free_map_line(map_t *mp);
