#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <libgen.h>

#define BUFFER_SIZE 100
#define NBR_SUES 500

typedef struct aunt_sue {
    int id;
    int children;
    int cats;
    int samoyeds;
    int pomeranians;
    int akitas;
    int vizslas;
    int goldfish;
    int trees;
    int cars;
    int perfumes;
} AUNT_SUE;

char* chomp(char *p);
int find_target_sue(AUNT_SUE target, AUNT_SUE sues[]);
int find_target_sue_retroencabulator(AUNT_SUE target, AUNT_SUE sues[]);

int main (int argc, char**argv) {
    if (argc<2) {
        printf("Usage: %s [input_file_path/]input_file\n", basename(argv[0]));
        return 1;
    }

    FILE *in_file = fopen(argv[1], "r");
    char buffer[BUFFER_SIZE] = {0};
    AUNT_SUE aunt_sues[NBR_SUES];
    if (in_file == NULL) {
        fprintf(stderr, "Unable to open file %s.\n", argv[1]);
        perror("Error message opening file file");
        return 1;
    }
    int idx = 0;
    while (fgets(buffer, sizeof(buffer), in_file)) {
        chomp(buffer);
        AUNT_SUE aunt_sue_tmp = {
            .id = 0,
            .children = -1,
            .cats = -1,
            .samoyeds = -1,
            .pomeranians = -1,
            .akitas = -1,
            .vizslas = -1,
            .goldfish = -1,
            .trees = -1,
            .cars = -1,
            .perfumes = -1
        };
        char *ptr_buffer = strchr(buffer, ' ')+1;
        aunt_sue_tmp.id = atoi(ptr_buffer);
        ptr_buffer = strchr(ptr_buffer, ' ')+1;
        // Sue 1: children: 1, cars: 8, vizslas: 7
        while (ptr_buffer) {
            char *ptr_count = strchr(ptr_buffer, ':')+2;
            int tmp_num = atoi(ptr_count);
            if (strncmp(ptr_buffer, "children", strlen("children")) == 0) {
                aunt_sue_tmp.children = tmp_num;
            } else if (strncmp(ptr_buffer, "children", strlen("children")) == 0) {
                aunt_sue_tmp.children = tmp_num;
            } else if (strncmp(ptr_buffer, "cats", strlen("cats")) == 0) {
                aunt_sue_tmp.cats = tmp_num;
            } else if (strncmp(ptr_buffer, "samoyeds", strlen("samoyeds")) == 0) {
                aunt_sue_tmp.samoyeds = tmp_num;
            } else if (strncmp(ptr_buffer, "pomeranians", strlen("pomeranians")) == 0) {
                aunt_sue_tmp.pomeranians = tmp_num;
            } else if (strncmp(ptr_buffer, "akitas", strlen("akitas")) == 0) {
                aunt_sue_tmp.akitas = tmp_num;
            } else if (strncmp(ptr_buffer, "vizslas", strlen("vizslas")) == 0) {
                aunt_sue_tmp.vizslas = tmp_num;
            } else if (strncmp(ptr_buffer, "goldfish", strlen("goldfish")) == 0) {
                aunt_sue_tmp.goldfish = tmp_num;
            } else if (strncmp(ptr_buffer, "trees", strlen("trees")) == 0) {
                aunt_sue_tmp.trees = tmp_num;
            } else if (strncmp(ptr_buffer, "cars", strlen("cars")) == 0) {
                aunt_sue_tmp.cars = tmp_num;
            } else if (strncmp(ptr_buffer, "perfumes", strlen("perfumes")) == 0) {
                aunt_sue_tmp.perfumes = tmp_num;
            }
            ptr_buffer = strpbrk(ptr_count, "abcdefghijklmnopqrstuvwxyz");
        }
        memcpy(&aunt_sues[idx], &aunt_sue_tmp, sizeof(AUNT_SUE));
        idx++;
    }
    fclose(in_file);

    AUNT_SUE target_sue = {
        .id = -1,
        .children = 3,
        .cats = 7,
        .samoyeds = 2,
        .pomeranians = 3,
        .akitas = 0,
        .vizslas = 0,
        .goldfish = 5,
        .trees = 3,
        .cars = 2,
        .perfumes = 1
    };
    printf("Aunt Sue who gave me the MFCSAM: %d.\n", find_target_sue(target_sue, aunt_sues));
    printf("Aunt Sue who gave me the MFCSAM after Retro Encabulator recallibration: %d.\n", find_target_sue_retroencabulator(target_sue, aunt_sues));

    return 0;
}

char* chomp(char *s) {
    size_t s_len = strlen(s);
    while (s_len > 0 && s[--s_len] == '\n') {
        s[s_len] = '\0';
    }
    return s;
}

int find_target_sue(AUNT_SUE target, AUNT_SUE sues[]) {
    for (int i=0 ; i<NBR_SUES ; i++) {
        if ((sues[i].children == -1 || sues[i].children == target.children) && 
            (sues[i].cats == -1 || sues[i].cats == target.cats) && 
            (sues[i].samoyeds == -1 || sues[i].samoyeds == target.samoyeds) && 
            (sues[i].pomeranians == -1 || sues[i].pomeranians == target.pomeranians) && 
            (sues[i].akitas == -1 || sues[i].akitas == target.akitas) && 
            (sues[i].vizslas == -1 || sues[i].vizslas == target.vizslas) && 
            (sues[i].goldfish == -1 || sues[i].goldfish == target.goldfish) && 
            (sues[i].trees == -1 || sues[i].trees == target.trees) && 
            (sues[i].cars == -1 || sues[i].cars == target.cars) && 
            (sues[i].perfumes == -1 || sues[i].perfumes == target.perfumes)) {
            return sues[i].id;
        }
    }

    return -1; // Not found, should not be reached
}

int find_target_sue_retroencabulator(AUNT_SUE target, AUNT_SUE sues[]) {
    for (int i=0 ; i<NBR_SUES ; i++) {
        if ((sues[i].children == -1 || sues[i].children == target.children) && 
            (sues[i].cats == -1 || sues[i].cats > target.cats) && 
            (sues[i].samoyeds == -1 || sues[i].samoyeds == target.samoyeds) && 
            (sues[i].pomeranians == -1 || sues[i].pomeranians < target.pomeranians) && 
            (sues[i].akitas == -1 || sues[i].akitas == target.akitas) && 
            (sues[i].vizslas == -1 || sues[i].vizslas == target.vizslas) && 
            (sues[i].goldfish == -1 || sues[i].goldfish < target.goldfish) && 
            (sues[i].trees == -1 || sues[i].trees > target.trees) && 
            (sues[i].cars == -1 || sues[i].cars == target.cars) && 
            (sues[i].perfumes == -1 || sues[i].perfumes == target.perfumes)) {
            return sues[i].id;
        }
    }

    return -1; // Not found, should not be reached
}
