#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <libgen.h>

#define BUFFER_SIZE 100
#define LABEL_SIZE 32
#define MAX_INGREDIENTS 10
#define MAX_TEASPOONS 100

typedef struct {
    char label[LABEL_SIZE];
    int capacity;
    int durability;
    int flavour;
    int texture;
    int calories;
} ingredient_t;

char* chomp (char *p);
long calc_max_score (ingredient_t *ingredients, size_t count_ingredients);

int main (int argc, char **argv) {
    if (argc<2) {
        printf("Usage: %s [input_file_path/]input_file\n", basename(argv[0]));
        return 1;
    }

    FILE *in_file = fopen(argv[1], "r");
    char buffer[BUFFER_SIZE] = {0};
    size_t count_ingredients = 0;
    ingredient_t ingredients[MAX_INGREDIENTS];
    if (in_file == NULL) {
        fprintf(stderr, "Unable to open file %s.\n", argv[1]);
        perror("Error message opening file file");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), in_file)) {
        chomp(buffer);
        char *ptr_buffer = strchr(buffer, ':');
        *ptr_buffer = ' ';
        sscanf(buffer, "%s capacity %d, durability %d, flavor %d, texture %d, calories %d",
                       &ingredients[count_ingredients].label[0],
                       &ingredients[count_ingredients].capacity,
                       &ingredients[count_ingredients].durability,
                       &ingredients[count_ingredients].flavour,
                       &ingredients[count_ingredients].texture,
                       &ingredients[count_ingredients].calories);
        count_ingredients++;
    }
    fclose(in_file);

    printf("Max score (without counting calories): %ld.\n", calc_max_score(&ingredients[0], count_ingredients));

    return 0;
}

char* chomp(char *s) {
    size_t s_len = strlen(s);
    while (s_len > 0 && s[--s_len] == '\n') {
        s[s_len] = '\0';
    }
    return s;
}

long calc_max_score (ingredient_t *ingredients, size_t count_ingredients) {
    long max_score = 0;

    return max_score;
}