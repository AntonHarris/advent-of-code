#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char * chomp(char *p) {
    while (p[strlen(p)-1] == '\n') {
        p[strlen(p)-1] = '\0';
    }
    return p;
}

int main (int argc, char**argv) {
    if (argc<2) {
        char *lastslash = strrchr(argv[0], '/');
        if (lastslash == NULL) { lastslash = argv[0]; }
        printf("Usage: %s [input_file_path/]input_file\n", lastslash+1);
        return 1;
    }

    FILE *in_file = fopen(argv[1], "r");
    if (in_file == NULL) {
        perror("Unable to open file");
        return 1;
    }
    fclose(in_file);

}