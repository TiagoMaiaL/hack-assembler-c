#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "parser.h"

struct inst parse_ainst();
struct inst parse_cinst();
bool ainst_val_valid();
bool cinst_dest_valid();
bool cinst_comp_valid();
bool cinst_jmp_valid();

struct inst parse(char *source_line)
{
    assert(strlen(source_line) > 0);

    lex_line(source_line);

    while (line_finished()) {
        struct token curr_token;

        curr_token = next_token();

        if (curr_token.type == comment || 
            curr_token.type == whitespace
        ) {
            free(curr_token.lexeme);
            continue;
        }

        if (curr_token.type == at) {
            parse_ainst();

        } else if (curr_token.type == char_sequence) {
            parse_cinst();

        } else {
            // TODO: Return error, for now we can abort
            abort();
        }
    }
}

struct inst parse_ainst()
{
    // TODO: Make sure lexeme only has number digits.
    // TODO: Allow for symbols in the future.
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

bool ainst_val_valid()
{
    // TODO:
    return false;
}

bool cinst_dest_valid()
{
    // TODO:
    return false;
}

bool cinst_comp_valid()
{
    // TODO:
    return false;
}

bool cinst_jmp_valid()
{
    // TODO:
    return false;
}
