#include <assert.h>
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

static unsigned long line_count;
int collect_symbols();
int collect_vars();
int parse_and_translate();
bool is_variable(char *str);
int digit_count(int num);

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

    if (collect_vars() == ERROR) {
        return ERROR;
    }

    if (parse_and_translate() == ERROR) {
        return ERROR;
    }
    
    close_all();

    return SUCCESS;
}

// TODO: Use the bare lexer to collect symbols
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

                    map_symbol(symbol, line_count);

                    free(symbol);

                    break;
                }

            case a_inst_type:
                ++line_count;
                break;

            case c_inst_type:
                ++line_count;
                break;
        }
    }

    return SUCCESS;
}

int collect_vars()
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

        if (result.parsed_inst.type != a_inst_type)
            continue;

        char *var = result.parsed_inst.a_inst.val;

        if (is_variable(var)) {
            map_var(var);
        }

        free(var);
    }

    return SUCCESS;
}

// TODO: Collect vars and then translate
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
                    char *var;

                    a_inst = result.parsed_inst.a_inst;
                    var = a_inst.val;

                    if (is_variable(var)) {
                        int addr = address(var);

                        assert(addr != NULL_ADDRESS);

                        int dc = digit_count(addr) + 1;
                        char *addr_str = malloc(
                            sizeof(char) * dc
                        );
                        sprintf(addr_str, "%d", addr);
                        a_inst.val = addr_str;
                    }

                    ainst_bin(a_inst, bin);
                    free(var);
                    // TODO: Free address_str
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

int digit_count(int num) {
    if (num == 0)
        return 1;

    int count = 0;
    int _num = num;

    while (_num != 0) {
        ++count;
        _num /= 10;
    }

    return count;
}
