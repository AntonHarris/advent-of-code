#!/usr/bin/python3

import sys

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 15.py file_to_use")
        exit(1)

    with open(sys.argv[1], 'r') as infile:
        data = [line.strip() for line in infile.readlines()]
    hashes = data[0].split(',')

    sum_hashes = 0
    for new_hash in hashes:
        curr_hash = 0
        for char in new_hash:
            curr_hash += ord(char)
            curr_hash *= 17
            curr_hash %= 256
        sum_hashes += curr_hash
    print(f"Sum hashes = {sum_hashes}")
