#include "test.h"
#include "test-parser.h"
#include "../src/parser.h"

void test_parser()
{
    tst_suite_begin("Test parser");

    tst_unit("A-Inst", test_parsing_ainst);
    tst_unit("Invalid A-Inst", test_parsing_invalid_ainst);
    tst_unit("C-Inst", test_parsing_cinst);
    tst_unit(
        "Invalid C-Inst destination", 
        test_parsing_invalid_cinst_dest
    );
    tst_unit(
        "Invalid C-Inst computation", 
        test_parsing_invalid_cinst_comp
    );
    tst_unit(
        "Invalid C-Inst jump", 
        test_parsing_invalid_cinst_jmp
    );
    tst_unit(
        "Malformed C-inst",
        test_parsing_malformed_cinst
    );

    tst_suite_finish();
}

void test_parsing_ainst()
{
    tst_true(0);
}

void test_parsing_invalid_ainst()
{
    tst_true(0);
}

void test_parsing_cinst()
{
    tst_true(0);
}

void test_parsing_invalid_cinst_dest()
{
    tst_true(0);
}

void test_parsing_invalid_cinst_comp()
{
    tst_true(0);
}

void test_parsing_invalid_cinst_jmp()
{
    tst_true(0);
}

void test_parsing_malformed_cinst()
{
    tst_true(0);
}

