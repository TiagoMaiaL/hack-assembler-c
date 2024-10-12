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

    struct token comment_a = next_token("// asdf\n");
    tst_true(comment_a.type == comment);
    tst_str_equals(comment_a.lexeme, "// asdf");

    struct token comment_b = next_token("// testing\n");
    tst_true(comment_b.type == comment);
    tst_str_equals(comment_b.lexeme, "// testing");

    struct token comment_c = next_token("// \n");
    tst_true(comment_c.type == comment);
    tst_str_equals(comment_c.lexeme, "// ");
}

void test_lexer_whitespace()
{
    tst_true(0);
}

void test_lexer_char_sequence()
{
    tst_true(0);
}

void test_lexer_equals_sign()
{
    tst_true(0);
}

void test_lexer_semicolon_sign()
{
    tst_true(0);
}

