#include <stdio.h>

struct cinst {
    char * dest;
    char * comp;
    char * jmp;
};

char * instbin(struct cinst);
void destbin(char[], char[]);
void jmpbin(char[], char[]);

int main()
{
    // For MVP:
    // 1. Parse input text into tokens
    // 2. Parse tokens into instructions or errors
    // 3. Translate instructions into bin code

    struct cinst comp;
    comp.dest = "D";
    comp.comp = "";
    comp.jmp = "JLE";

    char jmpbinout[4];
    jmpbin(comp.jmp, jmpbinout);

    printf("%s", jmpbinout);

    return 0;
}

#define ON    '1'
#define OFF   '0'

char * instbin(struct cinst comp)
{
    
    return "1110011111010000";
}

#define DEST_MAX_LEN 3
#define A_DEST       0
#define D_DEST       1
#define M_DEST       2

void destbin(char instdest[], char bin[])
{
    int i;

    for (i = 0; i < DEST_MAX_LEN; ++i)
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

    instdest[i] = '\0';
}

// TODO: Move helper functions to their own file.
short streq(char *l, char *r)
{
    int i = 0;
    short eq = 1;

    while (l[i] == r[i] && l[i] != '\0' && eq == 1) {
        eq = 1;
        ++i;
    }

    if (l[i] != r[i])
        eq = 0;

    return eq;
}

#define JMP_MAX_LEN 3

void jmpbin(char instjmp[], char bin[])
{
    for (int i = 0; i < JMP_MAX_LEN; ++i)
        bin[i] = OFF;

    if (streq(instjmp, "JMP")) {
        for (int i = 0; i < JMP_MAX_LEN; ++i)
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

