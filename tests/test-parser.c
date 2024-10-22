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
    struct parser_result result;
    
    result = parse("@1234\n");

    tst_true(result.code == 0);
    tst_true(result.parsed_inst.type == a_inst_type);
    tst_str_equals(result.parsed_inst.a_inst.val, "1234");
    free(result.parsed_inst.a_inst.val);
}

void test_parsing_invalid_ainst()
{
    tst_true(1);

    struct parser_result result;
    result = parse("@______\n");
    tst_true(result.code == -1);
}

void test_parsing_cinst()
{
    struct parser_result result;
    
    result = parse("D=M+1\n");
    
    tst_true(result.code == 0);
    tst_true(result.parsed_inst.type == c_inst_type);
    tst_str_equals(result.parsed_inst.c_inst.dest, "D");
    tst_str_equals(result.parsed_inst.c_inst.comp, "M+1");
    free(result.parsed_inst.c_inst.dest);
    free(result.parsed_inst.c_inst.comp);

    result = parse("D-1;JMP\n");

    tst_true(result.parsed_inst.type == c_inst_type);
    tst_str_equals(result.parsed_inst.c_inst.comp, "D-1");
    tst_str_equals(result.parsed_inst.c_inst.jmp, "JMP");
    free(result.parsed_inst.c_inst.comp);
    free(result.parsed_inst.c_inst.jmp);
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
    struct parser_result result;

    result = parse("=M+1\n");
    tst_true(result.code == -1);

    result = parse(";asdf\n");
    tst_true(result.code == -1);
}

