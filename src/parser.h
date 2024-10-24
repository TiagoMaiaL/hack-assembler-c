#include "inst.h"

#define PARSE_ERROR -1
#define PARSE_SUCCESS 0

struct parser_result
{
    short code; // 0 for success, -1 otherwise.
    struct inst parsed_inst;
};

struct parser_result parse(char *source_line);
