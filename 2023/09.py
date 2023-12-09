#!/usr/bin/python3

import sys

# stolen from Qiqi-impact
def ints(line: str, split=' '):
    return [int(x) for x in line.split(split) if x]

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 09.py file_to_use")
        exit(1)

    with open(sys.argv[1], 'r') as infile:
        data = [line.strip() for line in infile.readlines()]

    sum_ends = 0
    sum_beginnings = 0
    for line in data:
        sequences = []
        sequences.append(ints(line))
        while sum(sequences[-1])!=0 or (sum(sequences[-1])==0 and len(set(sequences[-1]))!=1):
            tmp_arr = []
            for i in range(0, len(sequences[-1])-1):
                tmp_arr.append(sequences[-1][i+1] - sequences[-1][i])
            sequences.append(tmp_arr)
        for i in range(len(sequences)-2, -1, -1):
            sequences[i].append(sequences[i][-1] + sequences[i+1][-1])
            sequences[i].insert(0, sequences[i][0] - sequences[i+1][0])
        sum_ends += sequences[0][-1]
        sum_beginnings += sequences[0][0]
    print("Sum ends: ",sum_ends)
    print("Sum beginnings: ", sum_beginnings)
