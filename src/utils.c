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

