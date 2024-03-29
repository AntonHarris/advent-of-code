#!/usr/bin/python3

import sys

def find_value_in_map(value: int, mapping_array) -> int:
    for my_map in mapping_array:
        if value < my_map[0]:
            return value
        if value <= my_map[1]:
            return (value + my_map[3])
    return value

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 05.py file_to_use")
        exit(1)

    with open(sys.argv[1], 'r') as infile:
        data = [line.strip() for line in infile.readlines()]

    # seeds = [int(seed) for seed in data[0].split(": ")[1].split(" ")]
    seeds = list(map(int, data[0].split(": ")[1].split(" ")))
    maps = []
    for line in data[1:]:
        if line == "":
            maps.append([]) # add new array to maps array
        elif line[0].isdigit():
            parts = list(map(int, line.split(" ")))
            maps[-1].append([parts[1], parts[1]+parts[2]-1, parts[0], parts[0]-parts[1]])
            # src_start, src_end, dest_start, action
    for idx in range(len(maps)):
        maps[-1].sort(key = lambda x: x[0])

    smallest_location = sys.maxsize
    for seed in seeds:
        value = int(seed)
        for mapping in maps:
            value = find_value_in_map(value, mapping)
        smallest_location = value if value<smallest_location else smallest_location
    print("Smallest location: ", smallest_location)

    """
    Brute-force method, I got the answer after about 25 mins on my computer using 'pypy'.
    TODO: find optimised algorithm.
    Misc. optimisation: multi-threading for each range
    """
    smallest_location = sys.maxsize
    seeds_array = data[0].split(": ")[1].split(" ")
    seeds_with_ranges = [[int(seeds_array[i]), int(seeds_array[i + 1])] for i in range(0, len(seeds_array), 2)]
    for seed_range in seeds_with_ranges:
        for seed in range(seed_range[0], seed_range[0] + seed_range[1]):
            value = int(seed)
            for mapping in maps:
                value = find_value_in_map(value, mapping)
            smallest_location = value if value<smallest_location else smallest_location # not re-initialising because it's still a valid value
    print("Smallest location, part 2: ", smallest_location)

