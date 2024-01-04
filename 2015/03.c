#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <libgen.h>

char * chomp(char *p);

int main (int argc, char**argv) {
    if (argc<2) {
        printf("Usage: %s [input_file_path/]input_file\n", basename(argv[0]));
        return 1;
    }

    FILE *in_file = fopen(argv[1], "r");
    char *buffer = NULL;
    size_t file_length = 0;
    if (in_file == NULL) {
        fprintf(stderr, "Unable to open file %s.\n", argv[0]);
        perror("Error message opening file file");
        return 1;
    }
    if (fseek(in_file, 0L, SEEK_END) == 0) {
        file_length = (size_t)ftell(in_file);
        fseek(in_file, 0L, SEEK_SET);
        buffer = (char *) calloc (file_length+1, sizeof(char));
    } else {
        perror("Unable to move in the file");
        return 1;
    }
    if (fgets(buffer, file_length, in_file) == NULL) {
        perror("Unable to read from file");
        return 1;
    }
    chomp(buffer);
    fclose(in_file);

    // Calculate max X and Y coordinates
    int x_coord[2] = {0}, y_coord[2] = {0};
    int curr_x_coord = 0, curr_y_coord = 0;
    char *ptr_data = buffer;
    while (*ptr_data) {
        switch(*ptr_data) {
            case '^':
                curr_y_coord++;
                if (curr_y_coord > y_coord[1]) {
                    y_coord[1] = curr_y_coord;
                }
                break;
            case '>':
                curr_x_coord++;
                if (curr_x_coord > x_coord[1]) {
                    x_coord[1] = curr_x_coord;
                }
                break;
            case 'v':
                curr_y_coord--;
                if (curr_y_coord < y_coord[0]) {
                    y_coord[0] = curr_y_coord;
                }
                break;
            case '<':
                curr_x_coord--;
                if (curr_x_coord < x_coord[0]) {
                    x_coord[0] = curr_x_coord;
                }
                break;
        }
        ptr_data++;
    }

    // Create presents map
    int x_size = x_coord[1]-x_coord[0]+1, y_size = y_coord[1]-y_coord[0]+1;
    int map_size = x_size*y_size;
    int *presents_map = (int *) calloc (map_size, sizeof(int));
    
    // Distribute presents, Santa alone
    ptr_data = buffer;
    int santa_x_coord[2] = {-x_coord[0]};
    int santa_y_coord[2] = {-y_coord[0]};
    int santa_or_robo = 0;
    *(presents_map+(santa_y_coord[0]*x_size)+santa_x_coord[0]) = 1;
    while (*ptr_data) {
        switch(*ptr_data) {
            case '^':
                santa_y_coord[santa_or_robo]++;
                break;
            case '>':
                santa_x_coord[santa_or_robo]++;
                break;
            case 'v':
                santa_y_coord[santa_or_robo]--;
                break;
            case '<':
                santa_x_coord[santa_or_robo]--;
                break;
        }
        *(presents_map+(santa_y_coord[santa_or_robo]*x_size)+santa_x_coord[santa_or_robo]) += 1;
        ptr_data++;
    }

    // Count houses with presents
    int *ptr_presents_map = presents_map;
    int houses_with_presents = 0;
    for (int i=0 ; i<map_size ; i++, ptr_presents_map++) {
        if (*ptr_presents_map > 0) {
            houses_with_presents++;
        }
    }
    printf("Houses with multiple presents, part 1: %d.\n", houses_with_presents);

    free(presents_map);
    free(buffer);

    return 0;
}

char * chomp(char *p) {
    while (strlen(p) > 0 && p[strlen(p)-1] == '\n') {
        p[strlen(p)-1] = '\0';
    }
    return p;
}
