#include <assert.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"

struct inst parse_ainst();
struct inst parse_cinst();
bool ainst_val_valid(struct token);
bool cinst_dest_valid(struct token);
bool cinst_comp_valid(struct token);
bool cinst_jmp_valid(struct token);

struct inst parse(char *source_line)
{
    assert(strlen(source_line) > 0);

    lex_line(source_line);

    while (!line_finished()) {
        struct token curr_token;

        curr_token = next_token();

        if (curr_token.type == comment || 
            curr_token.type == whitespace
        ) {
            free(curr_token.lexeme);
            continue;
        }

        if (curr_token.type == at) {
            // TODO: return a token if there are no errors.
            return parse_ainst();

        } else if (curr_token.type == char_sequence) {
            // TODO: return a token if there are no errors.
            parse_cinst();

        } else {
            // TODO: Return error, for now we can abort
            abort();
        }
    }
}

struct inst parse_ainst()
{
    struct token expected_char_seq = next_token();

    if (expected_char_seq.type == char_sequence && 
        ainst_val_valid(expected_char_seq)
    ) {
        struct ainst _ainst;
        _ainst.val = expected_char_seq.lexeme;

        struct inst _inst;
        _inst.type = a_inst_type;
        _inst.a_inst = _ainst;

        return _inst;

    } else {
        // TODO: handle errors.
    }
}

struct inst parse_cinst()
{
    // TODO: Expect char_seq
    // TODO: Lookahead for either equals or semicolon
      // TODO: if equals, char_seq is dest, validate it
      // TODO: if semicolon, char_seq is compt, validate it
    // TODO: expect next token to be char_seq
      // TODO: It's either a jmp or a comp, depending on prev
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

bool cinst_dest_valid(struct token)
{
    // TODO:
    return false;
}

bool cinst_comp_valid(struct token)
{
    // TODO:
    return false;
}

bool cinst_jmp_valid(struct token)
{
    // TODO:
    return false;
}
