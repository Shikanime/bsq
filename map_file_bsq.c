#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "./buffer_bsq.h"
#include "./map_file_bsq.h"

typedef void(map_open_file_lambda_t)(map_t *mp, int8_t *fb, size_t fc, size_t *li, size_t *ci);

int8_t  read_map_file(map_t *mp, int8_t *fp, map_open_file_lambda_t *callback);
void    populate_size_from_file(map_t *mp, int8_t *fb, size_t fc, size_t *li, size_t *ci);
int32_t add_size_from_file(map_t *mp, int8_t *fp);
void    populate_data_from_file(map_t *mp, int8_t *fb, size_t fc, size_t *li, size_t *ci);
int8_t  add_file_data_from_file(map_t *mp, int8_t *fp);
int8_t  translate_character(int8_t ch);

map_t       *map_new_from_file(int8_t *fp) {
    map_t   *mp=NULL;

    if (!(mp=new_map())) return NULL;
    if (add_size_from_file(mp, fp)) return NULL;
    if (new_map_line(mp)) return NULL;
    if (add_file_data_from_file(mp, fp)) return NULL;
    return mp;
}

void populate_size_from_file(map_t *mp, int8_t *fb, size_t fc, size_t *li, size_t *ci) {
    if (fb[fc] == '\n' || !fb[fc + 1]) {
        if (*li != 0) {
            ++mp->y_size;
            if (mp->x_size < *ci) {
                mp->x_size=*ci;
            }
        }
        ++*li;
        *ci=0;
    } else {
        ++*ci;
    }
}

int32_t add_size_from_file(map_t *mp, int8_t *fp) {
    return read_map_file(mp, fp, populate_size_from_file);
}

void populate_data_from_file(map_t *mp, int8_t *fb, size_t fc, size_t *li, size_t *ci) {
    if (fb[fc] == '\n' && *li == 0) {
        ++*li;
    } else if (*li != 0) {
        if (*ci < mp->x_size) {
            mp->data[*li - 1][*ci]=translate_character(fb[fc]);
            ++*ci;
        } else if (*li < mp->y_size) {
            ++*li;
            *ci=0;
        }
    }
}

int8_t add_file_data_from_file(map_t *mp, int8_t *fp) {
    return read_map_file(mp, fp, populate_data_from_file);
}

int8_t      read_map_file(map_t *mp, int8_t *fp, map_open_file_lambda_t *callback) {
    int32_t fd=0;
    int8_t  *fb=NULL;
    size_t  li=0;
    size_t  ci=0;

    if ((fd=open((char *) fp, O_RDONLY)) < 0) return 1;
    if (!(fb=new_buffer())) return 1;
    while (read((int) fd, fb, READ_BUFFER_SIZE) > 0) {
        for (size_t fc=0; fc < READ_BUFFER_SIZE && fb[fc]; ++fc) {
            callback(mp, fb, fc, &li, &ci);
        }
    }
    free_buffer(fb);
    if (close((int) fd) < 0) return 1;
    return 0;
}

int8_t translate_character(int8_t ch) {
    if (ch == '.') return '1';
    else if (ch == 'o') return '0';
    else return 'x';
}
