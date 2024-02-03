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

    summarise_pattern_notes = 0
    summarise_pattern_notes_smudged = 0
    for pattern in patterns:
        pattern_data = pattern.split("\n")
        horizontal_reflection_found, horizontal_reflection_line = find_horizontal_mirror(pattern_data)
        if horizontal_reflection_found == True:
            summarise_pattern_notes += 100*horizontal_reflection_line
        else:
            vertical_reflection_found, vertical_reflection_line = find_vertical_mirror(pattern_data)
            summarise_pattern_notes += vertical_reflection_line
        
        horizontal_reflection_found, horizontal_reflection_line = find_horizontal_mirror(pattern_data, 1)
        if horizontal_reflection_found == True:
            summarise_pattern_notes_smudged += 100*horizontal_reflection_line
        else:
            vertical_reflection_found, vertical_reflection_line = find_vertical_mirror(pattern_data, 1)
            summarise_pattern_notes_smudged += vertical_reflection_line

    print(f"Summary of pattern notes: {summarise_pattern_notes}")
    print(f"Summary of pattern notes, smudged mirror: {summarise_pattern_notes_smudged}")

