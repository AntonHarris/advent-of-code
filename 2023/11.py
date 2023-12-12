#!/usr/bin/python3

import sys

def is_line_empty(line) -> bool:
    if len(set(line))==1 and line[0]==".":
        return True
    return False

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 11.py file_to_use")
        exit(1)

    with open(sys.argv[1], 'r') as infile:
        data = [line.strip() for line in infile.readlines()]
    sky_map = [[*line] for line in data]

    # Add extra rows for "empty" lines
    empty_rows = []
    for idx, line in enumerate(sky_map):
        if is_line_empty(line):
            empty_rows.insert(0, idx)
    for idx in empty_rows:
        sky_map.insert(idx, ['.'] * len(sky_map[0]))
    # Add extra columns for "empty" columns
    empty_cols = []
    for j in range(0, len(sky_map[0])):
        tmp_line = []
        for i in range(0, len(sky_map)):
            tmp_line.append(sky_map[i][j])
        if is_line_empty(tmp_line):
            empty_cols.insert(0, j)
    for idx in empty_cols:
        for i in range(0, len(sky_map)):
            sky_map[i].insert(idx, '.')
    # Create vector/array of different galaxies
    galaxies = []
    for row in range(0, len(sky_map)):
        for col in range(0, len(sky_map[row])):
            if sky_map[row][col] == '#':
                galaxies.append((row, col))
    # Calculate differences for all sets of galaxies
    sum_paths = 0
    for i in range(0, len(galaxies)-1):
        for j in range(i+1, len(galaxies)):
            sum_paths += ((galaxies[j][0] - galaxies[i][0]) + (abs(galaxies[j][1] - galaxies[i][1])))
    print("Sum paths between galaxies after expansion: ", sum_paths)
