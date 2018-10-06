#include <stdlib.h>
#include "./matrix_bsq.h"

int32_t     **matrix_new(size_t x, size_t y) {
    int32_t **bsq=NULL;

    bsq = (int32_t **) calloc(y, sizeof(int32_t *));
    for(size_t i = 0; i < y; ++i) {
        bsq[i] = (int32_t *) calloc(x, sizeof(int32_t));
    }
    return bsq;
}
