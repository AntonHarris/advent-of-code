#!/usr/bin/python3

import sys

def find_value_in_map(value: int) -> int:
    pass

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 05.py file_to_use")
        exit(1)

    with open(sys.argv[1], 'r') as infile:
        data = [line.strip() for line in infile.readlines()]
    
    # seeds = [int(seed) for seed in data[0].split(": ")[1].split(" ")]
    seeds = list(map(int, data[0].split(": ")[1].split(" ")))

    idx = 3
    # arrays of maps, fields destination_start, source_start, and source_end
    seeds_to_soil = []
    while data[idx] != "":
        # add values to mapping
        idx = idx+1
    
    idx = idx+2
    soil_to_fertilizer = []
    while data[idx] != "":
        # add values to mapping
        idx = idx+1

    idx = idx+2
    fertilizer_to_water = []
    while data[idx] != "":
        # add values to mapping
        idx = idx+1

    idx = idx+2
    water_to_light = []
    while data[idx] != "":
        # add values to mapping
        idx = idx+1

    idx = idx+2
    light_to_temperature = []
    while data[idx] != "":
        # add values to mapping
        idx = idx+1

    idx = idx+2
    temperature_to_humidity = []
    while data[idx] != "":
        # add values to mapping
        idx = idx+1

    idx = idx+2
    humidity_to_location = []
    while idx<len(data) and data[idx] != "":
        # add values to mapping
        idx = idx+1
