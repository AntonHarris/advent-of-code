#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <libgen.h>

#define BUFFER_SIZE 100
#define CITY_SIZE 32

typedef struct buffer_struct {
    char src_city[CITY_SIZE];
    char dst_city[CITY_SIZE];
    unsigned int distance;
} BUFFER_STRUCT;

char* chomp(char *p);

int main (int argc, char**argv) {
    if (argc<2) {
        printf("Usage: %s [input_file_path/]input_file\n", basename(argv[0]));
        return 1;
    }

    char buffer[BUFFER_SIZE] = {0};
    FILE *in_file = fopen(argv[1], "r");
    if (in_file == NULL) {
        fprintf(stderr, "Unable to open file %s.\n", argv[1]);
        perror("Error message opening file file");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), in_file)) {
        chomp(buffer);
        // Dublin to Belfast = 141
        BUFFER_STRUCT tmp_node;
        sscanf(buffer, "%s to %s = %u", &(tmp_node.src_city[0]), &(tmp_node.dst_city[0]), &(tmp_node.distance));
        printf("Distance between %s and %s is %u.\n", tmp_node.src_city, tmp_node.dst_city, tmp_node.distance);
    }
    fclose(in_file);

    return 0;
}

char* chomp(char *s) {
    size_t s_len = strlen(s);
    while (s_len > 0 && s[--s_len] == '\n') {
        s[s_len] = '\0';
    }
    return s;
}