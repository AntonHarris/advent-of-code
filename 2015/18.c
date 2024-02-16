#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <libgen.h>

#define GRID_DIM 100
#define NUM_STEPS 100

char* chomp(char *p);
void execute_step(char grid[GRID_DIM][GRID_DIM]);
unsigned int count_lights_on(char grid[GRID_DIM][GRID_DIM]);

int main (int argc, char **argv) {
    if (argc<2) {
        printf("Usage: %s [input_file_path/]input_file\n", basename(argv[0]));
        return 1;
    }

    FILE *in_file = fopen(argv[1], "r");
    char grid[GRID_DIM][GRID_DIM];
    char grid2[GRID_DIM][GRID_DIM];
    char buffer[GRID_DIM+2]; // 2 to account for '\n\0'
    if (in_file == NULL) {
        fprintf(stderr, "Unable to open file %s.\n", argv[1]);
        perror("Error message opening file file");
        return 1;
    }
    int idx = 0;
    while (fgets(buffer, sizeof(buffer), in_file)) {
        chomp(buffer);
        strncpy(&grid[idx][0], buffer, GRID_DIM);
        strncpy(&grid2[idx][0], buffer, GRID_DIM);
        idx++;
    }
    fclose(in_file);

    // Part 1
    for (int i=0 ; i<NUM_STEPS ; i++) {
        execute_step(grid);

        grid2[0][0] = '#';
        grid2[0][GRID_DIM-1] = '#';
        grid2[GRID_DIM-1][0] = '#';
        grid2[GRID_DIM-1][GRID_DIM-1] = '#';
        execute_step(grid2);
        grid2[0][0] = '#';
        grid2[0][GRID_DIM-1] = '#';
        grid2[GRID_DIM-1][0] = '#';
        grid2[GRID_DIM-1][GRID_DIM-1] = '#';
    }
    printf("There are %u lights on after %d steps.\n", count_lights_on(grid), NUM_STEPS);
    printf("There are %u lights on after %d steps with corners stuck on.\n", count_lights_on(grid2), NUM_STEPS);

    return 0;
}

char* chomp(char *s) {
    size_t s_len = strlen(s);
    while (s_len > 0 && s[--s_len] == '\n') {
        s[s_len] = '\0';
    }
    return s;
}

