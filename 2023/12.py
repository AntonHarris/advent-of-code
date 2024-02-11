#!/usr/bin/python3

import sys
import re

def check_conditions(row_springs, row_conditions) -> bool:
    springs = re.findall(r'#+', row_springs)
    conditions = re.split(r',', row_condition_record)
    if len(springs) != len(conditions):
        return False
    for check in zip(springs, conditions):
        if len(check[0]) != int(check[1]):
            return False
    return True

def try_possible_arrangements(line) -> int:
    row_springs, row_conditions = line.split(" ")
    count_unknown = row_springs.count('?')
    sum_damaged = sum([int(group) for group in row_conditions.split(",")])
    return 1

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 12.py file_to_use")
        exit(1)

    with open(sys.argv[1], 'r') as infile:
        data = [line.strip() for line in infile.readlines()]

    # sum_poss_arrangements = 0
    # for line in data:
    #     sum_poss_arrangements += try_possible_arrangements(line)
    # print("Sum of possible arrangements: ", sum_poss_arrangements)
    print("Sum of possible arrangements: ", sum([try_possible_arrangements(line) for line in data]))
