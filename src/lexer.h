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

// TODO: Check if pointer should be returned.
// TODO: Store an internal source pointer to the char being lexed
struct token next_token(char *source_line);
