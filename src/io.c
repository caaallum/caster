#include "io.h"
#include <stdio.h>
#include <stdlib.h>

int
io_read_file(const char *filename, char **buff) {
    char *buffer = NULL;
    long length;
    FILE *f = NULL;

    f = fopen(filename, "rb");
    if (f == NULL) {
        return 1;
    }

    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = malloc(sizeof(char) + length);
    if (buffer == NULL) {
        fclose(f);
        return 1;
    }

    fread(buffer, 1, length, f);
    fclose(f);
    buffer[length] = '\0';

    *buff = buffer;
    return 0;
} 
