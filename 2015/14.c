#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <libgen.h>

#define REINDEER_BUFFER_SIZE 10
#define BUFFER_SIZE 100
#define RACE_TIME 2503

typedef enum Reindeer_state {
    REINDEER_FLYING = 0,
    REINDEER_RESTING = 1,
} REINDEER_STATE;

typedef struct reindeer {
    char name[20];
    unsigned int flight_speed;
    unsigned int flight_duration;
    unsigned int rest_time;
} REINDEER;

char* chomp(char *p);
unsigned int burst_race(const REINDEER reindeers[], const size_t reindeer_count);
unsigned int points_race(const REINDEER reindeers[], const size_t reindeer_count);

int main (int argc, char**argv) {
    if (argc<2) {
        printf("Usage: %s [input_file_path/]input_file\n", basename(argv[0]));
        return 1;
    }

    FILE *in_file = fopen(argv[1], "r");
    char buffer[BUFFER_SIZE] = {0};
    size_t reindeer_count = 0;
    REINDEER reindeers[REINDEER_BUFFER_SIZE];
    if (in_file == NULL) {
        fprintf(stderr, "Unable to open file %s.\n", argv[1]);
        perror("Error message opening file file");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), in_file)) {
        chomp(buffer);
        sscanf(buffer, "%s can fly %u km/s for %u seconds, but then must rest for %u seconds.",
                        &reindeers[reindeer_count].name[0], &(reindeers[reindeer_count].flight_speed), &(reindeers[reindeer_count].flight_duration), &(reindeers[reindeer_count].rest_time));
        reindeer_count++;
    }
    fclose(in_file);

    printf("Distance by winning reineer in a burst race: %u.\n", burst_race(reindeers, reindeer_count));
    printf("Points of winning reineer in a points race: %u.\n", points_race(reindeers, reindeer_count));

    return 0;
}

char* chomp(char *s) {
    size_t s_len = strlen(s);
    while (s_len > 0 && s[--s_len] == '\n') {
        s[s_len] = '\0';
    }
    return s;
}

unsigned int burst_race(const REINDEER reindeers[], const size_t reindeer_count) {
    unsigned int furthest_distance = 0;
    for (size_t i=0 ; i<reindeer_count ; i++) {
        unsigned int current_race_time = 0, current_distance = 0;
        while (current_race_time < RACE_TIME) {
            if (current_race_time+reindeers[i].flight_duration > RACE_TIME) {
                unsigned int short_flight_time = RACE_TIME-current_race_time;
                current_distance += reindeers[i].flight_speed*short_flight_time;
            } else {
                current_distance += reindeers[i].flight_speed*reindeers[i].flight_duration;
            }
            current_race_time += reindeers[i].flight_duration + reindeers[i].rest_time;
        }
        if (current_distance > furthest_distance) {
            furthest_distance = current_distance;
        }
    }
    return furthest_distance;
}

unsigned int points_race(const REINDEER reindeers[], const size_t reindeer_count) {
    unsigned int most_points = 0;
    // 0 = current reindeer action, 1 = current action time remaining, 2 = current reindeer distance, 3 = current reindeer points
    unsigned int race_stats[REINDEER_BUFFER_SIZE][4];
    // Initialise race stats
    for (size_t i=0 ; i<reindeer_count ; i++) {
        race_stats[i][0] = REINDEER_FLYING;
        race_stats[i][1] = reindeers[i].flight_duration;
        race_stats[i][2] = 0;
        race_stats[i][3] = 0;
    }
    // RACE !!
    for (unsigned int curr_race_time = 0 ; curr_race_time < RACE_TIME ; curr_race_time++) {
        // Reindeer action
        for (size_t i=0 ; i<reindeer_count ; i++) {
            if (race_stats[i][1] == 0) {
                if (race_stats[i][0] == REINDEER_FLYING) {
                    race_stats[i][0] = REINDEER_RESTING;
                    race_stats[i][1] = reindeers[i].rest_time;
                } else {
                    race_stats[i][0] = REINDEER_FLYING;
                    race_stats[i][1] = reindeers[i].flight_duration;
                }
            } 
            if (race_stats[i][0] == REINDEER_FLYING) {
                race_stats[i][2] += reindeers[i].flight_speed;
            }
            race_stats[i][1]--;
        }
        // Find farthest reindeer
        unsigned int furthest_distance = race_stats[0][2];
        for (size_t i=1 ; i<reindeer_count ; i++) {
            if (race_stats[i][2] > furthest_distance) {
                furthest_distance = race_stats[i][2];
            }
        }
        // Add points
        for (size_t i=0 ; i<reindeer_count ; i++) {
            if (race_stats[i][2] == furthest_distance) {
                race_stats[i][3]++;
            }
        }
    }
    // Find winner
    for (size_t i=0 ; i<reindeer_count ; i++) {
        if (race_stats[i][3] > most_points) {
            most_points = race_stats[i][3];
        }
    }
    return most_points;
}
