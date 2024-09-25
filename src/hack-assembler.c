#include <stdio.h>
#include <string.h>

#define ON        '1'
#define OFF       '0'
#define WORD_SIZE 16

struct cinst {
    char * dest;
    char * comp;
    char * jmp;
};

// TODO: Use the functions in stdlib
short streq(char *, char *);
short strin(char, char *);

// TODO: Document each one of these functions.
void cinstbin(char *, struct cinst);
void compbin(char * instcomp, char * bin);
void destbin(char[], char[]);
void jmpbin(char[], char[]);

struct ainst {
    char * val;
};

// TODO: Implement atoi and then use the function in stdlib
int atoi(char *);
void itobin(int, char *, int);
void ainstbin(struct ainst, char *);
int ipow(int, int);

// TODO: Check if converting negative integers will be needed.
int atoi(char *str)
{
    int c;
    int i;
    int count;

    i = 0;
    count = 0;
    
    while ((c = str[i]) != '\0') {
        // Validate str (must contain only digits)
        if (!(c >= '0' && c <= '9')) {
            return -1; // Let's use -1 for now, until we find a better value to return here.
        }
        ++i;
    }

    count = i;
    
    short digits[i];

    i = 0;

    while ((c = str[i]) != '\0') {
        short digit;

        digit = c - '0';
        digits[i] = digit;

        ++i;
    }

    int result;
    int end = count - 1;

    for (i = end; i >= 0; --i) {
        short digit = digits[i];
        result += digit * ipow(10, end - i);
    }

    return result;
}

int ipow(int n, int exp)
{
    if (exp == 0)
        return 1;
    else if (exp == 1)
        return n;
    else {
        long long result = 1;

        for (int i = 0; i < exp; ++i)
            result *= n;
        
        return result;
    }
}

void itobin(int val, char *bin, int bincount) {
    int i, res, rem;

    for (i = 0; i < bincount; ++i)
        bin[i] = OFF;

    bin[bincount] = '\0';

    i = 0;
    res = val;
    rem = 0;

    while (res > 0 && i < bincount) {
        rem = res % 2;
        res = res / 2;

        if (rem == 0) {
            bin[i] = OFF;
        } else {
            bin[i] = ON;
        }

        if (res == 1) {
            ++i;
            bin[i] = ON;
            res = 0;
        }

        ++i;
    }

    // Reverse the bin string.
    // TODO: Check if there's a stdlib function for this.
    // TODO: If there's, replace this code with it.
    // TODO: If not, extract this into a helper function.
    if (i > 0) {
        int left = 0;
        int right = bincount - 1;

        while (left < right) {
            int leftval, temp;

            leftval = bin[left];
            temp = bin[right];

            bin[left] = temp;
            bin[right] = leftval;

            ++left;
            --right;
        }
    }
}

void ainstbin(struct ainst inst, char *bin)
{
    char *valstr = inst.val;
    int val = atoi(valstr);
    itobin(val, bin, WORD_SIZE);
}

int main()
{
    // For MVP:
    // 1. Parse input text into tokens
    // 2. Parse tokens into instructions or errors
    // 3. Translate instructions into bin code
    struct ainst inst;
    inst.val = "123";

    char bin[WORD_SIZE];
    ainstbin(inst, bin);
    printf("@123 in binary = %s\n", bin);

    struct cinst inst2;
    inst2.dest = "A";
    inst2.comp = "-1";

    char cbin[WORD_SIZE];
    cinstbin(cbin, inst2);

    printf("A = -1 in binary = %s\n", cbin);

    return 0;
}

void cinstbin(char *bin, struct cinst comp)
{
    strcpy(bin, "111");

    char compbinary[8];
    compbin(comp.comp, compbinary);
    strcpy(bin + 3, compbinary);

    char destbinary[4];
    destbin(comp.dest, destbinary);
    strcpy(bin + 3 + 7, destbinary);

    char jmpbinary[4];
    jmpbin(comp.jmp, jmpbinary);
    strcpy(bin + 3 + 7 + 3, jmpbinary);
}

short strin(char c, char *str)
{
    int i;

    for (i = 0; str[i] != '\0'; ++i) {
        if (str[i] == c) {
            return 1;
        }
    }

    return 0;
}

void compbin(char * instcomp, char * bin)
{
    if (strin('M', instcomp)) {
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

    bin[DEST_MAX_LEN] = '\0';
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

