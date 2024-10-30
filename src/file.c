#include <stdlib.h>
#include "file.h"

bool _is_eof;
FILE *in_file = NULL;
FILE *out_file = NULL;

void open_in(char *path)
{
    _is_eof = false;
    in_file = fopen(path, "r");

    if (in_file == NULL) {
        perror("input file");
    }
}

char *read_line()
{
    long line_len;
    int c;

    line_len = 0;

    while ((c = fgetc(in_file)) != EOF) {
        ++line_len;
        if (c == '\n')
            break;
    }

    if (c == EOF) {
        if (ferror(in_file) == 0) {
            _is_eof = true;

        } else {
            perror("Issue while reading input file");
            abort();
        }
    }

    fseek(in_file, -line_len, SEEK_CUR);

    // Accomodate '\0'
    ++line_len;

    char *buff = malloc(line_len * sizeof(char));

    fgets(buff, line_len + 1, in_file);

    return buff;
}

bool is_eof() {
    return _is_eof;
}

void seek_start()
{
    fseek(in_file, 0, SEEK_SET);
    _is_eof = false;
}

void open_out(char *path)
{
    out_file = fopen(path, "w");

    if (out_file == NULL) {
        perror("output file");
    }
}

void out(char *line)
{
    fputs(line, out_file);
    fputc('\n', out_file);
}

void close_all()
{
    if (in_file != NULL) {
        fclose(in_file);
    }
    
    if (out_file != NULL) {
        fclose(out_file);
    }
}

