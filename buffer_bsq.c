#include <stdlib.h>
#include "./buffer_bsq.h"

int8_t      *new_buffer() {
    int8_t  *fb=NULL;

    if (!(fb=(int8_t *) calloc(READ_BUFFER_SIZE, sizeof(int8_t)))) return NULL;
    return fb;
}

void free_buffer(int8_t *fb) {
    free(fb);
}
