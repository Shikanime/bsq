#include "./map_bsq.h"

map_t       *new_map() {
    map_t   *mp;

    if (!(mp=(map_t *) calloc(1, sizeof(map_t)))) return NULL;
    mp->x_size=0;
    mp->y_size=0;
    mp->data=NULL;
    return mp;
}

void free_map(map_t *mp) {
    free_map_line(mp);
    free(mp);
}

int8_t new_map_line(map_t *mp) {
    if (!(mp->data=(int8_t **) calloc(mp->y_size, sizeof(int8_t *)))) return 1;
    for(size_t i = 0; i < mp->y_size; ++i)
    {
        if (!(mp->data[i]=(int8_t *) calloc(mp->x_size, sizeof(int8_t)))) return 1;
    }
    return 0;
}

void free_map_line(map_t *mp) {
    for(size_t y = 0; y < mp->y_size; ++y)
    {
        free(mp->data[y]);
    }
    free(mp->data);
}