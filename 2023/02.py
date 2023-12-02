#!/usr/bin/python3

import sys

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 02.py file_to_use")
        exit(1)

    infile = open(sys.argv[1], "r")
    data = infile.readlines()
    infile.close()

    max_cubes = {
        "red":12,
        "green":13,
        "blue":14
    }

    sum_ids = 0
    sum_cube_powers = 0
    for line in data:
        line = line.strip()
        x = line.split(": ")
        x1 = x[0].split(" ")
        game_id = (int)(x1[1])
        current_max = {
            "red":0,
            "green":0,
            "blue":0
        }
        for round in x[1].split("; "):
            for colour in round.split(", "):
                count = colour.split(" ")
                if (current_max[count[1]] < (int)(count[0])):
                    current_max[count[1]] = (int)(count[0])
        if ((current_max["red"]<=max_cubes["red"]) and (current_max["blue"]<=max_cubes["blue"]) and (current_max["green"]<=max_cubes["green"])):
            sum_ids = sum_ids + game_id
        sum_cube_powers = sum_cube_powers + (current_max["red"] * current_max["blue"] * current_max["green"])
    print("Sum game IDs possible games (part 1): ",sum_ids)
    print("Sum cube powers (part 2): ",sum_cube_powers)

