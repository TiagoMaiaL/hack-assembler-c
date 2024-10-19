#include <stdlib.h>
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
    struct inst expected_inst;
    
    expected_inst = parse("@1234\n");

    tst_true(expected_inst.type == a_inst_type);
    tst_str_equals(expected_inst.a_inst.val, "1234");
}

void test_parsing_invalid_ainst()
{
    tst_true(0);
}

void test_parsing_cinst()
{
    struct inst expected_inst;
    
    expected_inst = parse("D=M+1\n");
    tst_true(expected_inst.type == c_inst_type);
    tst_str_equals(expected_inst.c_inst.dest, "D");
    tst_str_equals(expected_inst.c_inst.comp, "M+1");
    free(expected_inst.c_inst.dest);
    free(expected_inst.c_inst.comp);

    expected_inst = parse("D-1;JMP\n");
    tst_true(expected_inst.type == c_inst_type);
    tst_str_equals(expected_inst.c_inst.comp, "D-1");
    tst_str_equals(expected_inst.c_inst.jmp, "JMP");
    free(expected_inst.c_inst.comp);
    free(expected_inst.c_inst.jmp);
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

