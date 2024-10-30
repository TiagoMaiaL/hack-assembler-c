#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ainst-bin.h"
#include "cinst-bin.h"
#include "file.h"
#include "parser.h"
#include "symbols.h"

#define EXPECTED_ARGS_COUNT 3
#define ERROR               -1
#define SUCCESS             0

static int line_count;
int collect_symbols();
int parse_and_translate();
bool is_variable(char *str);

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

    if (collect_symbols() == ERROR) {
        return ERROR;
    }

    if (parse_and_translate() == ERROR) {
        return ERROR;
    }
    
    close_all();

    return SUCCESS;
}

int collect_symbols()
{
    line_count = 0;

    while (!is_eof()) {
        char *line = read_line();

        if (strlen(line) == 0)
            continue;

        struct parser_result result = parse(line);
        free(line);

        if (result.code != PARSE_SUCCESS) {
            return ERROR;
        }

        struct inst parsed_inst = result.parsed_inst;

        switch (parsed_inst.type) {
            case none: continue;
            
            case symbol_type:
                {
                    char *symbol = parsed_inst.s_inst.val;

                    ++line_count;

                    if (address(symbol) == NULL_ADDRESS)
                        store(line_count, symbol);

                    free(symbol);

                    break;
                }

            case a_inst_type:
                {
                    char *var = parsed_inst.a_inst.val;

                    if (is_variable(var) &&
                        address(var) == NULL_ADDRESS
                    ) {
                        store(next_address(), var);
                        increase_address_count();
                    }
                    free(var);

                    ++line_count;

                    break;
                }

            case c_inst_type:
                ++line_count;

                break;
        }
    }

    return SUCCESS;
}

int parse_and_translate()
{
    line_count = 0;
    seek_start();

    if (errno != 0) {
        perror("Seeking to line 0");
        return ERROR;
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
            case none: continue;
            case symbol_type: continue;

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

    return SUCCESS;
}

bool is_variable(char *str)
{
    return isalpha(str[0]);
}

