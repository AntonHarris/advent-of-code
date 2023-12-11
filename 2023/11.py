#!/usr/bin/python3

import sys

def is_row_empty(line) -> bool:
    if len(set(line))==1 and line[0]==".":
        return True
    return False

def is_col_empty(col, data) -> bool:
    pass

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 11.py file_to_use")
        exit(1)

    with open(sys.argv[1], 'r') as infile:
        data = [line.strip() for line in infile.readlines()]
    
    for line in data:
        print("line: ", line, " - is it empty? ", is_row_empty(line))
