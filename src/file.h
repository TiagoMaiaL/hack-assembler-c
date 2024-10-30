#include <stdbool.h>
#include <stdio.h>

int file_error;

void open_in(char *path);
char *read_line();
bool is_eof();
void seek_start();

void open_out(char *path);
void out(char *line);

void close_all();
