#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <libgen.h>

#define BUFFER_SIZE 100
#define LABEL_SIZE 10

typedef enum instruction_types {
    i_assign = 0,
    i_and,
    i_or,
    i_lshift,
    i_rshift,
    i_not,
} INSTRUCTION_TYPES;

typedef struct instruction {
    char wire1[LABEL_SIZE];
    char wire2[LABEL_SIZE];
    unsigned short val;
    INSTRUCTION_TYPES instruc;
    char target_wire[LABEL_SIZE];
    struct instruction *next;
} INSTRUCTION;

typedef struct wire {
    char label[LABEL_SIZE];
    unsigned short val;
    struct wire *next;
} WIRE;

char* chomp(char *p);
void add_new_instruction (const char *s, INSTRUCTION **p_p_head);
void add_new_wire(const char *s_label, unsigned short val, WIRE **p_p_head);
size_t count_instructions (INSTRUCTION *p_head);
size_t count_wires (WIRE *p_head);
void wire_inits (INSTRUCTION **p_p_ihead, WIRE **p_p_whead);
void apply_instructions (INSTRUCTION **p_p_ihead, WIRE **p_p_whead);
WIRE * find_wire (const char *s, WIRE *p_head);
unsigned short get_value_of_wire (const char *s, WIRE *p_head);

int main (int argc, char **argv) {
    if (argc<2) {
        printf("Usage: %s [input_file_path/]input_file\n", basename(argv[0]));
        return 1;
    }

    FILE *in_file = fopen(argv[1], "r");
    char buffer[BUFFER_SIZE];
    INSTRUCTION *instructions_head = NULL;
    WIRE *wires_head = NULL;
    if (in_file == NULL) {
        fprintf(stderr, "Unable to open file %s.\n", argv[1]);
        perror("Error message opening file file");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), in_file)) {
        chomp(buffer);
        add_new_instruction(buffer, &instructions_head);
    }
    fclose(in_file);

    // printf("Size of instruction set: %lu.\n", count_instructions(instructions_head));
    // printf("Size of wire set: %lu.\n", count_wires(wires_head));
    wire_inits(&instructions_head, &wires_head);
    // printf("Size of instruction set after wire_inits: %lu.\n", count_instructions(instructions_head));
    // printf("Size of wire set after wire_inits: %lu.\n", count_wires(wires_head));
    apply_instructions(&instructions_head, &wires_head);
    // printf("Size of instruction set after apply_instructions: %lu.\n", count_instructions(instructions_head));
    // printf("Size of wire set after apply_instructions: %lu.\n", count_wires(wires_head));
    printf("Value of wire x = %d.\n", get_value_of_wire("x", wires_head));

    return 0;
}

char* chomp(char *s) {
    size_t s_len = strlen(s);
    while (s_len > 0 && s[--s_len] == '\n') {
        s[s_len] = '\0';
    }
    return s;
}

void add_new_instruction (const char *s, INSTRUCTION **p_p_head) {
    INSTRUCTION *new_inst = (INSTRUCTION *) malloc (sizeof(INSTRUCTION));
    new_inst->next = *p_p_head;
    if (s[0] >= '0' && s[0] <= '9') {
        sscanf(s, "%hu -> %s", &(new_inst->val), new_inst->target_wire);
        new_inst->instruc = i_assign;
    } else if (strncmp(s, "NOT", strlen("NOT")) == 0) {
        new_inst->instruc = i_not;
        sscanf(s, "NOT %s -> %s", new_inst->wire1, new_inst->target_wire);
    } else {
        char buffer[10] = {0};
        sscanf(s, "%s %s %s -> %s", new_inst->wire1, buffer, new_inst->wire2, new_inst->target_wire);
        if (strncmp(buffer, "OR", strlen("OR")) == 0) {
            new_inst->instruc = i_or;
        } else if (strncmp(buffer, "AND", strlen("AND")) == 0) {
            new_inst->instruc = i_and;
        } else if (strncmp(buffer, "LSHIFT", strlen("LSHIFT")) == 0) {
            new_inst->instruc = i_lshift;
        } else { // only RSHIFT left
            new_inst->instruc = i_rshift;
        }
    }
    *p_p_head = new_inst;
}

void add_new_wire(const char *s_label, unsigned short val, WIRE **p_p_head) {
    WIRE *p_wire = (WIRE *) malloc (sizeof(WIRE));
    strcpy(p_wire->label, s_label);
    p_wire->val = val;
    p_wire->next = *p_p_head;
    *p_p_head = p_wire;
}

size_t count_instructions (INSTRUCTION *p_head) {
    size_t count = 0;
    while (p_head) {
        count++;
        p_head = p_head->next;
    }
    return count;
}

size_t count_wires(WIRE *p_head) {
    size_t count = 0;
    while (p_head) {
        count++;
        p_head = p_head->next;
    }
    return count;
}

void wire_inits (INSTRUCTION **p_p_ihead, WIRE **p_p_whead) {
    INSTRUCTION *p_instruct = *p_p_ihead, *p_prev_instruct = NULL;
    while (p_instruct) {
        if (p_instruct->instruc == i_assign) {
            add_new_wire(p_instruct->target_wire, p_instruct->val, p_p_whead);

            INSTRUCTION *p_tmp_instruct = p_instruct;
            p_instruct = p_instruct->next;
            if (p_prev_instruct) {
                p_prev_instruct->next = p_tmp_instruct->next;
            } else {
                *p_p_ihead = p_instruct;
            }
            free(p_tmp_instruct);
        }
        else {
            p_prev_instruct = p_instruct;
            p_instruct = p_instruct->next;
        }
    }
}

void apply_instructions (INSTRUCTION **p_p_ihead, WIRE **p_p_whead) {
    ;
}

WIRE * find_wire (const char *s, WIRE *p_head) {
    while (p_head) {
        if (strcmp(s, p_head->label) == 0) {
            return p_head;
        }
    }
    return NULL;
}

unsigned short get_value_of_wire (const char *s, WIRE *p_head) {
    WIRE *tmp_wire = find_wire(s, p_head);
    return tmp_wire ? tmp_wire->val : 0;
}