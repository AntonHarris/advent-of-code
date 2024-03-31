#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <libgen.h>

#define BUFFER_SIZE 16

bool test_three_letter_suite (const char *s);
bool test_forbidden_letters (const char *s);
bool test_count_letter_pairs (const char *s);
bool valid_password (const char *s);
void find_next_password (const char *s);

int main (int argc, char **argv) {
    if (argc<2) {
        printf("Usage: %s puzzle_input\n", basename(argv[0]));
        return 1;
    }

    find_next_password(argv[1]);

    return 0;
}

bool test_three_letter_suite (const char *s) {
    size_t s_len = strlen(s);
    if (s_len<3) {
        return false;
    }

    s_len -= 2;
    for (size_t i=0 ; i<s_len ; i++, s++) {
        if (*(s+1) == (*s)+1 && *(s+2) == (*s)+2) {
            return true;
        }
    }

    return false;
}

bool test_forbidden_letters (const char *s) {
    const char *forbidden = "iol";

    for (char *ptr_forbidden = (char *)forbidden ; *ptr_forbidden ; ptr_forbidden++) {
        if (strchr(s, *ptr_forbidden)) {
            return false;
        }
    }

    return true;
}

bool test_count_letter_pairs (const char *s) {
    size_t s_len = strlen(s);
    if (s_len<4) {
        return false;
    }

    size_t count_pairs = 0;
    s_len -= 1;
    for (size_t i=0 ; i<s_len ; i++) {
        if (s[i] == s[i+1]) {
            count_pairs++;
            i++;
        }
    }

    return count_pairs>1;
}

bool valid_password (const char *s) {
    return test_three_letter_suite(s) && test_forbidden_letters(s) && test_count_letter_pairs(s);
}

void find_next_password (const char *s) {
    char buffer[BUFFER_SIZE] = {0};
    strcpy(buffer, s);

    do {
        int i = strlen(buffer)-1;
        bool carry = true;
        while (carry) {
            carry = false;
            if (buffer[i] == 'z') {
                buffer[i] = 'a';
                carry = true;
                i--;
            } else {
                buffer[i]++;
            }
        }
    } while (!valid_password(buffer));

    printf("Next valid password: %s.\n", buffer);
}
