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
        conditions.update({matches[1]: matches[2]})
#        conditions.update({matches[1]: matches[2].split(r',')})

    idx += 1
    sum_ratings = 0
    # loop on parts
    part_regex = r'^{([^}]+)}$'
    for line in data[idx:]:
        part = {}
        next_workflow = "in"
        matches = re.match(part_regex, line)
        line_arrayed = matches[1].split(r',')
        for i in line_arrayed:
            part.update({i.split(r'=')[0]: i.split(r'=')[1]})
        while True:
            if next_workflow=="A":
                sum_ratings += sum([int(x) for x in part.values()])
                break
            elif next_workflow=="R":
                break
            else:
                this_conditions = conditions[next_workflow].split(",")
                for this_condition in this_conditions:
                    if re.search(r':', this_condition) is not None:
                        matches = re.match(r'^([a-z])(.)(\d+):(.+)$', this_condition)
                        if eval(f"{part[matches[1]]}{matches[2]}{matches[3]}"):
                            next_workflow = matches[4]
                            break
                    else:
                        next_workflow = this_condition
                        break

    print(f"Sum parts ratings: {sum_ratings}")
