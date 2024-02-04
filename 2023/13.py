#!/usr/bin/python3

import sys

def count_char_diff(line_1, line_2) -> int:
    return sum(1 for char_1, char_2 in zip(line_1, line_2) if char_1 != char_2)

def find_horizontal_mirror(pattern, target=0) -> tuple[bool, int]:
    half_start = len(pattern)//2 + (1 if len(pattern)%2 != 0 else 0)
    for idx in range(1, half_start):
        idx_copy, idx_mirror = idx, idx-1
        count_diff = 0
        while idx_mirror >= 0:
            count_diff += count_char_diff(pattern[idx], pattern[idx_mirror])
            idx += 1
            idx_mirror -= 1
        if count_diff == target:
            return True, idx_copy
    half_start = half_start - (1 if len(pattern)%2 != 0 else 0)
    for idx in range(half_start, len(pattern)-1):
        idx_copy, idx_mirror = idx, idx+1
        count_diff = 0
        while idx_mirror < len(pattern):
            count_diff += count_char_diff(pattern[idx], pattern[idx_mirror])
            idx -= 1
            idx_mirror += 1
        if count_diff == target:
            return True, idx_copy+1
    return False, 0

def find_vertical_mirror(pattern, target=0) -> tuple[bool, int]:
#    transformed_pattern = list(zip(*pattern))
    transformed_pattern = [''.join(row) for row in zip(*pattern)]
    return find_horizontal_mirror(transformed_pattern, target)

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 13.py file_to_use")
        exit(1)

    with open(sys.argv[1], 'r') as infile:
        patterns = infile.read().split("\n\n")

    targets = [0, 1]
    for target in targets:
        summary_pattern_notes = 0
        for pattern in patterns:
            pattern_data = pattern.split("\n")
            horiz_found, horiz_line = find_horizontal_mirror(pattern_data, target)
            if horiz_found:
                summary_pattern_notes += 100*horiz_line
            else:
                vertic_found, vertic_line = find_vertical_mirror(pattern_data, target)
                summary_pattern_notes += vertic_line
        print(f"Summary notes for target {target} = {summary_pattern_notes}")
