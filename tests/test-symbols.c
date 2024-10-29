#include "test.h"
#include "test-symbols.h"

void test_symbols_table()
{
    tst_suite_begin("Test symbols table");

    tst_unit("Test adding address to store", test_adding_entry);
    tst_unit("Test retrieving address from symbol", test_searching_entry);
    tst_unit("Test freeing store memory", test_freeing_store);

    tst_suite_finish();
}

void test_adding_entry()
{
    tst_true(0);
}

void test_searching_entry()
{
    tst_true(0);
}

void test_freeing_store()
{
    tst_true(0);
}
