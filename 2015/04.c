#include <stdio.h>
#include <string.h>
#include <md5.h>
#include <limits.h>

int get_md5_hash_starts_with_x_zeroes(const char* input, int start, int num_zeroes);

int main() {
    const char* input = "yzbqklnj";

    int part_1_nbr = get_md5_hash_starts_with_x_zeroes(input, 0, 5);
    printf("Hash for %s%d starts with 5 0s.\n", input, part_1_nbr);
    int part_2_nbr = get_md5_hash_starts_with_x_zeroes(input, part_1_nbr+1, 6);
    printf("Hash for %s%d starts with 6 0s.\n", input, part_2_nbr);

    return 0;
}

int get_md5_hash_starts_with_x_zeroes(const char* input, int start, int num_zeroes) {
    char buffer[32];
    unsigned char digest[16];
    char digest_hex[33];
    struct MD5Context context;

    for (int i=start ; i<INT_MAX ; i++) {
        sprintf(buffer, "%s%d", input, i);
        MD5Init(&context);
        MD5Update(&context, (const uint8_t *)buffer, strlen(buffer));
        MD5Final(digest, &context);
        for (int n=0 ; n<16 ; n++) {
            sprintf(&digest_hex[n*2], "%02x", digest[n]);
        }
        digest_hex[32] = '\0';
        if (strncmp(digest_hex, "000000", num_zeroes) == 0) {
            return i;
        }
    }

    return 0;
}
