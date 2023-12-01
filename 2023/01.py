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

    digits = {
        "one":1,    "1":1,
        "two":2,    "2":2,
        "three":3,  "3":3,
        "four":4,   "4":4,
        "five":5,   "5":5,
        "six":6,    "6":6,
        "seven":7,  "7":7,
        "eight":8,  "8":8,
        "nine":9,   "9":9
    }

    sum_part_one = 0
    for line in data:
        line = line.strip()
        matches = re.findall("\d", line)
        sum_part_one = sum_part_one + digits[matches[0]]*10 + digits[matches[-1]]
    print("Part 1 sum: ", sum_part_one)
    
    sum_part_two = 0
    for line in data:
        line = line.strip()
        matches = re.findall("(?=(\d|one|two|three|four|five|six|seven|eight|nine))", line)
        sum_part_two = sum_part_two + digits[matches[0]]*10 + digits[matches[-1]]
    print("Part 2 sum: ", sum_part_two)
