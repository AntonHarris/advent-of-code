#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <libgen.h>

char *accept = "1234567890-";

char* chomp(char *p);
long int get_number(const char *s, char **num_end);
long int sum_all_numbers(const char *s);
long int sum_all_non_red_numbers(const char *s);
long int sum_from_array(const char *s, char **array_end);
long int sum_from_object(const char *s, char **object_end);

int main (int argc, char**argv) {
    if (argc<2) {
        printf("Usage: %s [input_file_path/]input_file\n", basename(argv[0]));
        return 1;
    }

    FILE *in_file = fopen(argv[1], "r");
    size_t file_length = 0;
    char *buffer = NULL;
    if (in_file == NULL) {
        fprintf(stderr, "Unable to open file %s.\n", argv[1]);
        perror("Error message opening file file");
        return 1;
    }
    if (fseek(in_file, 0L, SEEK_END) == 0) {
        file_length = (size_t)ftell(in_file);
        fseek(in_file, 0L, SEEK_SET);
        buffer = (char *) calloc (file_length+1, sizeof(char));
    } else {
        perror("Unable to move in the file");
    }
    if (fgets(buffer, file_length, in_file) == NULL) {
        perror("Unable to read from file");
        return 1;
    }
    fclose(in_file);
    chomp(buffer);

    printf("Sum of all numbers: %ld.\n", sum_all_numbers(buffer));
    printf("Sum of all non-red numbers: %ld.\n", sum_all_non_red_numbers(buffer));

    return 0;
}

char* chomp(char *s) {
    size_t s_len = strlen(s);
    while (s_len > 0 && s[--s_len] == '\n') {
        s[s_len] = '\0';
    }
    return s;
}

long int sum_all_numbers(const char *s) {
    long int sum = 0;
    char *ptr_s = (char *)s;
    
    ptr_s = strpbrk(s, accept);
    while (ptr_s) {
        sum += get_number(ptr_s, &ptr_s);
        ptr_s = strpbrk(ptr_s, accept);
    }

    return sum;
}

long int get_number(const char *s, char **num_end) {
    long int num = strtol(s, NULL, 10);
    *num_end += strspn(s, accept);
    return num;
}

long int sum_all_non_red_numbers(const char *s) {
    return *s == '[' ? sum_from_array(s, NULL) : sum_from_object(s, NULL);
}

long int sum_from_array(const char *s, char **array_end) {
    long int sum = 0;
    char *ptr_s = (char *)s;
    ptr_s++;
    while (*ptr_s) {
        switch(*ptr_s) {
            case '[' :
                sum += sum_from_array(ptr_s, &ptr_s);
                ptr_s++;
                break;
            case ']' :
                if (array_end != NULL) {
                    *array_end = ptr_s;
                }
                return sum;
                break;
            case '{' :
                sum += sum_from_object(ptr_s, &ptr_s);
                ptr_s++;
                break;
            case '-' :
            case '0' :
            case '1' :
            case '2' :
            case '3' :
            case '4' :
            case '5' :
            case '6' :
            case '7' :
            case '8' :
            case '9' :
                sum += get_number(ptr_s, &ptr_s);
                break;
            case '"' :
                ptr_s++;
                ptr_s = strchr(ptr_s, '"');
                ptr_s++;
                break;
            case ',' :
                ptr_s++;
                break;
        }
    }
    return sum;
}

long int sum_from_object(const char *s, char **object_end) {
    bool red_found = false;
    long int sum = 0;
    char *ptr_s = (char *)s;
    ptr_s++;
    while (*ptr_s) {
        switch(*ptr_s) {
            case '[' :
                sum += sum_from_array(ptr_s, &ptr_s);
                ptr_s++;
                break;
            case '{' :
                sum += sum_from_object(ptr_s, &ptr_s);
                ptr_s++;
                break;
            case '}' :
                if (red_found) {
                    sum = 0;
                }
                if (object_end != NULL) {
                    *object_end = ptr_s;
                }
                return sum;
                break;
            case '"' : // key/value case, included check for "red" and fetching number
                char *ptr_str_tmp = ptr_s+1;
                ptr_str_tmp = strchr(ptr_str_tmp, '"');
                ptr_str_tmp += 2; // get past the ':'
                if (*ptr_str_tmp == '"') {
                    ptr_str_tmp++;
                    if (strncmp(ptr_str_tmp, "red\"", 4) == 0) {
                        red_found = true;
                    }
                    ptr_str_tmp = strchr(ptr_str_tmp, '"');
                    ptr_str_tmp++;
                } else {
                    sum += get_number(ptr_str_tmp, &ptr_str_tmp);
                }
                ptr_s = ptr_str_tmp;
                break;
            case ',' :
                ptr_s++;
                break;
        }
    }
    return sum;
}
