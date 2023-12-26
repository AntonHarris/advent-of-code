#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <libgen.h>

#define BUFFER_SIZE 32
#define NO_SPACING 1
#define ONE_SPACING 2

char * chomp(char *p);
bool is_vowel (char c);
bool has_three_vowels (const char *s);
bool letter_repeat_with_spacing (const char *s, unsigned int spacing);
bool contain_forbidden_strings (const char *s);
bool pair_letters_repeat (const char *s);

int main (int argc, char**argv) {
    if (argc<2) {
        printf("Usage: %s [input_file_path/]input_file\n", basename(argv[0]));
        return 1;
    }

    FILE *in_file = fopen(argv[1], "r");
    if (in_file == NULL) {
        perror("Unable to open file");
        return 1;
    }
    char buffer[BUFFER_SIZE];
    unsigned int count_nice_strings_part_1 = 0;
    unsigned int count_nice_strings_part_2 = 0;
    while (fgets(buffer, sizeof(buffer), in_file)) {
        chomp(buffer);
        if (has_three_vowels(buffer) && letter_repeat_with_spacing(buffer, NO_SPACING) && !contain_forbidden_strings(buffer)) {
            count_nice_strings_part_1++;
        }
        if (pair_letters_repeat(buffer) && letter_repeat_with_spacing(buffer, ONE_SPACING)) {
            count_nice_strings_part_2++;
        }
    }
    fclose(in_file);

    printf("Number of nice strings, part 1: %u.\n", count_nice_strings_part_1);
    printf("Number of nice strings, part 2: %u.\n", count_nice_strings_part_2);
    
    return 0;
}

char * chomp(char *p) {
    while (strlen(p) > 0 && p[strlen(p)-1] == '\n') {
        p[strlen(p)-1] = '\0';
    }
    return p;
}

bool is_vowel (char c) {
    switch (tolower(c)) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
    }
    return false;
}

bool has_three_vowels (const char *s) {
    unsigned int count_vowels = 0;
    while (*s) {
        if (is_vowel(*s)) {
            count_vowels++;
            if (count_vowels>=3) {
                return true;
            }
        }
        s++;
    }

    return false;
}

bool letter_repeat_with_spacing (const char *s, unsigned int spacing) {
    s += spacing;

    while (*s) {
        if (*s == *(s-spacing)) {
            return true;
        }
        s++;
    }

    return false;
}

bool contain_forbidden_strings (const char *s) {
    char *forbidden_strings[] = {"ab", "cd", "pq", "xy"};
    size_t len_forbidden_strings = sizeof(forbidden_strings)/sizeof(forbidden_strings[0]);

    for (size_t i=0 ; i<len_forbidden_strings ; i++) {
        if (strstr(s, forbidden_strings[i])) {
            return true;
        }
    }

    return false;
}

// Alternative method: hash table of all letter pairs, letter pair as key, value is count of occurences
bool pair_letters_repeat (const char *s) {
    char tofind[3] = {0};
    size_t max_attempts = strlen(s);
    if (max_attempts<4) {
        return false;
    }

    max_attempts -= 3;
    for (size_t i=0 ; i<max_attempts ; i++, s++) {
        strncpy(tofind, s, 2);
        if (strstr(s+2, tofind)) {
            return true;
        }
    }

    return false;
}
