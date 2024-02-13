#!/usr/bin/python3

import sys
import re

def check_conditions(row_springs, row_conditions) -> bool:
    springs = re.findall(r'#+', row_springs)
    conditions = re.split(r',', row_conditions)
    if len(springs) != len(conditions):
        return False
    for check in zip(springs, conditions):
        if len(check[0]) != int(check[1]):
            return False
    return True

def try_possible_arrangements(line) -> int:
    row_springs, row_conditions = line.split(" ")
    row_springs_arr = list(row_springs)
    count_unknown = row_springs.count('?')
    sum_damaged = sum([int(group) for group in row_conditions.split(",")])

    # TODO: improve this algo (which takes about 21 seconds on my computer)
    count_possible_arrangements = 0
    for i in range(2**count_unknown):
        row_springs_arr = list(row_springs)
        tmp_i = i
        for j, c in enumerate(row_springs_arr):
            if c=='?':
                row_springs_arr[j] = "#" if tmp_i%2 == 1 else "."
                tmp_i //= 2
        tmp_str = ""
        for c in row_springs_arr:
            tmp_str += c
        count_possible_arrangements += 1 if check_conditions(tmp_str, row_conditions) else 0

    return count_possible_arrangements

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 12.py file_to_use")
        exit(1)

    with open(sys.argv[1], 'r') as infile:
        data = [line.strip() for line in infile.readlines()]

    print("Sum of possible arrangements: ", sum([try_possible_arrangements(line) for line in data]))
