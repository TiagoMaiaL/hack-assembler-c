#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"

struct parser_result parse_ainst();
struct parser_result parse_cinst(struct token);
bool ainst_val_valid(struct token);
bool cinst_dest_valid(struct token);
bool cinst_comp_valid(struct token);
bool cinst_jmp_valid(struct token);
struct parser_result make_empty_result();

struct parser_result parse(char *source_line)
{
    assert(strlen(source_line) > 0);

    lex_line(source_line);

    while (!line_finished()) {
        struct token curr_token;

        curr_token = next_token();

        if (curr_token.type == comment || 
            curr_token.type == whitespace
        ) {
            // Drop on the floor.
            free(curr_token.lexeme);
            continue;
        }

        if (curr_token.type == at) {
            free(curr_token.lexeme);
            return parse_ainst();

        } else if (curr_token.type == char_sequence) {
            return parse_cinst(curr_token);

        } else {
            // TODO: Print error message.
            free(curr_token.lexeme);

            struct parser_result result = make_empty_result();
            result.code = -1;
            return result;
        }
    }

    return make_empty_result();
}

struct parser_result parse_ainst()
{
    struct parser_result result = make_empty_result();
    result.parsed_inst.type = a_inst_type;

    struct token expected_char_seq = next_token();

    if (expected_char_seq.type == char_sequence && 
        ainst_val_valid(expected_char_seq)
    ) {
        result.parsed_inst.a_inst.val = expected_char_seq.lexeme;

    } else {
        // TODO: Print error.
        free(expected_char_seq.lexeme);
        result.code = -1;
    }

    return result;
}

// TODO: Refactor error handling code to provide assertive msgs.
struct parser_result parse_cinst(struct token initial_char_seq)
{
    struct parser_result result = make_empty_result();
    result.parsed_inst.type = c_inst_type;

    struct token expected_separator = next_token(); // = or ;
    free(expected_separator.lexeme); // won't be used.

    if (expected_separator.type == equals &&
        cinst_dest_valid(initial_char_seq)
    ) {
        struct token dest = initial_char_seq;
        struct token expected_comp = next_token();

        if (expected_comp.type == char_sequence &&
            cinst_comp_valid(expected_comp)
        ) {
            result.parsed_inst.c_inst.dest = dest.lexeme;
            result.parsed_inst.c_inst.comp = expected_comp.lexeme;

        } else {
            // TODO: Inform token mismatch and print lexeme
            free(dest.lexeme);
            free(expected_comp.lexeme);
            result.code = -1;
        }

    } else if (expected_separator.type == semicolon &&
               cinst_comp_valid(initial_char_seq)
    ) {
        struct token comp = initial_char_seq;
        struct token expected_jmp = next_token();

        if (expected_jmp.type == char_sequence &&
            cinst_jmp_valid(expected_jmp)
        ) {
            result.parsed_inst.c_inst.comp = comp.lexeme;
            result.parsed_inst.c_inst.jmp = expected_jmp.lexeme;

        } else {
            // TODO: Inform token mismatch and print lexeme
            free(comp.lexeme);
            free(expected_jmp.lexeme);
            result.code = -1;
        }

    } else {
        // TODO: Inform token mismatch and print lexeme
        free(initial_char_seq.lexeme);
        result.code = -1;
    }

    return result;
}

bool ainst_val_valid(struct token char_seq)
{
    int c;
    int i;

    i = 0;

    if (strlen(char_seq.lexeme) == 0) {
        return false;
    }

    while ((c = char_seq.lexeme[i]) != '\0') {
        if (!isdigit(c)) {
            return false;
        }
        ++i;
    }

    return true;
}

bool contains_str(char *str, const char *strs[], int count)
{
    bool in = false;

    for (int i = 0; i < count; ++i) {
        if (strcmp(strs[i], str) == 0) {
            return true;
        }
    }

    return in;
}

#define DESTS_COUNT 7
const char *valid_dests[] = {
    "A",
    "D",
    "M",
    "AM",
    "AD",
    "MD",
    "ADM"
};

bool cinst_dest_valid(struct token _token)
{
    return contains_str(_token.lexeme, valid_dests, DESTS_COUNT);
}

#define FUNCS_COUNT 28
const char *valid_funcs[] = {
    "0",
    "1",
    "-1",
    "D",
    "A",
    "!D",
    "!A",
    "-D",
    "-A",
    "D+1",
    "A+1",
    "D-1",
    "A-1",
    "D+A",
    "D-A",
    "A-D",
    "D&A",
    "D|A",
    "M",
    "!M",
    "-M",
    "M+1",
    "M-1",
    "D+M",
    "D-M",
    "M-D",
    "D&M",
    "D|M"
};

bool cinst_comp_valid(struct token _token)
{
    return contains_str(_token.lexeme, valid_funcs, FUNCS_COUNT);
}

#define JMPS_COUNT 7
const char *valid_jmps[] = {
    "JGT",
    "JEQ",
    "JGE",
    "JLT",
    "JNE",
    "JLE",
    "JMP"
};

bool cinst_jmp_valid(struct token _token)
{
    return contains_str(_token.lexeme, valid_jmps, JMPS_COUNT);
}


struct parser_result make_empty_result()
{
    struct ainst _ainst;
    _ainst.val = NULL;

    struct cinst _cinst;
    _cinst.dest = NULL;
    _cinst.comp = NULL;
    _cinst.jmp = NULL;

    struct inst _inst;
    _inst.type = none;
    _inst.a_inst = _ainst;
    _inst.c_inst = _cinst;

    struct parser_result result;
    result.code = 0;
    result.parsed_inst = _inst;

    return result;
}

