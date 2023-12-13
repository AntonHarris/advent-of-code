#!/usr/bin/python3

import sys

def is_line_empty(line) -> bool:
    if len(set(line))==1 and line[0]==".":
        return True
    return False

def how_many_empty_lines(start, end, list_empty) -> int:
    count_empty = 0
    for item in list_empty:
        if item>start and item<end:
            count_empty += 1
    return count_empty

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
            empty_rows.append(idx)
    # Add extra columns for "empty" columns
    empty_cols = []
    for j in range(0, len(sky_map[0])):
        tmp_line = []
        for i in range(0, len(sky_map)):
            tmp_line.append(sky_map[i][j])
        if is_line_empty(tmp_line):
            empty_cols.append(j)
    # Create vector/array of different galaxies
    galaxies = []
    for row in range(0, len(sky_map)):
        for col in range(0, len(sky_map[row])):
            if sky_map[row][col] == '#':
                galaxies.append((row, col))
    # Calculate differences for all sets of galaxies
    sum_paths_1 = 0
    sum_paths_2 = 0
    for i in range(0, len(galaxies)-1):
        for j in range(i+1, len(galaxies)):
            rows_diff = galaxies[j][0]-galaxies[i][0]
            empty_rows_diff = how_many_empty_lines(galaxies[i][0], galaxies[j][0], empty_rows)
            cols_diff = abs(galaxies[j][1] - galaxies[i][1])
            smallest_col = galaxies[i][1] if galaxies[i][1] < galaxies[j][1] else galaxies[j][1]
            biggest_col = galaxies[i][1] if galaxies[i][1] > galaxies[j][1] else galaxies[j][1]
            empty_cols_diff = how_many_empty_lines(smallest_col, biggest_col, empty_cols)
            sum_paths_1 = sum_paths_1 + ((rows_diff-empty_rows_diff) + (empty_rows_diff*2)) \
                                      + ((cols_diff-empty_cols_diff) + (empty_cols_diff*2))
            sum_paths_2 = sum_paths_2 + ((rows_diff-empty_rows_diff) + (empty_rows_diff*1000000)) \
                                      + ((cols_diff-empty_cols_diff) + (empty_cols_diff*1000000))
    print("Sum paths between galaxies after expansion: ", sum_paths_1)
    print("Sum paths between galaxies after bigger expansion: ", sum_paths_2)
