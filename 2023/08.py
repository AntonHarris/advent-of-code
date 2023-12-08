#!/usr/bin/python3

import sys
import re

def count_steps(starting_node, directions, nodes) -> int:
    count_steps = 0
    direction_idx = 0
    current_node = starting_node
    while current_node != "ZZZ":
        current_node = nodes[current_node][directions[direction_idx]]
        count_steps += 1
        direction_idx += 1
        direction_idx = direction_idx%(len(directions))
    return count_steps

def count_steps_parallel(starting_nodes, directions, nodes):
    count_steps = 0
    current_nodes = starting_nodes.copy()
    # this is where the loop should be
    return count_steps

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

    print("Number of steps for ['AAA']: ", count_steps("AAA", directions, nodes))

    starting_nodes = list(filter(lambda tmp_node: tmp_node.endswith('A'), nodes.keys()))
    print("starting_nodes: ", starting_nodes)
    print("Number of steps for // endswith('A'): ", count_steps_parallel(starting_nodes, directions, nodes))

