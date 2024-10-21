#include "inst.h"

struct parser_result
{
    short code; // 0 for success, -1 otherwise.
    struct inst parsed_inst;
};

struct parser_result parse(char *source_line);
