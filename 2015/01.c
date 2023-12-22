#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char**argv) {
    if (argc<2) {
        char *lastslash = strrchr(argv[0], '/');
        if (lastslash == NULL) { lastslash = argv[0]; }
        printf("Usage: %s [input_file_path/]input_file\n", lastslash+1);
        return 1;
    }

    char buffer[10000] = {0};
    FILE *in_file = fopen(argv[1], "r");
    if (in_file == NULL) {
        // printf("Unable to open file %s.\n", argv[1]);
        perror("Unable to open file");
        return 1;
    }
    if (fgets(buffer, sizeof(buffer)-1, in_file) == NULL) {
        perror("Unable to read from file");
        return 1;
    }
    fclose(in_file);
    if (buffer[strlen(buffer)-1] == '\n') {
        buffer[strlen(buffer)-1] = '\0';
    }

    char *ptr_buffer = &buffer[0];
    int floor = 0;
    int position_enter_basement = 0;
    while (*ptr_buffer) {
        floor += (*ptr_buffer++ == '(' ? 1 : -1);
        if (position_enter_basement == 0 && floor<0) { position_enter_basement = ptr_buffer - &buffer[0]; }
    }
    printf("Floor: %d.\n", floor);
    printf("Position entered basement: %d.\n", position_enter_basement);

    return 0;
}
