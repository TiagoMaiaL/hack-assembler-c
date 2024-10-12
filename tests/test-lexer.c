#include <stdlib.h>
#include "test.h"
#include "test-lexer.h"
#include "../src/lexer.h"

void test_lexer()
{
    tst_suite_begin("Lexer");

    tst_unit("Lex line", test_lex_line);
    tst_unit("Line finished", test_line_finished);
    tst_unit("Comments", test_lexer_comment);
    tst_unit("Comments", test_lexer_comment);
    tst_unit("Whitespace", test_lexer_whitespace);
    tst_unit("Char sequence", test_lexer_char_sequence);
    tst_unit("Equals sign", test_lexer_equals_sign);
    tst_unit("Semicolon", test_lexer_semicolon_sign);

    tst_suite_finish();
}

void test_lex_line()
{
    lex_line("testing\n");
    struct token char_seq; 

    char_seq = next_token();

    tst_true(char_seq.type == char_sequence);
}

void test_line_finished()
{
    lex_line("   \n");
    struct token some_token; 

    tst_false(line_finished());

    some_token = next_token();

    tst_true(line_finished());
}

void test_lexer_comment()
{
    lex_line("//\n");
    struct token empty_comment = next_token();
    tst_true(empty_comment.type == comment);
    tst_str_equals(empty_comment.lexeme, "//");
    free(empty_comment.lexeme);

    lex_line("// asdf\n");
    struct token comment_a = next_token();
    tst_true(comment_a.type == comment);
    tst_str_equals(comment_a.lexeme, "// asdf");
    free(comment_a.lexeme);

    lex_line("// testing\n");
    struct token comment_b = next_token();
    tst_true(comment_b.type == comment);
    tst_str_equals(comment_b.lexeme, "// testing");
    free(comment_b.lexeme);

    lex_line("// \n");
    struct token comment_c = next_token();
    tst_true(comment_c.type == comment);
    tst_str_equals(comment_c.lexeme, "// ");
    free(comment_c.lexeme);

    lex_line("///////\n");
    struct token comment_d = next_token();
    tst_true(comment_d.type == comment);
    tst_str_equals(comment_d.lexeme, "///////");
    free(comment_d.lexeme);
}

void test_lexer_whitespace()
{
    lex_line(" \n");
    struct token single_whitespace = next_token();
    tst_true(single_whitespace.type == whitespace);
    tst_str_equals(single_whitespace.lexeme, " ");
    free(single_whitespace.lexeme);

    lex_line("     \n");
    struct token whitespace_a = next_token();
    tst_true(whitespace_a.type == whitespace);
    tst_str_equals(whitespace_a.lexeme, "     ");
    free(whitespace_a.lexeme);

    lex_line(" \t\n");
    struct token whitespace_b = next_token();
    tst_true(whitespace_b.type == whitespace);
    tst_str_equals(whitespace_b.lexeme, " \t");
    free(whitespace_b.lexeme);

    lex_line("\t\t\t\n");
    struct token whitespace_c = next_token();
    tst_true(whitespace_c.type == whitespace);
    tst_str_equals(whitespace_c.lexeme, "\t\t\t");
    free(whitespace_c.lexeme);

    lex_line("\t\t  \t\n");
    struct token whitespace_d = next_token();
    tst_true(whitespace_d.type == whitespace);
    tst_str_equals(whitespace_d.lexeme, "\t\t  \t");
    free(whitespace_d.lexeme);
}

void test_lexer_char_sequence()
{
    lex_line("asdf\n");
    struct token char_seq_a = next_token();
    tst_true(char_seq_a.type == char_sequence);
    tst_str_equals(char_seq_a.lexeme, "asdf");
    free(char_seq_a.lexeme);

    lex_line("a\n");
    struct token char_seq_b = next_token();
    tst_true(char_seq_b.type == char_sequence);
    tst_str_equals(char_seq_b.lexeme, "a");
    free(char_seq_a.lexeme);

    lex_line("M+1\n");
    struct token char_seq_c = next_token();
    tst_true(char_seq_c.type == char_sequence);
    tst_str_equals(char_seq_c.lexeme, "M+1");
    free(char_seq_c.lexeme);

    lex_line("1234\n");
    struct token char_seq_d = next_token();
    tst_true(char_seq_d.type == char_sequence);
    tst_str_equals(char_seq_d.lexeme, "1234");
    free(char_seq_d.lexeme);

    lex_line("0\n");
    struct token char_seq_e = next_token();
    tst_true(char_seq_e.type == char_sequence);
    tst_str_equals(char_seq_e.lexeme, "0");
    free(char_seq_e.lexeme);
}

void test_lexer_equals_sign()
{
    lex_line("=\n");
    struct token equals_sign = next_token();
    tst_true(equals_sign.type == equals);
    tst_str_equals(equals_sign.lexeme, "=");
    free(equals_sign.lexeme);
}

void test_lexer_semicolon_sign()
{
    lex_line(";\n");
    struct token semicolon_sign = next_token();
    tst_true(semicolon_sign.type == semicolon);
    tst_str_equals(semicolon_sign.lexeme, ";");
    free(semicolon_sign.lexeme);
}

