#include <stdio.h>
#include <stdlib.h>
#include "fits.h"

int
main(int argc, char **argv) {
    catstruct *catalog;

    if (argc < 2) {
        printf("Error, Must have a file argument\n");
        return 1;
    }

    catalog = read_cat(argv[1]);
    if (catalog == 0) {
        printf("Error, failed to read file\n");
        return 1;
    }

    about_cat(catalog, stdout);
    free_cat(catalog);

    about_cat(catalog, stdout);

    printf("OK!!!\n");

    return 0;
}
