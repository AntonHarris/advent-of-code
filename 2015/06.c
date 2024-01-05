#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>

#define BUFFER_SIZE 100
#define GRID_ROWS 1000
#define GRID_COLS 1000
#define TURN_ON 1
#define TURN_OFF 0

char * chomp(char *p);
void turn_on_off(int *arr[], int *start_coords, int *end_coords, int action);
int count_lights_lit(const int *arr[]);

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
    int light_grid[GRID_ROWS][GRID_COLS] = {0};
    while (fgets(buffer, sizeof(buffer), in_file)) {
        chomp(buffer);
        int start_coords[2], end_coords[2];
        switch(buffer[6]) { // lazy way of doing this
            case ' ': // toggle
                sscanf(buffer, "toggle %d,%d through %d,%d", &start_coords[0], &start_coords[1], &end_coords[0], &end_coords[1]);
                break;
            case 'f': // turn off
                sscanf(buffer, "turn off %d,%d through %d,%d", &start_coords[0], &start_coords[1], &end_coords[0], &end_coords[1]);
                turn_on_off(light_grid, start_coords, end_coords, TURN_OFF);
                break;
            case 'n': // turn on
                sscanf(buffer, "turn on %d,%d through %d,%d", &start_coords[0], &start_coords[1], &end_coords[0], &end_coords[1]);
                turn_on_off(light_grid, start_coords, end_coords, TURN_ON);
                break;
        }
    }
    fclose(in_file);

    printf("Number of lit lights: %d.\n", count_lights_lit(light_grid));

    return 0;
}

char * chomp(char *p) {
    while (strlen(p) > 0 && p[strlen(p)-1] == '\n') {
        p[strlen(p)-1] = '\0';
    }
    return p;
}

void turn_on_off(int *arr[], int start_coords[], int end_coords[], int action) {
    for (int i=start_coords[0] ; i<=end_coords[0] ; i++) {
        // void *memset(void s[.n], int c, size_t n);
        memset(arr+(i*GRID_COLS)+start_coords[1], action, (end_coords[1]-start_coords[1]+1));
    }
}

int count_lights_lit(const int *arr[]) {
    int count_lights_on = 0;
    for (int i=0 ; i<GRID_ROWS ; i++) {
        for (int j=0 ; j<GRID_COLS ; j++) {
            if (arr[i][j] != 0) {
                count_lights_on++;
            }
        }
    }
    return count_lights_on;
}
