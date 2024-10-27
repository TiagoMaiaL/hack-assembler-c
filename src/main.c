#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ainst-bin.h"
#include "cinst-bin.h"
#include "file.h"
#include "parser.h"

#define EXPECTED_ARGS_COUNT 3
#define ERROR               -1
#define SUCCESS             0

int main(int argc, char **argv)
{
    if (argc != EXPECTED_ARGS_COUNT) {
        perror("input and output files must be provided");
        return ERROR;
    }

    open_in(argv[1]);
    open_out(argv[2]);

    if (errno != SUCCESS) {
        return errno;
    }

    while (!is_eof()) {
        char *line = read_line();

        if (strlen(line) == 0)
            continue;

        struct parser_result result = parse(line);

        free(line);

        if (result.code != PARSE_SUCCESS) {
            return ERROR;
        }

        char bin[17];

        switch (result.parsed_inst.type) {
            case none:
                continue;

            case a_inst_type:
                {
                    struct ainst a_inst;
                    a_inst = result.parsed_inst.a_inst;
                    ainst_bin(a_inst, bin);
                    free(a_inst.val);
                }

                break;

            case c_inst_type:
                {
                    struct cinst c_inst;
                    c_inst = result.parsed_inst.c_inst;
                    cinst_bin(c_inst, bin);

                    free(c_inst.comp);
                    if (c_inst.dest != NULL) {
                        free(c_inst.dest);
                    }
                    if (c_inst.jmp != NULL) {
                        free(c_inst.jmp);
                    }
                }
                break;
        }

        out(bin);
    }

    close_all();

    return SUCCESS;
}
