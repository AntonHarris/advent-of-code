#!/usr/bin/python3

import re

# TODO : file passed as argument to script
infile = open("./input_files/01_data.dat", "r")
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

# TODO : print in one line
print("Part 1 sum: ")
print(sum_part_one)

# TODO : complete part 2
for line in data:
    line = line.strip()