#include <string.h>
#include "test-utils.h"
#include "test.h"
#include "../src/utils.h"

void test_utils()
{
    tst_suite_begin("Test utility functions");

    tst_unit("streq", test_streq);
    tst_unit("strin", test_streq);
    tst_unit("strrev", test_strrev);
    tst_unit("itobin", test_itobin);

    tst_suite_finish();
}

void test_streq()
{
    tst_true(streq("asdf", "asdf"));
    tst_true(streq("", ""));
    tst_true(streq(" ", " "));
    tst_false(streq(" ", ""));
    tst_false(streq("asdf", "1231"));
    tst_false(streq("!?", "?!"));
}

void test_strin()
{
    tst_true(strin("asdf asdf", ' '));
    tst_true(strin("asdf hjkl\n", '\n'));
    tst_true(strin("asdfvhjkl", 'v'));
    tst_false(strin("hjkl", 'a'));
    tst_false(strin("hjkl123", '9'));
}

void test_strrev()
{
    char tested_str[11];
    
    strcpy(tested_str, "");
    strrev(tested_str);
    tst_str_equals(tested_str, "");

    strcpy(tested_str, " ");
    strrev(tested_str);
    tst_str_equals(tested_str, " ");

    strcpy(tested_str, "a");
    strrev(tested_str);
    tst_str_equals(tested_str, "a");

    strcpy(tested_str, " a");
    strrev(tested_str);
    tst_str_equals(tested_str, "a ");

    strcpy(tested_str, "asdf");
    strrev(tested_str);
    tst_str_equals(tested_str, "fdsa");

    strcpy(tested_str, "1234567890");
    strrev(tested_str);
    tst_str_equals(tested_str, "0987654321");

    strcpy(tested_str, "isi");
    strrev(tested_str);
    tst_str_equals(tested_str, "isi");
}

void test_itobin()
{
    char binstr[WORD_SIZE + 1];

    itobin(0, binstr, WORD_SIZE);
    tst_str_equals(binstr, "0000000000000000");

    itobin(1, binstr, WORD_SIZE);
    tst_str_equals(binstr, "0000000000000001");

    itobin(2, binstr, WORD_SIZE);
    tst_str_equals(binstr, "0000000000000010");

    itobin(3, binstr, WORD_SIZE);
    tst_str_equals(binstr, "0000000000000011");

    itobin(4, binstr, WORD_SIZE);
    tst_str_equals(binstr, "0000000000000100");

    itobin(5, binstr, WORD_SIZE);
    tst_str_equals(binstr, "0000000000000101");

    itobin(6, binstr, WORD_SIZE);
    tst_str_equals(binstr, "0000000000000110");

    itobin(7, binstr, WORD_SIZE);
    tst_str_equals(binstr, "0000000000000111");

    itobin(8, binstr, WORD_SIZE);
    tst_str_equals(binstr, "0000000000001000");

    itobin(1234, binstr, WORD_SIZE);
    tst_str_equals(binstr, "0000010011010010");

    itobin(137, binstr, WORD_SIZE);
    tst_str_equals(binstr, "0000000010001001");

    itobin(278, binstr, WORD_SIZE);
    tst_str_equals(binstr, "0000000100010110");

    itobin(22341, binstr, WORD_SIZE);
    tst_str_equals(binstr, "0101011101000101");
}

