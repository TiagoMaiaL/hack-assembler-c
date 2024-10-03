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

