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
long calc_max_score_test (ingredient_t *ingredients, bool include_calories);
long calc_max_score_data (ingredient_t *ingredients, bool include_calories);

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

    // printf("Max score (without taking calories into account): %ld.\n", calc_max_score_test(&ingredients[0], false));
    // printf("Max score (with only 500 calories cookies): %ld.\n", calc_max_score_test(&ingredients[0], true));
    printf("Max score (without taking calories into account): %ld.\n", calc_max_score_data(&ingredients[0], false));
    printf("Max score (with only 500 calories cookies): %ld.\n", calc_max_score_data(&ingredients[0], true));

    return 0;
}

char* chomp(char *s) {
    size_t s_len = strlen(s);
    while (s_len > 0 && s[--s_len] == '\n') {
        s[s_len] = '\0';
    }
    return s;
}

long calc_max_score_test (ingredient_t *ingredients, bool include_calories) {
    long max_score = 0;

    for (int i=0 ; i<MAX_TEASPOONS ; i++) {
        int j = MAX_TEASPOONS-i;
        long curr_capacity = ingredients[0].capacity*i + ingredients[1].capacity*j;
        curr_capacity = curr_capacity<0 ? 0 : curr_capacity;
        long curr_durability = ingredients[0].durability*i + ingredients[1].durability*j;
        curr_durability = curr_durability<0 ? 0 : curr_durability;
        long curr_flavour = ingredients[0].flavour*i + ingredients[1].flavour*j;
        curr_flavour = curr_flavour<0 ? 0 : curr_flavour;
        long curr_texture = ingredients[0].texture*i + ingredients[1].texture*j;
        curr_texture = curr_texture<0 ? 0 : curr_texture;
        long curr_calories = include_calories==false ? 1 : ingredients[0].calories*i + ingredients[1].calories*j;
        curr_calories = curr_calories<0 ? 0 : curr_calories;
        long curr_score = curr_capacity*curr_durability*curr_flavour*curr_texture;
        if (curr_score > max_score && (include_calories ==  false || curr_calories == 500)) {
            max_score = curr_score;
        }
    }

    return max_score;
}

long calc_max_score_data (ingredient_t *ingredients, bool include_calories) {
    long max_score = 0;

    for (int i=0 ; i<MAX_TEASPOONS ; i++) {
        for (int j=0 ; j<MAX_TEASPOONS-i ; j++) {
            for (int k=0 ; k<MAX_TEASPOONS-i-j ; k++) {
                int l = MAX_TEASPOONS-i-j-k;
                long curr_capacity = ingredients[0].capacity*i + ingredients[1].capacity*j + ingredients[2].capacity*k + ingredients[3].capacity*l;
                curr_capacity = curr_capacity<0 ? 0 : curr_capacity;
                long curr_durability = ingredients[0].durability*i + ingredients[1].durability*j + ingredients[2].durability*k + ingredients[3].durability*l;
                curr_durability = curr_durability<0 ? 0 : curr_durability;
                long curr_flavour = ingredients[0].flavour*i + ingredients[1].flavour*j + ingredients[2].flavour*k + ingredients[3].flavour*l;
                curr_flavour = curr_flavour<0 ? 0 : curr_flavour;
                long curr_texture = ingredients[0].texture*i + ingredients[1].texture*j + ingredients[2].texture*k + ingredients[3].texture*l;
                curr_texture = curr_texture<0 ? 0 : curr_texture;
                long curr_calories = include_calories==false ? 1 : ingredients[0].calories*i + ingredients[1].calories*j + ingredients[2].calories*k + ingredients[3].calories*l;
                curr_calories = curr_calories<0 ? 0 : curr_calories;
                long curr_score = curr_capacity*curr_durability*curr_flavour*curr_texture;
                if (curr_score > max_score && (include_calories ==  false || curr_calories == 500)) {
                    max_score = curr_score;
                }
            }
        }
    }

    return max_score;
}
