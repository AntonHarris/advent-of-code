#!/usr/bin/python3

import sys
import re

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 03.py file_to_use")
        exit(1)

    with open(sys.argv[1], 'r') as infile:
        data = [line.strip() for line in infile.readlines()]
    
    symbols_list = []
    gears_list = []
    numbers_list = []
    number_regex, symbols_regex, gear_symbol_regex = r'(\d+)', r'[^\.\d]', r'\*'
    for row, line in enumerate(data):
        matches = re.finditer(symbols_regex, line)
        symbol_id, number_id = 1, 1
        for match in matches:
            symbols_list.append({"id":f"{row}-{symbol_id}", "row": row, "col": match.start()})
            if match.group(0) == '*':
                gears_list.append({"id":f"{row}-{symbol_id}", "row": row, "col": match.start()})
            symbol_id += 1
        matches = re.finditer(number_regex, line)
        for match in matches:
            numbers_list.append({"id":f"{row}-{number_id}", "row": row, "col_start": match.start(), "col_end": match.end()-1, "number":int(match.group(0))})
            number_id += 1

