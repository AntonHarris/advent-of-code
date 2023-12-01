#!/usr/bin/python3

import sys

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 22.py file_to_use")
        exit(1)

    infile = open(sys.argv[1], "r")
    data = infile.readlines()
    infile.close()
