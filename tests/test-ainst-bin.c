#include <string.h>
#include "test-ainst-bin.h"
#include "test.h"
#include "../src/ainst-bin.h"
#include "../src/utils.h"

void test_ainst_translation()
{
    tst_suite_begin("Test A-inst -> Binary translation");

    tst_unit("ainst_bin", test_ainst_bin);

    tst_suite_finish();
}

void test_ainst_bin()
{
    char bin[WORD_SIZE + 1];
    struct ainst inst;
    
    inst.val = "155";
    ainst_bin(inst, bin);
    tst_str_equals("0000000010011011", bin);

    inst.val = "2055";
    ainst_bin(inst, bin);
    tst_str_equals("0000100000000111", bin);

    inst.val = "781";
    ainst_bin(inst, bin);
    tst_str_equals("0000001100001101", bin);

    inst.val = "22";
    ainst_bin(inst, bin);
    tst_str_equals("0000000000010110", bin);

    inst.val = "7000";
    ainst_bin(inst, bin);
    tst_str_equals("0001101101011000", bin);
}

