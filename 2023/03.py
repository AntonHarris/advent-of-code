#!/usr/bin/python3

import sys
import re

def find_symbols(line: str) -> int:
    symbols_search = r'[^\.\d]'
    return True if re.search(symbols_search,line) is not None else False

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 03.py file_to_use")
        exit(1)

    with open(sys.argv[1], 'r') as infile:
        data = [line.strip() for line in infile.readlines()]
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
    print("Sum of parts numbers: ",part_number_sum)

