enum token_type {
    whitespace,
    comment,
    inst_component, // M+1, -1, 0, D, ...
    equals, // dest=computation
    semicolon, // computation;jmp
    // TODO: Add a token for symbol
}

struct token {
    enum token_type type;
    char *lexeme;
}

// TODO: Check if pointer should be returned.
// TODO: Store an internal source pointer to the char being lexed
token next_token(char *source_line);
