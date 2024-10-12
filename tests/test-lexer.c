#include <stdlib.h>
#include "test.h"
#include "test-lexer.h"
#include "../src/lexer.h"

void test_lexer()
{
    tst_suite_begin("Lexer");

    tst_unit("Comments", test_lexer_comment);
    tst_unit("Whitespace", test_lexer_whitespace);
    tst_unit("Char sequence", test_lexer_char_sequence);
    tst_unit("Equals sign", test_lexer_equals_sign);
    tst_unit("Semicolon", test_lexer_semicolon_sign);

    tst_suite_finish();
}

// TODO: add a test for an empty string.

void test_lexer_comment()
{
    struct token empty_comment = next_token("//\n");
    tst_true(empty_comment.type == comment);
    tst_str_equals(empty_comment.lexeme, "//");
    free(empty_comment.lexeme);

    struct token comment_a = next_token("// asdf\n");
    tst_true(comment_a.type == comment);
    tst_str_equals(comment_a.lexeme, "// asdf");
    free(comment_a.lexeme);

    struct token comment_b = next_token("// testing\n");
    tst_true(comment_b.type == comment);
    tst_str_equals(comment_b.lexeme, "// testing");
    free(comment_b.lexeme);

    struct token comment_c = next_token("// \n");
    tst_true(comment_c.type == comment);
    tst_str_equals(comment_c.lexeme, "// ");
    free(comment_c.lexeme);

    struct token comment_d = next_token("///////\n");
    tst_true(comment_d.type == comment);
    tst_str_equals(comment_d.lexeme, "///////");
    free(comment_d.lexeme);
}

void test_lexer_whitespace()
{
    struct token single_whitespace = next_token(" \n");
    tst_true(single_whitespace.type == whitespace);
    tst_str_equals(single_whitespace.lexeme, " ");
    free(single_whitespace.lexeme);

    struct token whitespace_a = next_token("     \n");
    tst_true(whitespace_a.type == whitespace);
    tst_str_equals(whitespace_a.lexeme, "     ");
    free(whitespace_a.lexeme);

    struct token whitespace_b = next_token(" \t\n");
    tst_true(whitespace_b.type == whitespace);
    tst_str_equals(whitespace_b.lexeme, " \t");
    free(whitespace_b.lexeme);

    struct token whitespace_c = next_token("\t\t\t\n");
    tst_true(whitespace_c.type == whitespace);
    tst_str_equals(whitespace_c.lexeme, "\t\t\t");
    free(whitespace_c.lexeme);

    struct token whitespace_d = next_token("\t\t  \t\n");
    tst_true(whitespace_d.type == whitespace);
    tst_str_equals(whitespace_d.lexeme, "\t\t  \t");
    free(whitespace_d.lexeme);
}

void test_lexer_char_sequence()
{
    struct token char_seq_a = next_token("asdf\n");
    tst_true(char_seq_a.type == char_sequence);
    tst_str_equals(char_seq_a.lexeme, "asdf");
    free(char_seq_a.lexeme);

    struct token char_seq_b = next_token("a\n");
    tst_true(char_seq_b.type == char_sequence);
    tst_str_equals(char_seq_b.lexeme, "a");
    free(char_seq_a.lexeme);

    struct token char_seq_c = next_token("M+1\n");
    tst_true(char_seq_c.type == char_sequence);
    tst_str_equals(char_seq_c.lexeme, "M+1");
    free(char_seq_c.lexeme);

    struct token char_seq_d = next_token("1234\n");
    tst_true(char_seq_d.type == char_sequence);
    tst_str_equals(char_seq_d.lexeme, "1234");
    free(char_seq_d.lexeme);

    struct token char_seq_e = next_token("0\n");
    tst_true(char_seq_e.type == char_sequence);
    tst_str_equals(char_seq_e.lexeme, "0");
    free(char_seq_e.lexeme);
}

void test_lexer_equals_sign()
{
    struct token equals_sign = next_token("=\n");
    tst_true(equals_sign.type == equals);
    tst_str_equals(equals_sign.lexeme, "=");
    free(equals_sign.lexeme);
}

void test_lexer_semicolon_sign()
{
    struct token semicolon_sign = next_token(";\n");
    tst_true(semicolon_sign.type == semicolon);
    tst_str_equals(semicolon_sign.lexeme, ";");
    free(semicolon_sign.lexeme);
}

