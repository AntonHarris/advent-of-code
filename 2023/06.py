#!/usr/bin/python3

import sys
import re

def number_winning_races(times, distances) -> int:
    number_winning_races = 1
    for idx in range(0, len(times)):
        count_winning_races = 0
        for time in range(1, times[idx]):
            if time*(times[idx]-time) > distances[idx]:
                count_winning_races = count_winning_races + 1
        number_winning_races = number_winning_races*count_winning_races
    return number_winning_races

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 06.py file_to_use")
        exit(1)

    with open(sys.argv[1], 'r') as infile:
        data = [line.strip() for line in infile.readlines()]

    times = [int(time) for time in re.findall("\d+", data[0])]
    distances = [int(distance) for distance in re.findall("\d+", data[1])]

    """
    number_winning_races = 1
    for idx in range(0, len(times)):
        races = []
        for time in range(1, times[idx]):
            races.append(time*(times[idx]-time))
        winning_races = list(filter(lambda x: x>distances[idx], races))
        number_winning_races = number_winning_races*len(winning_races)
    print("Number of winning races: ", number_winning_races)
    """
    print("Number of winning races: ", number_winning_races(times, distances))

    times = [int("".join(re.findall("\d+", data[0])))]
    distances = [int("".join(re.findall("\d+", data[1])))]
    print("Number of winning races, part 2: ", number_winning_races(times, distances))
