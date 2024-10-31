#include <assert.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"

struct parser_result parse_ainst();
struct parser_result parse_cinst(struct token);
struct parser_result parse_assign_cinst(struct token);
struct parser_result parse_jmp_cinst(struct token);
struct parser_result parse_symbol(struct token);
bool ainst_val_valid(struct token);
bool cinst_dest_valid(struct token);
bool cinst_comp_valid(struct token);
bool cinst_jmp_valid(struct token);
bool sinst_val_valid(char *val);
struct parser_result make_empty_result();
void print_error(char *header, char *expected, char *found);

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

        } else if (curr_token.type == symbol) {
            return parse_symbol(curr_token);

        } else {
            print_error(
                "Unexpected token at instruction start",
                "'@' or 'char_sequence'",
                curr_token.lexeme
            );
            free(curr_token.lexeme);

            struct parser_result result = make_empty_result();
            result.code = PARSE_ERROR;
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
        print_error(
            "Error parsing a-instruction address",
            "'char_sequence'",
            expected_char_seq.lexeme
        );
        free(expected_char_seq.lexeme);
        result.code = PARSE_ERROR;
    }

    return result;
}

struct parser_result parse_cinst(struct token initial_char_seq)
{
    struct token expected_separator = next_token(); // = or ;

    if (expected_separator.type == equals) {
        free(expected_separator.lexeme);
        return parse_assign_cinst(initial_char_seq);

    } else if (expected_separator.type == semicolon) {
        free(expected_separator.lexeme);
        return parse_jmp_cinst(initial_char_seq);

    } else {
        printf("initial char = %s\n", initial_char_seq.lexeme);
        printf("type = %d\n", expected_separator.type);
        int i = 0;
        int c;
        while ((c = expected_separator.lexeme[i]) != '\0') {
            printf("c = %d\n", c);
            ++i;
        }
        print_error(
            "Error parsing c-instruction",
            "'=' or ';'",
            expected_separator.lexeme
        );
        free(initial_char_seq.lexeme);
        free(expected_separator.lexeme);

        struct parser_result result = make_empty_result();
        result.parsed_inst.type = c_inst_type;
        result.code = PARSE_ERROR;
        return result;
    }
}

struct parser_result parse_assign_cinst(struct token dest)
{
    struct parser_result result = make_empty_result();
    result.parsed_inst.type = c_inst_type;

    if (!cinst_dest_valid(dest)) {
        print_error(
            "Invalid destination for c-instruction",
            "A, D, M ...",
            dest.lexeme
        );
        free(dest.lexeme);
        result.code = PARSE_ERROR;
        return result;
    }

    struct token expected_comp = next_token();

    if (expected_comp.type == char_sequence &&
        cinst_comp_valid(expected_comp)
    ) {
        result.parsed_inst.c_inst.dest = dest.lexeme;
        result.parsed_inst.c_inst.comp = expected_comp.lexeme;

    } else {
        print_error(
            "Invalid computation for c-instruction",
            "0, 1, -1, D, M+1, D+M, ...",
            expected_comp.lexeme
        );
        free(dest.lexeme);
        free(expected_comp.lexeme);
        result.code = PARSE_ERROR;
    }

    return result;
}

struct parser_result parse_jmp_cinst(struct token comp)
{
    struct parser_result result = make_empty_result();
    result.parsed_inst.type = c_inst_type;

    if (!cinst_comp_valid(comp)) {
        print_error(
            "Invalid computation for c-instruction",
            "0, 1, -1, D, M+1, D+M, ...",
            comp.lexeme
        );

        free(comp.lexeme);
        result.code = PARSE_ERROR;
        return result;
    }

    struct token expected_jmp = next_token();

    if (expected_jmp.type == char_sequence &&
        cinst_jmp_valid(expected_jmp)
    ) {
        result.parsed_inst.c_inst.comp = comp.lexeme;
        result.parsed_inst.c_inst.jmp = expected_jmp.lexeme;

    } else {
        print_error(
            "Invalid jump for c-instruction",
            "JEQ, JLT, JMP, JGT ...",
            expected_jmp.lexeme
        );
        free(comp.lexeme);
        free(expected_jmp.lexeme);
        result.code = PARSE_ERROR;
    }

    return result;
}

struct parser_result parse_symbol(struct token symbol_token)
{
    struct parser_result result = make_empty_result();
    result.parsed_inst.type = symbol_type;

    int i;
    int c;
    int len;

    i = 0;
    len = 0;

    while ((c = symbol_token.lexeme[i]) != '\0') {
        // strip whitespaces
        ++i;

        if (c == ' ')
            continue;

        ++len;
    }

    // - '(' and ')' delimiters and + '\0'
    char *val = malloc((sizeof(char) * len) - 2 + 1);
    int j;

    i = 0;
    j = 0;

    while ((c = symbol_token.lexeme[i]) != '\0') {
        ++i;

        if (c == '(' || c == ')' || c == ' ')
            continue;

        val[j] = c;
        ++j;
    }

    val[j] = '\0';
    
    if (!sinst_val_valid(val)) {
        print_error(
            "Invalid value for symbol",
            "alphanumeric char sequence",
            val
        );
        result.code = PARSE_ERROR;
        free(val);

    } else {
        result.parsed_inst.s_inst.val = val;
    }
    
    free(symbol_token.lexeme);
    
    return result;
}

bool ainst_val_valid(struct token char_seq)
{
    int c;
    int i;
    bool is_var;

    i = 0;
    is_var = false;

    if (strlen(char_seq.lexeme) == 0) {
        return false;
    }

    if (isalpha(char_seq.lexeme[0])) {
        is_var = true;
    }

    while ((c = char_seq.lexeme[i]) != '\0') {
        if (is_var && (!isalnum(c) && 
                       c != '_' && 
                       c != '.' &&
                       c != '$')) {
            return false;

        } else if (!is_var && !isdigit(c)) {
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

bool sinst_val_valid(char *val)
{
    bool valid;
    bool has_alpha;
    int i;
    int c;

    has_alpha = false;
    valid = true;
    i = 0;
        
    while ((c = val[i]) != '\0') {
        if (!isalnum(c) && 
            c != '_' && 
            c != '.' &&
            c != '$') {
            valid = false;
            break;
        }

        if (!has_alpha && isalpha(c)) {
            has_alpha = true;
        }

        ++i;
    }
    
    valid = valid && has_alpha;

    return valid;
}

struct parser_result make_empty_result()
{
    struct ainst _ainst;
    _ainst.val = NULL;

    struct cinst _cinst;
    _cinst.dest = NULL;
    _cinst.comp = NULL;
    _cinst.jmp = NULL;

    struct sinst _sinst;
    _sinst.val = NULL;

    struct inst _inst;
    _inst.type = none;
    _inst.a_inst = _ainst;
    _inst.c_inst = _cinst;
    _inst.s_inst = _sinst;

    struct parser_result result;
    result.code = PARSE_SUCCESS;
    result.parsed_inst = _inst;

    return result;
}

void print_error(char *header, char *expected, char *found)
{
    // TODO: Print the line number.
    errno = PARSE_ERROR;
    perror(header);
    printf("Expected: %s, Found: '%s'\n", expected, found);
}

