#include "test.h"
#include "test-cinst-bin.h"
#include "../src/cinst-bin.h"
#include "../src/utils.h"

void str_cpy_range(char *str, char *target, int i, int len);

void test_cinst_translation()
{
    tst_suite_begin("Test C-inst -> Binary translation");

    tst_unit("cinst_bin header", test_cinst_header);
    tst_unit("cinst_bin comp", test_cinst_comp);
    tst_unit("cinst_bin dest", test_cinst_dest);
    tst_unit("cinst_bin jmp", test_cinst_jmp);
    tst_unit("cinst_bin", test_cinst_bin);

    tst_suite_finish();
}

void test_cinst_header()
{
    char bin[WORD_SIZE + 1];

    struct cinst inst;
    inst.comp = "D+1";
    inst.dest = "M";
    inst.jmp = "";

    cinst_bin(inst, bin);

    char header[4];
    str_cpy_range(bin, header, 0, 3);

    tst_str_equals(header, "111");
}

#define COMP_LEN 7

void get_comp_bin(struct cinst inst, char *comp_bin)
{
    short comp_start_index = 3;
    char bin[WORD_SIZE + 1];

    cinst_bin(inst, bin);
    str_cpy_range(bin, comp_bin, comp_start_index, COMP_LEN);
}

void test_cinst_comp()
{
    char comp[COMP_LEN + 1];

    struct cinst inst;
    inst.dest = "M";
    inst.jmp = "";

    inst.comp = "0";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "0101010");

    inst.comp = "1";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "0111111");
   
    inst.comp = "-1";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "0111010");

    inst.comp = "D";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "0001100");

    inst.comp = "A";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "0110000");

    inst.comp = "!D";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "0001101");

    inst.comp = "!A";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "0110001"); 

    inst.comp = "-D";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "0001111");

    inst.comp = "-A";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "0110011");

    inst.comp = "D+1";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "0011111");

    inst.comp = "A+1";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "0110111");

    inst.comp = "D-1";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "0001110");

    inst.comp = "A-1";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "0110010");

    inst.comp = "D+A";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "0000010");

    inst.comp = "D-A";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "0010011");

    inst.comp = "A-D";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "0000111");

    inst.comp = "D&A";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "0000000");

    inst.comp = "D|A";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "0010101");

    inst.comp = "M";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "1110000");

    inst.comp = "!M";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "1110001");

    inst.comp = "-M";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "1110011");

    inst.comp = "M+1";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "1110111");

    inst.comp = "M-1";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "1110010");

    inst.comp = "D+M";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "1000010");

    inst.comp = "D-M";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "1010011");

    inst.comp = "M-D";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "1000111");

    inst.comp = "D&M";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "1000000");

    inst.comp = "D|M";
    get_comp_bin(inst, comp);
    tst_str_equals(comp, "1010101");
}

#define DEST_LEN 3

void get_dest_bin(struct cinst inst, char *dest_bin)
{
    short dest_start_index = 10;
    char bin[WORD_SIZE + 1];

    cinst_bin(inst, bin);
    str_cpy_range(bin, dest_bin, dest_start_index, DEST_LEN);
}

void test_cinst_dest()
{
    char dest[DEST_LEN + 1];

    struct cinst inst;
    inst.comp = "0";
    inst.jmp = "";

    inst.dest = "";
    get_dest_bin(inst, dest);
    tst_str_equals(dest, "000");

    inst.dest = "M";
    get_dest_bin(inst, dest);
    tst_str_equals(dest, "001");

    inst.dest = "D";
    get_dest_bin(inst, dest);
    tst_str_equals(dest, "010");

    inst.dest = "MD";
    get_dest_bin(inst, dest);
    tst_str_equals(dest, "011");

    inst.dest = "A";
    get_dest_bin(inst, dest);
    tst_str_equals(dest, "100");

    inst.dest = "AM";
    get_dest_bin(inst, dest);
    tst_str_equals(dest, "101");

    inst.dest = "AD";
    get_dest_bin(inst, dest);
    tst_str_equals(dest, "110");

    inst.dest = "AMD";
    get_dest_bin(inst, dest);
    tst_str_equals(dest, "111");
}

#define JMP_LEN 3

void get_jmp_bin(struct cinst inst, char *jmp_bin)
{
    short jmp_start_index = 13;
    char bin[WORD_SIZE + 1];

    cinst_bin(inst, bin);
    str_cpy_range(bin, jmp_bin, jmp_start_index, JMP_LEN);
}

void test_cinst_jmp()
{
    char jmp[JMP_LEN + 1];

    struct cinst inst;
    inst.comp = "0";
    inst.dest = "";

    inst.jmp = "";
    get_jmp_bin(inst, jmp);
    tst_str_equals(jmp, "000");
 
    inst.jmp = "JGT";
    get_jmp_bin(inst, jmp);
    tst_str_equals(jmp, "001");
 
    inst.jmp = "JEQ";
    get_jmp_bin(inst, jmp);
    tst_str_equals(jmp, "010");

    inst.jmp = "JGE";
    get_jmp_bin(inst, jmp);
    tst_str_equals(jmp, "011");

    inst.jmp = "JLT";
    get_jmp_bin(inst, jmp);
    tst_str_equals(jmp, "100");

    inst.jmp = "JNE";
    get_jmp_bin(inst, jmp);
    tst_str_equals(jmp, "101");

    inst.jmp = "JLE";
    get_jmp_bin(inst, jmp);
    tst_str_equals(jmp, "110");

    inst.jmp = "JMP";
    get_jmp_bin(inst, jmp);
    tst_str_equals(jmp, "111");
}

void test_cinst_bin()
{
    char bin[WORD_SIZE + 1];

    struct cinst inst;
    inst.dest = "M";
    inst.jmp = "";

    inst.comp = "D+1";
    cinst_bin(inst, bin);
    tst_str_equals(bin, "1110011111001000");

    inst.comp = "D+M";
    cinst_bin(inst, bin);
    tst_str_equals(bin, "1111000010001000");

    inst.dest = "";
    inst.jmp = "JMP";
    inst.comp = "A+1";
    cinst_bin(inst, bin);
    tst_str_equals(bin, "1110110111000111");

}

void str_cpy_range(char *str, char *target, int i, int len)
{
    int j;
    char *range_str;

    range_str = str + i;

    for (j = 0; j < len; ++j) {
        target[j] = range_str[j];
    }

    target[j] = '\0';
}

