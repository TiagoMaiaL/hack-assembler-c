#include <string.h>
#include "cinst-bin.h"
#include "utils.h"

// TODO: Document each one of these functions.
void comp_bin(char *comp, char *bin);
void dest_bin(char *dest, char *bin);
void jmp_bin(char *jmp, char *bin);

// TODO: Define constants for cinst_bin.
void cinst_bin(struct cinst inst, char *bin)
{
    strcpy(bin, "111");

    char comp_binary[8];
    comp_bin(inst.comp, comp_binary);
    strcpy(bin + 3, comp_binary);

    char dest_binary[4];
    dest_bin(inst.dest, dest_binary);
    strcpy(bin + 3 + 7, dest_binary);

    char jmp_binary[4];
    jmp_bin(inst.jmp, jmp_binary);
    strcpy(bin + 3 + 7 + 3, jmp_binary);
}

void comp_bin(char *instcomp, char *bin)
{
    if (strin(instcomp, 'M')) {
        bin[0] = ON;
    } else {
        bin[0] = OFF;
    }

    bin += 1;

    if (streq(instcomp, "0")) {
        strcpy(bin, "101010");

    } else if (streq(instcomp, "1")) {
        strcpy(bin, "111111");

    } else if (streq(instcomp, "-1")) {
        strcpy(bin, "111010");
   
    } else if (streq(instcomp, "D")) {
        strcpy(bin, "001100");
 
    } else if (streq(instcomp, "A") || streq(instcomp, "M")) {
        strcpy(bin, "110000");

    } else if (streq(instcomp, "!D")) {
        strcpy(bin, "001101");

    } else if (streq(instcomp, "!A") || streq(instcomp, "!M")) {
        strcpy(bin, "110001");

    } else if (streq(instcomp, "-D")) {
        strcpy(bin, "001111");

    } else if (streq(instcomp, "-A") || streq(instcomp, "-M")) {
        strcpy(bin, "110011");

    } else if (streq(instcomp, "D+1")) {
        strcpy(bin, "011111");

    } else if (streq(instcomp, "A+1") || streq(instcomp, "M+1")) {
        strcpy(bin, "110111");

    } else if (streq(instcomp, "D-1")) {
        strcpy(bin, "001110");

    } else if (streq(instcomp, "A-1") || streq(instcomp, "M-1")) {
        strcpy(bin, "110010");

    } else if (streq(instcomp, "D+A") || streq(instcomp, "D+M")) {
        strcpy(bin, "000010");

    } else if (streq(instcomp, "D-A") || streq(instcomp, "D-M")) {
        strcpy(bin, "010011");

    } else if (streq(instcomp, "A-D") || streq(instcomp, "M-D")) {
        strcpy(bin, "000111");

    } else if (streq(instcomp, "D&A") || streq(instcomp, "D&M")) {
        strcpy(bin, "000000");

    } else if (streq(instcomp, "D|A") || streq(instcomp, "D|M")) {
        strcpy(bin, "010101");
    }
}

#define DEST_LEN     3
#define A_DEST       0
#define D_DEST       1
#define M_DEST       2
void dest_bin(char *instdest, char *bin)
{
    int i;

    for (i = 0; i < DEST_LEN; ++i)
        bin[i] = OFF;

    i = 0;

    while (instdest[i] != '\0') {
        if (instdest[i] == 'A') {
            bin[A_DEST] = ON;

        } else if (instdest[i] == 'D') {
            bin[D_DEST] = ON;

        } else if (instdest[i] == 'M') {
            bin[M_DEST] = ON;
        }
        ++i;
    }

    bin[DEST_LEN] = '\0';
}

#define JMP_LEN 3

void jmp_bin(char instjmp[], char bin[])
{
    for (int i = 0; i < JMP_LEN; ++i)
        bin[i] = OFF;

    if (streq(instjmp, "JMP")) {
        for (int i = 0; i < JMP_LEN; ++i)
            bin[i] = ON;

    } else if (streq(instjmp, "JGT")) {
        bin[2] = ON;

    } else if (streq(instjmp, "JEQ")) {
        bin[1] = ON;

    } else if (streq(instjmp, "JGE")) {
        bin[1] = bin[2] = ON;

    } else if (streq(instjmp, "JLT")) {
        bin[0] = ON;

    } else if (streq(instjmp, "JNE")) {
        bin[0] = bin[2] = ON;

    } else if (streq(instjmp, "JLE")) {
        bin[0] = bin[1] = ON;
    }

    bin[3] = '\0';
}

