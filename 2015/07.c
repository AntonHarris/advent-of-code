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

typedef struct wire_t {
    char label[LABEL_SIZE];
    unsigned short val;
} WIRE_T;

typedef struct wire_list_t {
    WIRE_T wire;
    struct wire_list_t *next;
} WIRE_LIST_T;

char* chomp(char *p);
void handle_instruction (FILE *in_file, WIRE_LIST_T **head);
void add_wire_to_list (const char *s, unsigned short val, WIRE_LIST_T **head);
WIRE_LIST_T* find_wire (const char *s, WIRE_LIST_T *head);
unsigned short get_wire_val (const char *s, WIRE_LIST_T *head);

int main (int argc, char **argv) {
    if (argc<2) {
        return 1;
    }

    FILE *in_file = fopen(argv[1], "r");
    WIRE_LIST_T *head = NULL;
    if (in_file == NULL) {
        fprintf(stderr, "Unable to open file %s.\n", argv[1]);
        perror("Error message opening file file");
        return 1;
    }
    while (!feof(in_file)) {
        handle_instruction(in_file, &head);
    }
    fclose(in_file);

    WIRE_LIST_T *tmp_ptr_head = head;
    while (tmp_ptr_head) {
        tmp_ptr_head = tmp_ptr_head->next;
    }

    printf("Value of wire a = %u.\n", get_wire_val("a", head));

    return 0;
}

char* chomp(char *s) {
    size_t s_len = strlen(s);
    while (s_len > 0 && s[--s_len] == '\n') {
        s[s_len] = '\0';
    }
    return s;
}

void handle_instruction (FILE *in_file, WIRE_LIST_T **head) {
    char buffer[BUFFER_SIZE] = {0}, *ptr_buffer = &buffer[0];
    if (fgets(buffer, sizeof(buffer), in_file)) {
        chomp(buffer);
        unsigned short val_1 = 0, val_2 = 0;
        INSTRUCTION_TYPES inst_type;
        if (isdigit(*ptr_buffer)) {
            inst_type = i_assign;
            sscanf(ptr_buffer, "%hu", &val_1);
        } else {
            if (strncmp(buffer, "NOT", 3) == 0) {
                inst_type = i_not;
            } else {
                char tmp_label[LABEL_SIZE];
                sscanf(buffer, "%s", tmp_label);
                WIRE_LIST_T *tmp_wl = NULL;
                while ((tmp_wl = find_wire(tmp_label, *head)) == NULL) {
                    handle_instruction(in_file, head);
                }
                val_1 = get_wire_val(tmp_label, tmp_wl);
            }
        }

        if (inst_type != i_not) {
            ptr_buffer = strchr(ptr_buffer, ' ');
            ptr_buffer++;
        }

        switch(*ptr_buffer) {
            case '-': // assignation
                ptr_buffer = strchr(ptr_buffer, ' ');
                ptr_buffer++;
                add_wire_to_list(ptr_buffer, val_1, head);
                printf("Assigned value of %d to label %s.\n", val_1, ptr_buffer);
                return;
            case 'A': // AND
                inst_type = i_and;
                break;
            case 'O': // OR
                inst_type = i_or;
                break;
            case 'L': // LSHIFT
                inst_type = i_lshift;
                break;
            case 'R': // RSHIFT
                inst_type = i_rshift;
                break;
            default: ; // NOT, do nothing
        }

        ptr_buffer = strchr(ptr_buffer, ' ');
        ptr_buffer++;

        if (isdigit(*ptr_buffer)) {
            sscanf(ptr_buffer, "%hu", &val_2);
        } else {
            char tmp_label[LABEL_SIZE];
            sscanf(ptr_buffer, "%s", tmp_label);
            WIRE_LIST_T *tmp_wl = NULL;
            while ((tmp_wl = find_wire(tmp_label, *head)) == NULL) {
                handle_instruction(in_file, head);
            }
            val_2 = get_wire_val(tmp_label, tmp_wl);
        }

        ptr_buffer++;
        ptr_buffer = strchr(ptr_buffer, ' ');
        ptr_buffer++;
        ptr_buffer = strchr(ptr_buffer, ' ');
        ptr_buffer++;

        switch(inst_type) {
            case i_and:
                add_wire_to_list(ptr_buffer, val_1 & val_2, head);
                break;
            case i_or:
                add_wire_to_list(ptr_buffer, val_1 | val_2, head);
                break;
            case i_lshift:
                add_wire_to_list(ptr_buffer, val_1 << val_2, head);
                break;
            case i_rshift:
                add_wire_to_list(ptr_buffer, val_1 >> val_2, head);
                break;
            case i_not:
                add_wire_to_list(ptr_buffer, val_2^0xFFFF, head);
                break;
            case i_assign: // do nothing, case already handled earlier
                break;
        }
    }
}

void add_wire_to_list (const char *s, unsigned short val, WIRE_LIST_T **head) {
    WIRE_LIST_T *new_wl = (WIRE_LIST_T *) malloc (sizeof(WIRE_LIST_T));
    strcpy(new_wl->wire.label, s);
    new_wl->wire.val = val;
    new_wl->next = *head;
    *head = new_wl;
}

WIRE_LIST_T* find_wire (const char *s, WIRE_LIST_T *head) {
    while (head) {
        if (strcmp(head->wire.label, s) == 0) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}

unsigned short get_wire_val (const char *s, WIRE_LIST_T *head) {
    WIRE_LIST_T *wire = find_wire(s, head);
    return wire == NULL ? 0 : wire->wire.val;
}