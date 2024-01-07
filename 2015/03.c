#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <libgen.h>

typedef struct coords_house {
    int x;
    int y;
    struct coords_house *next;
} COORDS_HOUSE;

#define X_COORD 0
#define Y_COORD 1

char * chomp(char *p);
bool house_exists (const COORDS_HOUSE *already_Visited, const COORDS_HOUSE *house_to_check);
COORDS_HOUSE * add_new_house(int x, int y, COORDS_HOUSE *next_house);
COORDS_HOUSE * check_and_add_house(int x, int y, COORDS_HOUSE *next_house);
unsigned int count_houses (const COORDS_HOUSE *houses);
void free_houses (COORDS_HOUSE **houses);

int main (int argc, char**argv) {
    if (argc<2) {
        printf("Usage: %s [input_file_path/]input_file\n", basename(argv[0]));
        return 1;
    }

    FILE *in_file = fopen(argv[1], "r");
    char *buffer = NULL;
    size_t file_length = 0;
    if (in_file == NULL) {
        fprintf(stderr, "Unable to open file %s.\n", argv[1]);
        perror("Error message opening file file");
        return 1;
    }
    if (fseek(in_file, 0L, SEEK_END) == 0) {
        file_length = (size_t)ftell(in_file);
        fseek(in_file, 0L, SEEK_SET); // Supposing that if I could move to end, no issues returning to start
        buffer = (char *) calloc (file_length+1, sizeof(char));
    } else {
        perror("Unable to move in the file");
        return 1;
    }
    if (fgets(buffer, file_length, in_file) == NULL) {
        perror("Unable to read from file");
        return 1;
    }
    fclose(in_file);
    chomp(buffer);

    COORDS_HOUSE *santa_alone = add_new_house(0, 0, NULL);
    COORDS_HOUSE *santa_with_robo = add_new_house(0, 0, NULL);
    char *ptr_buffer = buffer;
    int santa_alone_coords[2] = {0, 0};
    int santa_with_robo_coords[2][2] = { [0 ... 1] = { [0 ... 1] = 0 }};
    int santa_or_robo = 0; // Santa is 0, Robot is 1
    while (*ptr_buffer) {
        switch (*ptr_buffer++) {
            case '^':
                santa_alone_coords[Y_COORD]++;
                santa_with_robo_coords[santa_or_robo][Y_COORD]++;
                break;
            case '>':
                santa_alone_coords[X_COORD]++;
                santa_with_robo_coords[santa_or_robo][X_COORD]++;
                break;
            case 'v':
                santa_alone_coords[Y_COORD]--;
                santa_with_robo_coords[santa_or_robo][Y_COORD]--;
                break;
            case '<':
                santa_alone_coords[X_COORD]--;
                santa_with_robo_coords[santa_or_robo][X_COORD]--;
                break;
        }
        santa_alone = check_and_add_house(santa_alone_coords[X_COORD], santa_alone_coords[Y_COORD], santa_alone);
        santa_with_robo = check_and_add_house(santa_with_robo_coords[santa_or_robo][X_COORD], santa_with_robo_coords[santa_or_robo][Y_COORD], santa_with_robo);
        santa_or_robo = !santa_or_robo;
    }
    printf("Houses visited by Santa alone: %u.\n", count_houses(santa_alone));
    printf("Houses visited by Santa and Robot: %u.\n", count_houses(santa_with_robo));

    free(buffer);
    return 0;
}

char * chomp(char *p) {
    while (strlen(p) > 0 && p[strlen(p)-1] == '\n') {
        p[strlen(p)-1] = '\0';
    }
    return p;
}

bool house_exists (const COORDS_HOUSE *already_Visited, const COORDS_HOUSE *house_to_check) {
    while (already_Visited) {
        if (already_Visited->x == house_to_check->x && already_Visited->y == house_to_check->y) {
            return true;
        }
        already_Visited = already_Visited->next;
    }
    return false;
}

COORDS_HOUSE * add_new_house(int x, int y, COORDS_HOUSE *next_house) {
    COORDS_HOUSE *new_house = (COORDS_HOUSE *) calloc (sizeof(COORDS_HOUSE), 1);
    if (new_house) {
        new_house->x = x;
        new_house->y = y;
        new_house->next = next_house;
    } else {
        perror("Unable to calloc for new house");
        exit(1);
    }
    return new_house;
}

COORDS_HOUSE * check_and_add_house(int x, int y, COORDS_HOUSE *next_house) {
    COORDS_HOUSE new_house = {
        .x = x,
        .y = y
    };
    if (!house_exists(next_house, &new_house)) {
        return add_new_house(new_house.x, new_house.y, next_house);
    }

    return next_house;
}

unsigned int count_houses (const COORDS_HOUSE *houses) {
    unsigned int houses_counted = 0;
    while (houses) {
        houses_counted++;
        houses = houses->next;
    }
    return houses_counted;
}

void free_houses (COORDS_HOUSE **houses) {
    COORDS_HOUSE *ptr_houses = *houses;
    *houses = NULL;
    while (ptr_houses) {
        COORDS_HOUSE *tmp_ptr = ptr_houses;
        ptr_houses = ptr_houses->next;
        free(tmp_ptr);
    }
    return;
}
