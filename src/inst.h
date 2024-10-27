#ifndef INST_H
#define INST_H
struct ainst {
    char *val;
};

struct cinst {
    char *dest;
    char *comp;
    char *jmp;
};

enum inst_type {
    none,
    a_inst_type, 
    c_inst_type
};

struct inst {
    enum inst_type type;
    struct cinst c_inst;
    struct ainst a_inst;
};
#endif
