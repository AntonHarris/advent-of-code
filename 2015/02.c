#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char * chomp(char *p) {
    while (p[strlen(p)-1] == '\n') {
        p[strlen(p)-1] = '\0';
    }
    return p;
}

unsigned int smallest_dimension (unsigned int dim_1, unsigned int dim_2, unsigned int dim_3) {
    if (dim_1<=dim_2 && dim_1<=dim_3) return dim_1;
    if (dim_2<=dim_1 && dim_2<=dim_3) return dim_2;
    return dim_3;
}

unsigned int smallest_perimeter (unsigned int l, unsigned int w, unsigned int h) {
    unsigned int array[2];
    array[0] = l;
    if (w<array[0]) {
        array[1] = array[0];
        array[0] = w;
    } else {
        array[1] = w;
    }
    if (h<array[0]) {
        array[1] = array[0];
        array[0] = h;
    } else {
        if (h<array[1]) {
            array[1] = h;
        }
    }
    return 2*array[0] + 2*array[1];
}

unsigned int present_volume (unsigned int l, unsigned int w, unsigned int h) {
    return l*w*h;
}

unsigned int wrapping_paper_required (unsigned int l, unsigned int w, unsigned int h) {
    unsigned int dim_1 = l*w, dim_2 = w*h, dim_3 = h*l;
    return 2*dim_1 + 2*dim_2 + 2*dim_3 + smallest_dimension(dim_1, dim_2, dim_3);
}

int main (int argc, char**argv) {
    if (argc<2) {
        char *lastslash = strrchr(argv[0], '/');
        if (lastslash == NULL) { lastslash = argv[0]; }
        printf("Usage: %s [input_file_path/]input_file\n", lastslash+1);
        return 1;
    }

    char buffer[100];
    unsigned int total_wrap_required = 0;
    unsigned int total_ribbon_required = 0;
    FILE *in_file = fopen(argv[1], "r");
    if (in_file == NULL) {
        perror("Unable to open file");
        return 1;
    }
    while (fgets(buffer, sizeof(buffer), in_file) != NULL) {
        chomp(buffer);
        unsigned int l=0, w=0, h=0;
        sscanf(buffer, "%ux%ux%u", &l, &w, &h);
        total_wrap_required += wrapping_paper_required(l, w, h);
        total_ribbon_required += smallest_perimeter(l, w, h) + present_volume(l, w, h);
    }
    fclose(in_file);

    printf("Total sq ft wrapping paper required: %u.\n", total_wrap_required);
    printf("Total length ribbon required: %u.\n", total_ribbon_required);


    return 0;
}
