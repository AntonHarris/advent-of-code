#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>

#define BUFFER_SIZE 100
#define GRID_ROWS 1000
#define GRID_COLS 1000

typedef enum Action {
    ACT_TURN_OFF = 0,
    ACT_TURN_ON = 1,
} ACTION;

typedef enum Brightness {
    TURN_OFF = -1,
    TURN_ON = 1,
    TOGGLE = 2,
} BRIGHTNESS;

char* chomp (char *p);
// Part 1 functions declarations
void turn_on_off (int arr[GRID_ROWS][GRID_COLS], int start_coords[], int end_coords[], ACTION action);
void toggle_lights (int arr[GRID_ROWS][GRID_COLS], int start_coords[], int end_coords[]);
int count_lights_lit (const int arr[GRID_ROWS][GRID_COLS]);
// Part 2 functions declarations
void change_light_brightness(int arr[GRID_ROWS][GRID_COLS], int start_coords[], int end_coords[], BRIGHTNESS change);
int calc_lights_brightness(const int arr[GRID_ROWS][GRID_COLS]);

int main (int argc, char **argv) {
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
    int light_grid_part_1[GRID_ROWS][GRID_COLS] = { [0 ... (GRID_ROWS-1)] = { [0 ... (GRID_COLS-1)] = 0 }};
    int light_grid_part_2[GRID_ROWS][GRID_COLS] = { [0 ... (GRID_ROWS-1)] = { [0 ... (GRID_COLS-1)] = 0 }};
    while (fgets(buffer, sizeof(buffer), in_file)) {
        chomp(buffer);
        int start_coords[2], end_coords[2];
        switch(buffer[6]) { // lazy way of doing this
            case ' ': // toggle
                sscanf(buffer, "toggle %d,%d through %d,%d", &start_coords[0], &start_coords[1], &end_coords[0], &end_coords[1]);
                toggle_lights(light_grid_part_1, start_coords, end_coords);
                change_light_brightness(light_grid_part_2, start_coords, end_coords, TOGGLE);
                break;
            case 'f': // turn off
                sscanf(buffer, "turn off %d,%d through %d,%d", &start_coords[0], &start_coords[1], &end_coords[0], &end_coords[1]);
                turn_on_off(light_grid_part_1, start_coords, end_coords, ACT_TURN_OFF);
                change_light_brightness(light_grid_part_2, start_coords, end_coords, TURN_OFF);
                break;
            case 'n': // turn on
                sscanf(buffer, "turn on %d,%d through %d,%d", &start_coords[0], &start_coords[1], &end_coords[0], &end_coords[1]);
                turn_on_off(light_grid_part_1, start_coords, end_coords, ACT_TURN_ON);
                change_light_brightness(light_grid_part_2, start_coords, end_coords, TURN_ON);
                break;
        }
    }
    printf("Number of lit lights: %d.\n", count_lights_lit(light_grid_part_1));
    printf("Total light grid brightness: %d.\n", calc_lights_brightness(light_grid_part_2));

    fclose(in_file);

    return 0;
}

char* chomp (char *p) {
    while (strlen(p) > 0 && p[strlen(p)-1] == '\n') {
        p[strlen(p)-1] = '\0';
    }
    return p;
}

// Part 1 functions
void turn_on_off (int arr[GRID_ROWS][GRID_COLS], int start_coords[], int end_coords[], ACTION action) {
    for (int i=start_coords[0] ; i<=end_coords[0] ; i++) {
        for (int j=start_coords[1] ; j<=end_coords[1] ; j++) {
            arr[i][j] = action;
        }
    }
}

void toggle_lights (int arr[GRID_ROWS][GRID_COLS], int start_coords[], int end_coords[]) {
    for (int i=start_coords[0] ; i<=end_coords[0] ; i++) {
        for (int j=start_coords[1] ; j<=end_coords[1] ; j++) {
            arr[i][j] = !arr[i][j];
        }
    }
}

int count_lights_lit(const int arr[GRID_ROWS][GRID_COLS]) {
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

// Part 2 functions
void change_light_brightness(int arr[GRID_ROWS][GRID_COLS], int start_coords[], int end_coords[], BRIGHTNESS change) {
    for (int i=start_coords[0] ; i<=end_coords[0] ; i++) {
        for (int j=start_coords[1] ; j<=end_coords[1] ; j++) {
            arr[i][j] += change;
            if (arr[i][j] < 0) {
                arr[i][j] = 0;
            }
        }
    }
}

int calc_lights_brightness(const int arr[GRID_ROWS][GRID_COLS]) {
    int lights_brightness = 0;
    for (int i=0 ; i<GRID_ROWS ; i++) {
        for (int j=0 ; j<GRID_COLS ; j++) {
            lights_brightness += arr[i][j];
        }
    }
    return lights_brightness;
}
