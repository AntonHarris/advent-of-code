#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <libgen.h>

int main (int argc, char**argv) {
    if (argc<2) {
        printf("Usage: %s [input_file_path/]input_file\n", basename(argv[0]));
        return 1;
    }

    FILE *in_file = fopen(argv[1], "r");
    char *buffer = NULL;
    size_t file_length = 0;
    if (in_file == NULL) {
        fprintf(stderr, "Unable to open file %s.\n", argv[0]);
        perror("Error message opening file file");
        return 1;
    }
    if (fseek(in_file, 0L, SEEK_END) == 0) {
        file_length = (size_t)ftell(in_file);
        fseek(in_file, 0L, SEEK_SET);
        buffer = (char *) calloc (file_length+1, sizeof(char));
    } else {
        perror("Unable to move in the file");
        return 1;
    }
    if (fgets(buffer, file_length, in_file) == NULL) {
        perror("Unable to read from file");
        return 1;
    }
    fclose(in_file);

    return 0;
}