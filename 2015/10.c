#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <libgen.h>

#define BUFFER_SIZE 5000000

void next_sequence (char *s);

int main (int argc, char **argv) {
    if (argc<3) {
        printf("Usage: %s puzzle_input number_cycles\n", basename(argv[0]));
        return 1;
    }

    char *buffer = (char *) calloc (BUFFER_SIZE, sizeof(char));
    unsigned int nbr_cycles = atoi(argv[2]);
    strcpy(buffer, argv[1]);
    for (unsigned int i=0 ; i<nbr_cycles ; i++) {
        next_sequence(buffer);
    }
    printf("Length of final sequence: %lu.\n", strlen(buffer));
    free(buffer);

    return 0;
}

void next_sequence (char *s) {
    char *buffer = (char *) calloc (BUFFER_SIZE, sizeof(char));
    char *ptr_char = s, *ptr_count = NULL, *ptr_buffer = buffer;
    while (*ptr_char) {
        ptr_count = ptr_char;
        while (*ptr_count && *ptr_count==*ptr_char) {
            ptr_count++;
        }
        ptr_buffer += sprintf(ptr_buffer, "%d%c", (int)(ptr_count-ptr_char), *ptr_char);
        ptr_char = ptr_count;
    }
    strcpy(s, buffer);
    free(buffer);
}
