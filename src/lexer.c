#include <stdbool.h>
#include "lexer.h"

enum lex_state {
    none,
    in_whitespace,
    in_comment,
    in_inst_component
}

enum lex_state state;

bool is_whitespace(char c);
bool is_slash(char c);
bool is_general_inst(char c);
bool is_equals(char c);
bool is_semicolon(char c);

token next_token(char *source_line)
{
    int i;
    int c;

    i = 0;
    state = none;

    while ((c = source_line[0]) != '\0') {
        if (is_whitespace(c)) {
            state = in_whitespace;

        } else if (is_slash(c)) {
            state = in_comment;

        } else if (is_general_inst(c)) {
            state = in_inst_component;

        } else if (is_equals(c)) {
            state = none;

        } else if (is_semicolon(c)) {
            state = none;
        }

        // Collect the lexeme
        // return token
    }
}

bool is_whitespace(char c)
{
    return c == ' ' || c == '\t';
}

bool is_slash(char c)
{
    return c == '/';
}

bool is_general_inst(char c)
{
    return  !is_whitespace(c) && 
            !is_slash(c) &&
            !is_equals(c) &&
            !is_semicolon(c);
}

bool is_equals(char c)
{
    return c == '=';
}

bool is_semicolon(char c)
{
    return c == ';';
}

