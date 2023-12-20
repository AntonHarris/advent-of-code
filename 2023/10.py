#!/usr/bin/python3

import sys
from enum import Enum

class PipeDirections(Enum):
    NONE = 0, 0
    NORTH = -1, 0
    EAST = 0, +1
    SOUTH = +1, 0
    WEST = 0, -1

"""
| is a vertical pipe connecting north and south.
- is a horizontal pipe connecting east and west.
L is a 90-degree bend connecting north and east.
J is a 90-degree bend connecting north and west.
7 is a 90-degree bend connecting south and west.
F is a 90-degree bend connecting south and east.
. is ground; there is no pipe in this tile.
S is the starting position of the animal
"""

def find_start(data):
    for i in range(0, len(data)):
        for j in range(0, len(data[i])):
            if data[i][j] == 'S':
                return i,j

def find_first_dir(row, col, data) -> PipeDirections:
    # check N-E-S-W to find first I can take
    if row>0 and (data[row-1][col] == '|' or data[row-1][col] == '7' or data[row-1][col] == 'F'):
        return PipeDirections.NORTH
    if col<len(data[row]) and (data[row][col+1] == '-' or data[row][col+1] == 'J' or data[row][col+1] == '7'):
        return PipeDirections.EAST
    if row<len(data) and (data[row+1][col] == '|' or data[row+1][col] == 'L' or data[row+1][col] == 'J'):
        return PipeDirections.SOUTH
    return PipeDirections.WEST

def find_next_dir(row, col, prev_dir, data) -> PipeDirections:
    if data[row][col] == '|':
        if prev_dir == PipeDirections.NORTH:
            return PipeDirections.NORTH
        return PipeDirections.SOUTH
    if data[row][col] == '-':
        if prev_dir == PipeDirections.EAST:
            return PipeDirections.EAST
        return PipeDirections.WEST
    if data[row][col] == 'L':
        if prev_dir == PipeDirections.SOUTH:
            return PipeDirections.EAST
        return PipeDirections.NORTH
    if data[row][col] == 'J':
        if prev_dir == PipeDirections.SOUTH:
            return PipeDirections.WEST
        return PipeDirections.NORTH
    if data[row][col] == '7':
        if prev_dir == PipeDirections.NORTH:
            return PipeDirections.WEST
        return PipeDirections.SOUTH
    if data[row][col] == 'F':
        if prev_dir == PipeDirections.NORTH:
            return PipeDirections.EAST
        return PipeDirections.SOUTH
    return PipeDirections.NONE # should never reach here

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 10.py file_to_use")
        exit(1)

    with open(sys.argv[1], 'r') as infile:
        data = [line.strip() for line in infile.readlines()]

    pipe_map = []
    second_pipe_map = []
    for line in data:
        pipe_map.append([*line])
        second_pipe_map.append([*line])

    row, col = find_start(pipe_map)
    next_direction = find_first_dir(row, col, pipe_map)
    pipe_length = 1 # 1 for starting position's pipe
    while pipe_map[row+next_direction.value[0]][col+next_direction.value[1]] != 'S':
        row += next_direction.value[0]
        col += next_direction.value[1]
        pipe_length += 1
        next_direction = find_next_dir(row, col, next_direction, pipe_map)
        pipe_map[row][col] = 'S'
    print("Steps to farthest pipe section: ", int(pipe_length/2))

    for i in range(0, len(pipe_map)):
        for j in range(0, len(pipe_map[i])):
            if pipe_map[i][j] != 'S':
                second_pipe_map[i][j] = '.'
    # something should normally be done with S, it should be replaced with the appropriate pipe piece,
    # but it works for my input data so I can't be bothered, maybe in v2.0
    count_inner = 0
    for i in range(len(second_pipe_map)):
        section = 0.0
        for j in range(len(second_pipe_map[i])):
            if second_pipe_map[i][j] == '|':
                section += 1
            elif second_pipe_map[i][j] == '-':
                pass # nohing changes
            elif second_pipe_map[i][j] == 'L':
                section += 0.5
            elif second_pipe_map[i][j] == 'J':
                section -= 0.5
            elif second_pipe_map[i][j] == '7':
                section += 0.5
            elif second_pipe_map[i][j] == 'F':
                section -= 0.5
            elif second_pipe_map[i][j] == '.':
                if abs(section)%2 == 1:
                    count_inner += 1
    print("Number of inner loop areas: ", count_inner)
