#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <libgen.h>

#define BUFFER_SIZE 50
#define LABEL_SIZE 10

typedef enum {
    i_assign = 0,
    i_and,
    i_or,
    i_lshift,
    i_rshift,
    i_not,
} instruction_types;

typedef struct {
    char target_label[LABEL_SIZE];
    char left_label[LABEL_SIZE];
    instruction_types i_type;
    char right_label[LABEL_SIZE];
    bool val_available;
    unsigned short val;
} instruction_t;

typedef struct instruction_list_t {
    instruction_t instruction;
    struct instruction_list_t *next;
} instruction_list_t;

char* chomp (char *p);
size_t count_spaces (const char *s);
instruction_list_t* add_new_instruction (instruction_list_t *l, const char *s);
instruction_t* get_target_instruction (instruction_list_t *l, const char *s);
void override_instruction (instruction_list_t *l, const char *s, instruction_types it, const char *ll, const char *rl);
void clear_values (instruction_list_t *l);
void empty_and_free_instruction_list (instruction_list_t *l);
unsigned short get_value_of_target (const char *t, instruction_list_t *il);

int main (int argc, char **argv) {
    if (argc<2) {
        printf("Usage: %s [input_file_path/]input_file\n", basename(argv[0]));
        return 1;
    }

    FILE *in_file = fopen(argv[1], "r");
    char buffer[BUFFER_SIZE] = {0};
    instruction_list_t *instructions = NULL;
    if (in_file == NULL) {
        fprintf(stderr, "Unable to open file %s.\n", argv[1]);
        perror("Error message opening file file");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), in_file)) {
        chomp(buffer);
        instructions = add_new_instruction(instructions, buffer);
    }
    fclose(in_file);

    char *target = "a";
    unsigned short target_value = get_value_of_target(target, instructions);
    printf("Part 1: Value of wire %s = %u.\n", target, target_value);

    clear_values(instructions);
    sprintf(buffer, "%u", target_value);
    override_instruction(instructions, "b", i_assign, "", buffer);
    target_value = get_value_of_target(target, instructions);
    printf("Part 2: Value of wire %s after override of wire b = %u.\n", target, target_value);

    empty_and_free_instruction_list(instructions);

    return 0;
}

char* chomp(char *s) {
    size_t s_len = strlen(s);
    while (s_len > 0 && s[--s_len] == '\n') {
        s[s_len] = '\0';
    }
    return s;
}

size_t count_spaces (const char *s) {
    size_t count = 0;
    while (*s) {
        if (*s == ' ') {
            count++;
        }
        s++;
    }
    return count;
}

instruction_list_t* add_new_instruction (instruction_list_t *l, const char *s) {
    instruction_list_t *new_instruction = (instruction_list_t *) calloc (1, sizeof(instruction_list_t));
    new_instruction->next = l;
    new_instruction->instruction.val_available = false; // should be default value

    char *ptr_target = strrchr(s, ' ');
    ptr_target++;
    strcpy(new_instruction->instruction.target_label, ptr_target);

    if (count_spaces(s) == 2) {
        new_instruction->instruction.i_type = i_assign;
        sscanf(s, "%s", new_instruction->instruction.right_label);
    } else if (strncmp(s, "NOT", strlen("NOT")) == 0) {
        new_instruction->instruction.i_type = i_not; // alternatively: if (count_spaces(s) == 3) {
        char *ptr_s = strchr(s, ' ');
        ptr_s++;
        sscanf(ptr_s, "%s", new_instruction->instruction.right_label);
    } else {
        char i_type_buffer[BUFFER_SIZE];
        sscanf(s, "%s %s %s", new_instruction->instruction.left_label, i_type_buffer, new_instruction->instruction.right_label);
        if (strcmp(i_type_buffer, "OR") == 0) {
            new_instruction->instruction.i_type = i_or;
        } else if (strcmp(i_type_buffer, "AND") == 0) {
            new_instruction->instruction.i_type = i_and;
        } else if (strcmp(i_type_buffer, "LSHIFT") == 0) {
            new_instruction->instruction.i_type = i_lshift;
        } else /* if (strcmp(i_type_buffer, "RSHIFT") == 0) */ {
            new_instruction->instruction.i_type = i_rshift;
        }
    }

    return new_instruction;
}

instruction_t* get_target_instruction (instruction_list_t *l, const char *s) {
    while (l) {
        if (strcmp(l->instruction.target_label, s) == 0) {
            return &(l->instruction);
        }
        l = l->next;
    }
    return NULL;
}

void override_instruction (instruction_list_t *l, const char *s, instruction_types it, const char *ll, const char *rl) {
    instruction_t *instr = get_target_instruction(l, s);
    instr->i_type = it;
    strcpy(instr->left_label, ll);
    strcpy(instr->right_label, rl);
}

void clear_values (instruction_list_t *l) {
    while (l) {
        l->instruction.val_available = false;
        l = l->next;
    }
}

void empty_and_free_instruction_list (instruction_list_t *l) {
    while (l) {
        instruction_list_t *tmp_l = l;
        l = l->next;
        free(tmp_l);
    }
}

unsigned short get_value_of_target (const char *t, instruction_list_t *il) {
    unsigned int res_val = 0;
    instruction_t *instr = get_target_instruction(il, t);
    if (instr) {
        if (instr->val_available) {
            return instr->val;
        }

        unsigned short left_val = 0, right_val = 0;

        if (instr->i_type != i_not && instr->i_type != i_assign) {
            if (isdigit(instr->left_label[0])) {
                left_val = (unsigned short) strtol(instr->left_label, NULL, 10);
            } else {
                left_val = get_value_of_target(instr->left_label, il);
            }
        }
        if (isdigit(instr->right_label[0])) {
            right_val = (unsigned short) strtol(instr->right_label, NULL, 10);
        } else {
            right_val = get_value_of_target(instr->right_label, il);
        }

        switch(instr->i_type) {
            case i_or : res_val = (left_val | right_val);
                break;
            case i_and : res_val = (left_val & right_val);
                break;
            case i_lshift : res_val = (left_val << right_val);
                break;
            case i_rshift : res_val = (left_val >> right_val);
                break;
            case i_not : res_val = (right_val^0xFFFF);
                break;
            case i_assign : res_val = right_val;
                break;
        }

        instr->val_available = true;
        instr->val = res_val;
    }

    return res_val;
}