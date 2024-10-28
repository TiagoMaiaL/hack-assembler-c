#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

enum lex_state {
    none,
    in_whitespace,
    in_comment,
    in_char_sequence
};

enum lex_state state;

bool is_whitespace(char c);
bool is_slash(char c);
bool is_general_char(char c);
bool is_equals(char c);
bool is_semicolon(char c);
bool is_at_sign(char c);
bool is_newline(char c);
bool is_control_char(char c);
char *copy_substr(int i, int j, char *src);

char *lexing_line;
int cursor_index;

void lex_line(char *source_line)
{
    assert(strlen(source_line) != 0);
    assert(strchr(source_line, '\n') != NULL);

    lexing_line = source_line;
    cursor_index = 0;
}

bool line_finished()
{
    return lexing_line[cursor_index] == '\n';
}

struct token next_token()
{
    int i;
    int c;
    int token_start;
    int token_end;

    i = cursor_index;
    state = none;

    struct token lexed_token;

    while ((c = lexing_line[i]) != '\0') {
        char next_c = lexing_line[i + 1];

        if (state == none) {
            if (is_whitespace(c)) {
                state = in_whitespace;
                lexed_token.type = whitespace;
                token_start = i;

            } else if (is_slash(c) && is_slash(next_c)) {
                state = in_comment;
                lexed_token.type = comment;
                token_start = i;

            } else if (is_equals(c)) {
                token_start = i;
                token_end = i;
                lexed_token.type = equals;
                ++i;
                break;

            } else if (is_semicolon(c)) {
                token_start = i;
                token_end = i;
                lexed_token.type = semicolon;
                ++i;
                break;

            } else if (is_at_sign(c)) {
                token_start = i;
                token_end = i;
                lexed_token.type = at;
                ++i;
                break;

            } else if (is_general_char(c)) {
                state = in_char_sequence;
                token_start = i;
                lexed_token.type = char_sequence;

            } else {
                token_start = i;
                token_end = i;
                lexed_token.type = whitespace;
                ++i;
                break;
            }
        }

        bool is_comment_end;
        bool is_whitespace_end;
        bool is_char_sequence_end;

        is_comment_end = is_newline(c) && 
                         state == in_comment;

        is_whitespace_end = !is_whitespace(c) &&
                            state == in_whitespace;

        is_char_sequence_end = !is_general_char(c) &&
                               state == in_char_sequence;

        if (is_comment_end || 
            is_whitespace_end || 
            is_char_sequence_end
        ) {
            token_end = i - 1;
            break;
        }
        
        ++i;
    }

    cursor_index = i;

    char *lexeme;
    lexeme = copy_substr(token_start, token_end, lexing_line);

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

bool is_general_char(char c)
{
    return  !is_whitespace(c) && 
            !is_slash(c) &&
            !is_equals(c) &&
            !is_semicolon(c) &&
            !is_newline(c) &&
            !is_at_sign(c) &&
            !is_control_char(c) &&
            c != '\0';
}

bool is_equals(char c)
{
    return c == '=';
}

bool is_semicolon(char c)
{
    return c == ';';
}

bool is_at_sign(char c)
{
    return c == '@';
}

bool is_newline(char c)
{
    return c == '\n';
}

bool is_control_char(char c)
{
    return c >= 0 && c <= 31;
}

char *copy_substr(int i, int j, char *src)
{
    int sub_i;
    int len;
    char *sub_str;

    sub_i = 0;
    // len is indexes + 1 (they start at 0), + '\0'
    len = (j - i) + 2;
    sub_str = malloc(len * sizeof(char));

    while (i <= j) {
        sub_str[sub_i] = src[i];
        ++i;
        ++sub_i;
    }

    return sub_str;
}

