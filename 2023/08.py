#!/usr/bin/python3

import sys
import re

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 08.py file_to_use")
        exit(1)

    with open(sys.argv[1], 'r') as infile:
        data = [line.strip() for line in infile.readlines()]

    directions = [*data[0]]
    nodes = {}
    for line in data[2:]:
        node = line.split(" = ")[0]
        children = re.sub(r'[(,)]', '', line.split(" = ")[1])
        nodes[node] = {"L": children.split(" ")[0], "R": children.split(" ")[1]}

    count_steps = 0
    current_node = "AAA"
    direction_idx = 0
    while current_node != "ZZZ":
        current_node = nodes[current_node][directions[direction_idx]]
        count_steps += 1
        direction_idx += 1
        direction_idx = direction_idx%(len(directions))
    print("Number of steps: ", count_steps)
