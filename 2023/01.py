#!/usr/bin/python3

import sys
import re

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 01.py file_to_use")
        exit(1)

    infile = open(sys.argv[1], "r")
    data = infile.readlines()
    infile.close()

    sum_part_one = 0
    for line in data:
        line = line.strip()
        first = re.search("\d", line)
        # TODO : improve to get last digit in one step
        last = re.search("(\d)[^\d]*$", line)
        last = re.search("\d", last.group())
        sum_part_one = sum_part_one + int(first.group() + last.group())
    print("Part 1 sum: ", sum_part_one)
    
    # TODO : complete part 2
    for line in data:
        line = line.strip()