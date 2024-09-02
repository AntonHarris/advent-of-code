#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <libgen.h>

#define BUFFER_SIZE 100
#define CITY_SIZE 32
#define MAX_NODE_EDGES 10

unsigned int count_nodes = 0;

typedef struct node_t {
    char city[CITY_SIZE];
    unsigned int index;
    struct node_t *next;
} NODE_T;

char* chomp (char *p);
unsigned int get_city_index (NODE_T **nodes, char *city);
NODE_T* find_city (NODE_T *nodes, char *city);
NODE_T* new_city (char *city);
void free_nodes (NODE_T **nodes);

// debugging functions
void list_cities (NODE_T *nodes);
void show_edges (unsigned int edges[MAX_NODE_EDGES][MAX_NODE_EDGES]);

int main (int argc, char**argv) {
    if (argc<2) {
        printf("Usage: %s [input_file_path/]input_file\n", basename(argv[0]));
        return 1;
    }

    char buffer[BUFFER_SIZE] = {0};
    unsigned int edges[MAX_NODE_EDGES][MAX_NODE_EDGES] = { [0 ... MAX_NODE_EDGES-1] = { [0 ... MAX_NODE_EDGES-1] = 0 }};
    NODE_T *nodes = NULL;
    FILE *in_file = fopen(argv[1], "r");
    if (in_file == NULL) {
        fprintf(stderr, "Unable to open file %s.\n", argv[1]);
        perror("Error message opening file file");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), in_file)) {
        char src_city[CITY_SIZE] = {0};
        char dst_city[CITY_SIZE] = {0};
        unsigned int distance = 0, src_city_idx = 0, dst_city_idx = 0;
        // Dublin to Belfast = 141
        chomp(buffer);
        sscanf(buffer, "%s to %s = %u", src_city, dst_city, &distance);
        printf("Distance between %s and %s is %u.\n", src_city, dst_city, distance);
        src_city_idx = get_city_index(&nodes, src_city);
        dst_city_idx = get_city_index(&nodes, dst_city);
        edges[src_city_idx][dst_city_idx] = edges[dst_city_idx][src_city_idx] = distance;
    }
    // list_cities(nodes);
    // show_edges(edges);
    fclose(in_file);
    free_nodes(&nodes);

    return 0;
}

char* chomp(char *s) {
    size_t s_len = strlen(s);
    while (s_len > 0 && s[--s_len] == '\n') {
        s[s_len] = '\0';
    }
    return s;
}

unsigned int get_city_index (NODE_T **nodes, char *city) {
    NODE_T *tmp_node = *nodes;

    if (tmp_node != NULL) {
        tmp_node = find_city(*nodes, city);
    }
    if (!tmp_node) {
        tmp_node = new_city(city);
        count_nodes++;
        if (*nodes == NULL) {
            *nodes = tmp_node;
        } else {
            NODE_T *last_node = *nodes;
            while (last_node->next) {
                last_node = last_node->next;
            }
            tmp_node->index = (last_node->index)+1;
            last_node->next = tmp_node;
        }
    }

    return tmp_node->index;
}

NODE_T *find_city (NODE_T *nodes, char *city) {
    while (nodes) {
        if (strcmp(nodes->city, city) == 0) {
            return nodes;
        }
        nodes = nodes->next;
    }
    return NULL;
}

NODE_T* new_city (char *city) {
    NODE_T *tmp_node = (NODE_T *) calloc (1, sizeof(NODE_T));
    strcpy(tmp_node->city, city);
    return tmp_node;
}

void free_nodes (NODE_T **nodes) {
    NODE_T *tmp_node;

    while (*nodes) {
        tmp_node = *nodes;
        *nodes = tmp_node->next;
        free(tmp_node);
    }
}

void list_cities (NODE_T *nodes) {
    while (nodes) {
        printf("Node index %u: %s\n", nodes->index, nodes->city);
        nodes = nodes->next;
    }
}

void show_edges (unsigned int edges[MAX_NODE_EDGES][MAX_NODE_EDGES]) {
    for (unsigned int i = 0 ; i<count_nodes ; i++) {
        for (unsigned int j = 0 ; j<count_nodes ; j++) {
            printf("%4u", edges[i][j]);
        }
        printf("\n");
    }
}
