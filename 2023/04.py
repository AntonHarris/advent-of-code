#!/usr/bin/python3

import sys
import re

if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 04.py file_to_use")
        exit(1)

    with open(sys.argv[1], 'r') as infile:
        data = [line.strip() for line in infile.readlines()]

    sum_winning_cards = 0;
    card_counting = [1] * len(data)
    for card_idx, card in enumerate(data):
        count_winning_numbers = 0
        card_info, numbers = data[card_idx].split(": ")
        card_num = (int)(re.split(r'\s+', card_info)[1])
        winning_numbers, played_numbers = numbers.split(" | ")
        winning_numbers_array = {num:"1" for num in winning_numbers.split()}
        played_numbers_array = {num:"1" for num in played_numbers.split()}
        for num in played_numbers_array.keys():
            count_winning_numbers = count_winning_numbers+1 if num in winning_numbers_array else count_winning_numbers
        for i in range(1,(count_winning_numbers+1)):
            card_counting[card_idx+i] = card_counting[card_idx+i] + card_counting[card_idx]
        sum_winning_cards = (sum_winning_cards + (1<<(count_winning_numbers-1))) if (count_winning_numbers>0) else sum_winning_cards
    print("Sum winning cards final: ", sum_winning_cards)
    print("Total number of cards: ", sum(card_counting))
