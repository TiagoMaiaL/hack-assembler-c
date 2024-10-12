enum token_type {
    whitespace,
    comment,
    char_sequence, // M+1, -1, 0, D, aaa, 1223, ...
    equals, // dest=computation
    semicolon, // computation;jmp
    // TODO: Add a token for symbol
    other // Unrecognizeable type of token
};

struct token {
    enum token_type type;
    char *lexeme;
};

void lex_line(char *source_line);
bool line_finished();
struct token next_token();

