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
    numbers_dict = dict()
    number_regex, symbols_regex = r'(\d+)', r'[^\.\d]'
    for row, line in enumerate(data):
        matches = re.finditer(symbols_regex, line)
        for match in matches:
            symbols_list.append({"id":f"{row}-{match.start()}", "row": row, "col": match.start()})
            if match.group(0) == '*':
                gears_list.append({"id":f"{row}-{match.start()}", "row": row, "col": match.start()})
        matches = re.finditer(number_regex, line)
        for match in matches:
            numbers_dict.update({f"{row}-{match.start()}":{"row": row, "col_start": match.start(), "col_end": match.end()-1, "number":int(match.group(0))}})

    # Loop through all symbols, find the numbers next to them, sum them all
    numbers_id_set = set()
    for symbol in symbols_list:
        for number_id in numbers_dict.keys():
            if (numbers_dict[number_id]["row"] == symbol["row"]-1 and ((numbers_dict[number_id]["col_end"] <= symbol["col"]+1 and numbers_dict[number_id]["col_end"] >= symbol["col"]-1) or (numbers_dict[number_id]["col_start"] >= symbol["col"]-1 and numbers_dict[number_id]["col_start"] <= symbol["col"]+1))) or \
               (numbers_dict[number_id]["row"] == symbol["row"] and (numbers_dict[number_id]["col_end"] == symbol["col"]-1 or numbers_dict[number_id]["col_start"] == symbol["col"]+1)) or \
               (numbers_dict[number_id]["row"] == symbol["row"]+1 and ((numbers_dict[number_id]["col_end"] <= symbol["col"]+1 and numbers_dict[number_id]["col_end"] >= symbol["col"]-1) or (numbers_dict[number_id]["col_start"] >= symbol["col"]-1 and numbers_dict[number_id]["col_start"] <= symbol["col"]+1))):
                numbers_id_set.add(number_id)
    parts_numbers_sum = 0
    for number_id in numbers_id_set:
        parts_numbers_sum += numbers_dict[number_id]["number"]
    print(f"Parts sum: {parts_numbers_sum}")

    # Loop through all the gear symbols, find the adjacent numbers, and if there are only 2 sum the multiplications
    gear_ratios_sum = 0
    for gear in gears_list:
        gear_numbers_id_set = set()
        for number_id in numbers_dict.keys():
            if (numbers_dict[number_id]["row"] == gear["row"]-1 and ((numbers_dict[number_id]["col_end"] <= gear["col"]+1 and numbers_dict[number_id]["col_end"] >= gear["col"]-1) or (numbers_dict[number_id]["col_start"] >= gear["col"]-1 and numbers_dict[number_id]["col_start"] <= gear["col"]+1))) or \
               (numbers_dict[number_id]["row"] == gear["row"] and (numbers_dict[number_id]["col_end"] == gear["col"]-1 or numbers_dict[number_id]["col_start"] == gear["col"]+1)) or \
               (numbers_dict[number_id]["row"] == gear["row"]+1 and ((numbers_dict[number_id]["col_end"] <= gear["col"]+1 and numbers_dict[number_id]["col_end"] >= gear["col"]-1) or (numbers_dict[number_id]["col_start"] >= gear["col"]-1 and numbers_dict[number_id]["col_start"] <= gear["col"]+1))):
                gear_numbers_id_set.add(number_id)
        if len(gear_numbers_id_set) == 2:
            gear_ratios_sum += (numbers_dict[gear_numbers_id_set.pop()]["number"]*numbers_dict[gear_numbers_id_set.pop()]["number"])
    print(f"Sum of gear rations: {gear_ratios_sum}")
        
