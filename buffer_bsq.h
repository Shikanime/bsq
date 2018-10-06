#pragma once
#include <stdint.h>
#define READ_BUFFER_SIZE 4096

int8_t  *new_buffer();
void    free_buffer(int8_t *fb);
