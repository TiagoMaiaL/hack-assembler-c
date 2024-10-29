#include "test.h"
#include "test-symbols.h"
#include "../src/symbols.h"

void test_symbols_table()
{
    tst_suite_begin("Test symbols table");

    tst_unit("Test using uninitialized store", test_uninitialized_store);
    tst_unit("Test using symbol table", test_using_symbols_table);
    tst_unit("Test fetching non-entered symbols", test_fetching_non_entered_symbols);
    tst_unit("Test freeing store memory", test_freeing_store);

    tst_suite_finish();
}

void test_uninitialized_store()
{
    tst_true(address("non entered symbol") == NULL_ADDRESS);
    tst_true(address(" ") == NULL_ADDRESS);
    tst_true(address("asdf") == NULL_ADDRESS);
}

void test_using_symbols_table()
{
    store(0, "some_symbol_0");
    store(1, "some_symbol_1");
    store(2, "some_symbol_2");
    store(3, "some_symbol_3");

    tst_true(address("some_symbol_0") == 0);
    tst_true(address("some_symbol_1") == 1);
    tst_true(address("some_symbol_2") == 2);
    tst_true(address("some_symbol_3") == 3);
}

void test_fetching_non_entered_symbols()
{
    tst_true(address("null address") == NULL_ADDRESS);
}

void test_freeing_store()
{
    free_store();

    tst_true(address("some_symbol_0") == NULL_ADDRESS);
    tst_true(address("some_symbol_1") == NULL_ADDRESS);
    tst_true(address("some_symbol_2") == NULL_ADDRESS);
    tst_true(address("some_symbol_3") == NULL_ADDRESS);
}