void execute_step(char grid[GRID_DIM][GRID_DIM]) {
    char tmp_grid[GRID_DIM][GRID_DIM] = { [0 ... (GRID_DIM-1)] = { [0 ... (GRID_DIM-1)] = '.' }};;
    // corners
    int neighbours = 0;
    if (grid[0][1] == '#') neighbours++;
    if (grid[1][1] == '#') neighbours++;
    if (grid[1][0] == '#') neighbours++;
    if ((grid[0][0] == '#' && neighbours>1) || (grid[0][0] == '.' && neighbours==3))
        tmp_grid[0][0] = '#';

    neighbours = 0;
    if (grid[0][GRID_DIM-2] == '#') neighbours++;
    if (grid[1][GRID_DIM-2] == '#') neighbours++;
    if (grid[1][GRID_DIM-1] == '#') neighbours++;
    if ((grid[0][GRID_DIM-1] == '#' && neighbours>1) || (grid[0][GRID_DIM-1] == '.' && neighbours==3))
        tmp_grid[0][GRID_DIM-1] = '#';

    neighbours = 0;
    if (grid[GRID_DIM-2][0] == '#') neighbours++;
    if (grid[GRID_DIM-2][1] == '#') neighbours++;
    if (grid[GRID_DIM-1][1] == '#') neighbours++;
    if ((grid[GRID_DIM-1][0] == '#' && neighbours>1) || (grid[GRID_DIM-1][0] == '.' && neighbours==3))
        tmp_grid[GRID_DIM-1][0] = '#';

    neighbours = 0;
    if (grid[GRID_DIM-2][GRID_DIM-1] == '#') neighbours++;
    if (grid[GRID_DIM-2][GRID_DIM-2] == '#') neighbours++;
    if (grid[GRID_DIM-1][GRID_DIM-2] == '#') neighbours++;
    if ((grid[GRID_DIM-1][GRID_DIM-1] == '#' && neighbours>1) || (grid[GRID_DIM-1][GRID_DIM-1] == '.' && neighbours==3))
        tmp_grid[GRID_DIM-1][GRID_DIM-1] = '#';

    // first and last line, sans corners
    for (int i=1 ; i<(GRID_DIM-1) ; i++) {
        neighbours = 0;
        if (grid[0][i-1] == '#') neighbours++;
        if (grid[0][i+1] == '#') neighbours++;
        if (grid[1][i-1] == '#') neighbours++;
        if (grid[1][i+1] == '#') neighbours++;
        if (grid[1][i] == '#') neighbours++;
        if ((grid[0][i] == '#' && (neighbours==2 || neighbours == 3)) || (grid[0][i] == '.' && neighbours==3))
            tmp_grid[0][i] = '#';

        neighbours = 0;
        if (grid[GRID_DIM-1][i-1] == '#') neighbours++;
        if (grid[GRID_DIM-1][i+1] == '#') neighbours++;
        if (grid[GRID_DIM-2][i-1] == '#') neighbours++;
        if (grid[GRID_DIM-2][i+1] == '#') neighbours++;
        if (grid[GRID_DIM-2][i] == '#') neighbours++;
        if ((grid[GRID_DIM-1][i] == '#' && (neighbours==2 || neighbours == 3)) || (grid[GRID_DIM-1][i] == '.' && neighbours==3))
            tmp_grid[GRID_DIM-1][i] = '#';

        neighbours = 0;
        if (grid[i-1][0] == '#') neighbours++;
        if (grid[i+1][0] == '#') neighbours++;
        if (grid[i-1][1] == '#') neighbours++;
        if (grid[i+1][1] == '#') neighbours++;
        if (grid[i][1] == '#') neighbours++;
        if ((grid[i][0] == '#' && (neighbours==2 || neighbours == 3)) || (grid[i][0] == '.' && neighbours==3))
            tmp_grid[i][0] = '#';

        neighbours = 0;
        if (grid[i-1][GRID_DIM-1] == '#') neighbours++;
        if (grid[i+1][GRID_DIM-1] == '#') neighbours++;
        if (grid[i-1][GRID_DIM-2] == '#') neighbours++;
        if (grid[i+1][GRID_DIM-2] == '#') neighbours++;
        if (grid[i][GRID_DIM-2] == '#') neighbours++;
        if ((grid[i][GRID_DIM-1] == '#' && (neighbours==2 || neighbours == 3)) || (grid[i][GRID_DIM-1] == '.' && neighbours==3))
            tmp_grid[i][GRID_DIM-1] = '#';
    }
    // middle square
    for (int i=1 ; i<(GRID_DIM-1) ; i++) {
        for (int j=1 ; j<(GRID_DIM-1) ; j++) {
            neighbours = 0;
            if (grid[i-1][j-1] == '#') neighbours++;
            if (grid[i-1][j] == '#') neighbours++;
            if (grid[i-1][j+1] == '#') neighbours++;
            if (grid[i][j-1] == '#') neighbours++;
            if (grid[i][j+1] == '#') neighbours++;
            if (grid[i+1][j-1] == '#') neighbours++;
            if (grid[i+1][j] == '#') neighbours++;
            if (grid[i+1][j+1] == '#') neighbours++;
            if ((grid[i][j] == '#' && (neighbours==2 || neighbours == 3)) || (grid[i][j] == '.' && neighbours==3))
            tmp_grid[i][j] = '#';
        }
    }

    memcpy(grid, tmp_grid, GRID_DIM*GRID_DIM);
}

unsigned int count_lights_on(char grid[GRID_DIM][GRID_DIM]) {
    unsigned int count_lights_on = 0;
    for (int i=0 ; i<GRID_DIM ; i++) {
        for (int j=0 ; j<GRID_DIM ; j++) {
            if (grid[i][j] == '#') count_lights_on++;
        }
    }
    return count_lights_on;
}