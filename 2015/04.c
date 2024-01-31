#include <stdio.h>
#include <string.h>
#include <md5.h>
#include <limits.h>
#include <stdbool.h>
#include <libgen.h>

int get_md5_hash_starts_with_x_zeroes(const char* input, int start, int num_zeroes);

int main(int argc, char **argv) {
    char input_string[20] = {0};
    if (argc<2) {
        printf("Usage: %s input_string\nNo input string provided, using default string, yzbqklnj.\n\n", basename(argv[0]));
        strcpy(input_string, "yzbqklnj");
    } else {
        strcpy(input_string, argv[1]);
    }

    int part_1_nbr = get_md5_hash_starts_with_x_zeroes(input_string, 0, 5);
    printf("Hash for %s%d starts with 5 0s.\n", input_string, part_1_nbr);
    int part_2_nbr = get_md5_hash_starts_with_x_zeroes(input_string, part_1_nbr+1, 6);
    printf("Hash for %s%d starts with 6 0s.\n", input_string, part_2_nbr);

    return 0;
}

int get_md5_hash_starts_with_x_zeroes(const char* input, int start, int num_zeroes) {
    bool all_zeroes = true;
    char buffer[32];
    unsigned char digest[16];
    struct MD5Context context;
 
    for (int i=start ; i<INT_MAX ; i++) {
        all_zeroes = true;
        sprintf(buffer, "%s%d", input, i);
        MD5Init(&context);
        MD5Update(&context, (const uint8_t *)buffer, strlen(buffer));
        MD5Final(digest, &context);
        digest[num_zeroes/2] &= '\xF0';
        for (int j=0 ; j<(num_zeroes+1)/2 ; j++) {
            if (digest[j] != '\0') {
                all_zeroes = false;
            }
        }
        if (all_zeroes) {
            return i;
        }
    }
 
    return 0;
}
