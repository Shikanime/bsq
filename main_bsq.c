#include "./map_file_bsq.h"
#include "./map_printer_bsq.h"
#include <unistd.h>
#include <stdint.h>

int         main(int argc, char * argv[]) {
    map_t   *mp=NULL;

    if (argc <= 1) {
        write(2, "You must indicate a valid file path\n", 36);
        return 87;
    }
    if (!(mp=map_new_from_file((int8_t *) argv[1]))) {
        write(2, "Unable to load file\n", 20);
        return 87;
    }
    mark_largest_square(mp);
    print_map(mp);
    free_map(mp);
    return 0;
}
