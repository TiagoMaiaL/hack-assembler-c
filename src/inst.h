struct ainst {
    char *val;
};

struct cinst {
    char *dest;
    char *comp;
    char *jmp;
};

enum inst_type {
    a, 
    c
};

struct inst {
    enum inst_type type;
    struct cinst c_inst;
    struct ainst a_inst;
};
