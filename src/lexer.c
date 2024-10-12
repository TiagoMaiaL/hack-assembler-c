#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

enum lex_state {
    none,
    in_whitespace,
    in_comment,
    in_inst_component
};

enum lex_state state;

bool is_whitespace(char c);
bool is_slash(char c);
bool is_general_inst(char c);
bool is_equals(char c);
bool is_semicolon(char c);
bool is_newline(char c);
char *copy_substr(int i, int j, char *src);

struct token next_token(char *source_line)
{
    int i;
    int c;
    int token_start;
    int token_end;

    i = 0;
    state = none;

    struct token lexed_token;

    while ((c = source_line[i]) != '\0') {
        char next_c = source_line[i + 1];

        if (is_whitespace(c) && state == none) {
            state = in_whitespace;

        } else if (is_slash(c) && 
                   is_slash(next_c)) {
            state = in_comment;
            lexed_token.type = comment;
            token_start = i;

        } else if (is_equals(c)) {
            state = none;

        } else if (is_semicolon(c)) {
            state = none;
        }
        // TODO: lex char sequence

        if (state == in_comment && is_newline(c)) {
            token_end = i - 1; 
            break;
        }
        
        ++i;
    }

    char *lexeme;
    lexeme = copy_substr(token_start, token_end, source_line);

    lexed_token.lexeme = lexeme;

    return lexed_token;
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

bool is_newline(char c)
{
    return c == '\n';
}

char *copy_substr(int i, int j, char *src)
{
    int len;
    char *sub_str;

    // len is indexes + 1 (they start at 0), + '\0'
    len = (j - i) + 2;

    sub_str = malloc(len * sizeof(char));

    while (i <= j) {
        sub_str[i] = src[i];
        ++i;
    }

    return sub_str;
}

