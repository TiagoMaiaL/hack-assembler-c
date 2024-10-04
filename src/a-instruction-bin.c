#include <stdlib.h>
#include "a-instruction-bin.h"
#include "utils.h"

void ainstbin(struct ainst inst, char *bin)
{
    char *valstr = inst.val;
    int val = atoi(valstr);
    itobin(val, bin, WORD_SIZE);
}

