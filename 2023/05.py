#!/usr/bin/python3

import sys

def find_value_in_map(value: int, map_array) -> int:
    for my_map in map_array:
        if value >= my_map["src_start"] and value <= my_map["src_end"]:
            return (value + my_map["action"])
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
    idx = -1
    for line in data[1:]:
        if line == "":
            idx = idx + 1
            maps.append([]) # add new array to maps array
        elif line[0].isdigit():
            parts = line.split(" ")
            tmp_dict = {
                "dest_start": int(parts[0]),
                "src_start": int(parts[1]),
                "src_end": int(parts[1])+int(parts[2])-1,
                "action": int(parts[0]) - int(parts[1])
            }
            maps[idx].append(tmp_dict)
        else:
            pass

    smallest_location = sys.maxsize
    for seed in seeds:
        value = int(seed)
        for mapping in maps:
            value = find_value_in_map(value, mapping)
        smallest_location = value if value<smallest_location else smallest_location
    print("Smallest location: ", smallest_location)

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
