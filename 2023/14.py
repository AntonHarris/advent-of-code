#!/usr/bin/python3

import sys

def tilt_north(dish_mapping):
    for j in range(len(dish_mapping[0])):
        next_free = 0
        for i in range(len(dish_mapping)):
            if dish_mapping[i][j]=='#':
                next_free = i+1
            elif dish_mapping[i][j]=='O':
                dish_mapping[i][j]='.'
                dish_mapping[next_free][j]='O'
                next_free += 1
            else:
                pass
    return dish_mapping

def count_rocks(line) -> int:
    return line.count('O')

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 14.py file_to_use")
        exit(1)

    with open(sys.argv[1], 'r') as infile:
        data = [line.strip() for line in infile.readlines()]
    dish_mapping = [[*line] for line in data]

    dish_mapping = tilt_north(dish_mapping)
    sum_rock_vals = 0;
    for i in range(len(dish_mapping)):
        sum_rock_vals = sum_rock_vals + (len(dish_mapping)-i)*count_rocks(dish_mapping[i])
    print("Sum of rock values: ", sum_rock_vals)
