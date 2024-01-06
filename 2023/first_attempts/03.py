#!/usr/bin/python3

import sys
import re

def find_symbols(line: str) -> int:
    symbols_search = r'[^\.\d]'
    return True if re.search(symbols_search,line) is not None else False

def find_part_number_sum(data) -> int:
    data_len = len(data)
    numbers_search = r'\d+'

    part_number_sum = 0
    for index, line in enumerate(data):
        line_len = len(line)
        matches = re.search(numbers_search, line)
        start = 0
        end = 0
        while matches is not None:
            curr_start, curr_end = matches.span()
            start = end + curr_start
            end = start + curr_end-curr_start
            symbols_found = False
            if (start>0): start = start-1
            # find if symbols above
            if (index>0):
                if (find_symbols(data[index-1][start:end+1])):
                    symbols_found = True
            # find if symbols to left
            if (start>0):
                if (find_symbols(line[start:start+1])):
                    symbols_found = True
            # find if symbols to right
            if (end<len(line)):
                if (find_symbols(line[end:end+1])):
                    symbols_found = True
            # find if symbols below
            if (index<data_len-1):
                if (find_symbols(data[index+1][start:end+1])):
                    symbols_found = True
            if (symbols_found):
                part_number_sum = part_number_sum + (int)(matches.group(0))
            # get next match
            matches = re.search(numbers_search, line[end:])
    return part_number_sum

def find_gear_ratio(data) -> int:
    data_len = len(data)
    gear_ratio = 0
    gear_symbol = r'\*'
    number_symbol = r'\d+'
    for line_idx, line in enumerate(data):
        line_len = len(line)
        matches = re.search(gear_symbol, line)
        gear_idx = 0
        while matches is not None:
            gear_idx = gear_idx + matches.span()[0]
            # find if adjacent to exactly 2 numbers
            start_x = gear_idx-1 if (gear_idx>0) else gear_idx
            end_x = gear_idx+2 if (gear_idx<line_len-1) else gear_idx
            count_adj_num = 0
            if (line_idx>0):
                num_matches = re.findall(number_symbol, data[line_idx-1][start_x:end_x])
                count_adj_num = count_adj_num + len(num_matches)
            num_matches = re.findall(number_symbol, data[line_idx][start_x:end_x])
            count_adj_num = count_adj_num + len(num_matches)
            if (line_idx<data_len-1):
                num_matches = re.findall(number_symbol, data[line_idx+1][start_x:end_x])
                count_adj_num = count_adj_num + len(num_matches)
            # if adjacent to exactly 2 numbers, find those numbers and multiply them together
            print(f"For gear at x {gear_idx} and y {line_idx}, I found {count_adj_num} adjacent numbers")
            # add ratio to sum of ratios
            gear_idx = gear_idx+1
            matches = re.search(gear_symbol, line[gear_idx:])

    return gear_ratio

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 03.py file_to_use")
        exit(1)

    with open(sys.argv[1], 'r') as infile:
        data = [line.strip() for line in infile.readlines()]

    print("Sum of parts numbers: ", find_part_number_sum(data))
    print("Gear ratio: ", find_gear_ratio(data))
