#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <libgen.h>

#define BUFFER_SIZE 100

char * chomp(char *p);
size_t count_chars_values(const char *s);
size_t count_chars_str_reencoded(const char *s);

int main (int argc, char**argv) {
    if (argc<2) {
        printf("Usage: %s [input_file_path/]input_file\n", basename(argv[0]));
        return 1;
    }

    FILE *in_file = fopen(argv[1], "r");
    char buffer[BUFFER_SIZE] = {0};
    size_t count_characters_lit = 0, count_characters_val = 0, count_characters_reencoded = 0;
    if (in_file == NULL) {
        fprintf(stderr, "Unable to open file %s.\n", argv[1]);
        perror("Error message opening file file");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), in_file)) {
        chomp(buffer);
        count_characters_lit += strlen(buffer);
        count_characters_val += count_chars_values(buffer);
        count_characters_reencoded += count_chars_str_reencoded(buffer);
    }
    fclose(in_file);
    printf("String literals count - characters in memory count = %lu.\n", count_characters_lit-count_characters_val);
    printf("Re-encoded string count - string literals count = %lu.\n", count_characters_reencoded-count_characters_lit);

    return 0;
}

char * chomp(char *s) {
    size_t s_len = strlen(s);
    while (s_len > 0 && s[--s_len] == '\n') {
        s[s_len] = '\0';
    }
    return s;
}

size_t count_chars_values(const char *s) {
    char buffer[BUFFER_SIZE], *ptr_buffer = &buffer[1];
    size_t ret_count = 0;

    strcpy(buffer, s);
    buffer[strlen(buffer)-1] = '\0';
    while (*ptr_buffer) {
        if (*ptr_buffer == '\\') {
            ptr_buffer++;
            switch (*ptr_buffer) {
                case '\\':
                case '"':
                    ptr_buffer++;
                    break;
                case 'x':
                    ptr_buffer += 3;
                    break;
            }
        } else {
            ptr_buffer++;
        }
        ret_count++;
    }

    return ret_count;
}

size_t count_chars_str_reencoded(const char *s) {
    char buffer[2*BUFFER_SIZE] = {0}, *ptr_buffer = buffer;

    *ptr_buffer++ = '"';
    while (*s) {
        if(*s == '"' || *s == '\\') {
            *ptr_buffer++ = '\\';
        }
        *ptr_buffer++ = *s++;
    }
    *ptr_buffer = '"';
    
    return strlen(buffer);
}
