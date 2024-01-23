#!/usr/bin/python3

import sys

# TODO: get this function working
def find_horizontal_mirror(pattern) -> tuple[bool, int]:
    for idx in range(len(pattern)//2):
        idx_copy = idx
        idx_mirror = idx+1
        while idx>=0:
            if pattern[idx] != pattern[idx_mirror]:
                break
            idx -= 1
            idx_mirror += 1
            if idx<0:
                return True, idx_copy
    for idx in range(len(pattern)-1,len(pattern)//2,-1):
        idx_copy = idx
        idx_mirror = idx-1
        while idx<len(pattern):
            if pattern[idx] != pattern[idx_mirror]:
                break
            idx += 1
            idx_mirror -= 1
            if idx<0:
                return True, idx_copy
    return False, 0

def find_vertical_mirror(pattern) -> tuple[bool, int]:
    """
    TODO: Create new matrix to call find_horizontal_mirror:
    [                 [
        [1, 2, 3],        [1, 4, 7],
        [4, 5, 6], =>     [2, 5, 8],
        [7, 8, 9]         [3, 6, 9]
    ]                 ]
    """
    return False, 0

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 13.py file_to_use")
        exit(1)

    with open(sys.argv[1], 'r') as infile:
        # data = infile.read()
        # patterns = data.split("\n\n")
        patterns = infile.read().split("\n\n")

    summarise_pattern_notes = 0
    for pattern in patterns:
        pattern_data = pattern.split("\n")
        horizontal_reflection_found, horizontal_reflection_line = find_horizontal_mirror(pattern_data)
        if horizontal_reflection_found == True:
            summarise_pattern_notes += 100*horizontal_reflection_line
        else:
            vertical_reflection_found, vertical_reflection_line = find_vertical_mirror(pattern_data)
            summarise_pattern_notes += vertical_reflection_line
    print(f"Summary of pattern notes: {summarise_pattern_notes}")

