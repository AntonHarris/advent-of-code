#!/usr/bin/python3

import sys
import re

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 19.py file_to_use")
        exit(1)

    with open(sys.argv[1], 'r') as infile:
        data = [line.strip() for line in infile.readlines()]
    
    conditions = {}
    condition_regex = r'^([a-z]+){([^}]+)}$'
    idx = 0
    for line in data:
        if line=="":
            break
        else:
            idx += 1
        matches = re.match(condition_regex, line)
        conditions.update({matches[1]: matches[2].split(r',')})
    print(conditions)

    idx += 1
    sum_ratings = 0
    # loop on parts
    for line in data[idx:]:
        pass
        # print(line)
    print(f"Sum parts ratings: {sum_ratings}")
