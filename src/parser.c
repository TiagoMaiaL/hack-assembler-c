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

            struct parser_result result;
            result.code = -1;
            return result;
        }
    }

    // TODO: Return empty positive parser_result
    // TODO: Test return of empty parser_result
    // TODO: Add factory for empty parser_result
}

struct parser_result parse_ainst()
{

    // TODO: Create result factory.
    struct parser_result result;

    struct token expected_char_seq = next_token();

    if (expected_char_seq.type == char_sequence && 
        ainst_val_valid(expected_char_seq)
    ) {
        struct ainst _ainst;
        _ainst.val = expected_char_seq.lexeme;

        struct inst _inst;
        _inst.type = a_inst_type;
        _inst.a_inst = _ainst;

        result.code = 0;
        result.parsed_inst = _inst;

    } else {
        // TODO: Print error.
        result.code = -1;
    }

    return result;
}

struct parser_result parse_cinst(struct token initial_char_seq)
{
    struct parser_result result;

    struct token expected_separator = next_token(); // = or ;

    if (expected_separator.type == equals &&
        cinst_dest_valid(initial_char_seq)
    ) {
        free(expected_separator.lexeme);

        struct token dest = initial_char_seq;
        struct token expected_comp = next_token();

        if (expected_comp.type == char_sequence) {
            struct cinst _cinst;
            _cinst.dest = dest.lexeme;
            _cinst.comp = expected_comp.lexeme;
            _cinst.jmp = NULL;

            struct inst _inst;
            _inst.type = c_inst_type;
            _inst.c_inst = _cinst;

            result.code = 0;
            result.parsed_inst = _inst;

        } else {
            // TODO: Inform token mismatch and print lexeme
            result.code = -1;
        }

    } else if (expected_separator.type == semicolon) {
        free(expected_separator.lexeme);
    
        struct token comp = initial_char_seq;
        struct token expected_jmp = next_token();

        if (expected_jmp.type == char_sequence &&
            cinst_jmp_valid(expected_jmp)
        ) {
            struct cinst _cinst;
            _cinst.comp = comp.lexeme;
            _cinst.jmp = expected_jmp.lexeme;
            _cinst.dest = NULL;

            struct inst _inst;
            _inst.type = c_inst_type;
            _inst.c_inst = _cinst;

            result.code = 0;
            result.parsed_inst = _inst;
   
        } else {
            // TODO: Inform token mismatch and print lexeme
            result.code = -1;
        }

    } else {
        // TODO: Inform token mismatch and print lexeme
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
    bool is_valid = false;

    for (int i = 0; i < DESTS_COUNT; ++i) {
        if (strcmp(valid_dests[i], _token.lexeme) == 0) {
            return true;
        }
    }

    return is_valid;
}

bool cinst_comp_valid(struct token)
{
    // TODO:
    return false;
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
    bool is_valid = false;

    for (int i = 0; i < JMPS_COUNT; ++i) {
        if (strcmp(valid_jmps[i], _token.lexeme) == 0) {
            return true;
        }
    }

    return is_valid;
}
