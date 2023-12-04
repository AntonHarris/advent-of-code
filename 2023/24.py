#!/usr/bin/python3

import sys

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 24.py file_to_use")
        exit(1)

    with open(sys.argv[1], 'r') as infile:
        data = [line.strip() for line in infile.readlines()]
