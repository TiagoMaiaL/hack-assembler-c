#include <stdio.h>
#include <string.h>
#include "file.h"

int main(int argc, char **argv)
{
    if (argc != 3) {
        perror("input and output file paths must be provided");
        return -1;
    }

    open_in(argv[1]);

    read_line();
    printf("Is EOF? %d\n", is_eof());

    close_all();

    return 0;
}
