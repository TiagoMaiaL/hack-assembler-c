#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "utils.h"

bool strin(char *s, char c)
{
    return strchr(s, c) != NULL;
}

void strrev(char * str)
{
    int len;

    len = 0;

    while (str[len] != '\0') {
        ++len;
    }

    int left;
    int right;

    left = 0;
    right = len - 1;

    while (left < right) {
        int leftval, temp;

        leftval = str[left];
        temp = str[right];

        str[left] = temp;
        str[right] = leftval;

        ++left;
        --right;
    }
}

bool streq(char *l, char *r)
{
    return strcmp(l, r) == 0;
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

    strrev(bin);
}

