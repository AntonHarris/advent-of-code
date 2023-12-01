#!/usr/bin/python3

import re

infile = open("./input_files/01_data.dat", "r")
data = infile.readlines()
infile.close()

sum = 0
for line in data:
    line = line.strip()
    first = re.search("\d", line)
    last = re.search("(\d)[^\d]*$", line)
    last = re.search("\d", last.group())
    sum = sum + int(first.group() + last.group())

print("Part 1 sum: ")
print(sum)