#include <stdlib.h>
#include "ainst-bin.h"
#include "utils.h"

void ainst_bin(struct ainst inst, char *bin)
{
    char *valstr = inst.val;
    int val = atoi(valstr);
    itobin(val, bin, WORD_SIZE);
}

