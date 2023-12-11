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

# TODO : this function needs to be corrected to correctly determine what is the next direction to take
def find_next_dir(row, col, data, prev_dir=PipeDirections.NONE):
    # check N-E-S-W to find first I can take
    if row>0 and prev_dir != PipeDirections.SOUTH and (data[row-1][col] == '|' or data[row-1][col] == '7' or data[row-1][col] == 'F'):
        return PipeDirections.NORTH
    if col<len(data[row]) and prev_dir != PipeDirections.WEST and (data[row][col+1] == '-' or data[row][col+1] == 'J' or data[row][col+1] == '7'):
        print("through here")
        return PipeDirections.EAST
    if row<len(data) and prev_dir != PipeDirections.NORTH and (data[row+1][col] == '|' or data[row+1][col] == 'L' or data[row+1][col] == 'J'):
        return PipeDirections.SOUTH
    return PipeDirections.WEST

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 10.py file_to_use")
        exit(1)

    with open(sys.argv[1], 'r') as infile:
        data = [line.strip() for line in infile.readlines()]

    pipe_map = []
    for line in data:
        pipe_map.append([*line])

    row, col = find_start(pipe_map)
    print("start: ",row,"-",col,"=",data[row][col])
    next_direction = find_next_dir(row, col, data)
    print("next direction=",next_direction)
    pipe_length = 0
    while data[row+next_direction.value[0]][col+next_direction.value[1]] != 'S':
        row += next_direction.value[0]
        col += next_direction.value[1]
        print(row,"-",col,"=",data[row][col])
        pipe_length += 1
        next_direction = find_next_dir(row, col, data, next_direction)
    print(pipe_length)
