#!/usr/bin/python3

import sys
from enum import Enum

# Global variable
card_order_low_to_high = "23456789TJQKA"
card_order_low_to_high_with_joker = "J23456789TQKA"

# Enum to order hand types
class Hand_type(Enum):
    FIVE_OF_A_KIND = 7
    FOUR_OF_A_KIND = 6
    FULL_HOUSE = 5
    THREE_OF_A_KIND = 4
    TWO_PAIRS = 3
    ONE_PAIR = 2
    HIGH_CARD = 1

def calc_hand_type (hand):
    hand_dict = dict()
    for c in list(hand):
        if c in hand_dict:
            hand_dict[c] += 1
        else:
            hand_dict[c] = 1
    match len(hand_dict.keys()):
        case 1:
            return Hand_type.FIVE_OF_A_KIND
        case 2:
            if max(hand_dict.values()) == 4:
                return Hand_type.FOUR_OF_A_KIND
            else:
                return Hand_type.FULL_HOUSE
        case 3:
            if max(hand_dict.values()) == 3:
                return Hand_type.THREE_OF_A_KIND
            else:
                return Hand_type.TWO_PAIRS
        case 4:
            return Hand_type.ONE_PAIR
    return Hand_type.HIGH_CARD

# TODO: for part 2
def calc_hand_type_with_joker (hand):
    return Hand_type.HIGH_CARD

# Class to represent a "poker" hand
class Card_hand:
    def __init__ (self, hand, bid):
        self.hand = hand
        self.bid = int(bid)
        # find hand_type, initialise self.hand_type with value
        self.hand_type = calc_hand_type(hand)
        # find hand_type with J being a Joker, initialise self.hand_type with value, TODO for part 2
        self.hand_type_joker = calc_hand_type_with_joker(hand)
    
    def __str__ (self):
        return f"Hand: {self.hand}, hand type: {str(self.hand_type.name)}, bid: {self.bid}"
    
    def get_hand (self):
        return self.hand

    def get_hand_type (self):
        return self.hand_type
    
    def get_hand_type_with_joker (self):
        return self.hand_type
    
    def get_bid (self):
        return self.bid

    def compare (self, hand, comparaison_string):
        if self.hand_type.value > hand.get_hand_type().value:
            return -1
        if self.hand_type.value < hand.get_hand_type().value:
            return 1
        for i in range(len(self.hand)):
            if comparaison_string.index(self.hand[i]) > comparaison_string.index(hand.hand[i]):
                return -1
            elif comparaison_string.index(self.hand[i]) < comparaison_string.index(hand.hand[i]):
                return 1
        return 0 # identical hand
    
# Main
if __name__ == "__main__":
    if (len(sys.argv)<2):
        print("Usage: 07.py file_to_use")
        exit(1)

    with open(sys.argv[1], 'r') as infile:
        data = [line.strip() for line in infile.readlines()]

    hands = []
    hands_with_joker = []
    for line in data:
        new_hand = Card_hand(*line.split(" "))
        idx = len(hands)
        idx_with_joker = len(hands_with_joker)
        for i in range(len(hands)):
            if hands[i].compare(new_hand, card_order_low_to_high) < 0:
                idx = i
                break
        for i in range(len(hands_with_joker)):
            if hands_with_joker[i].compare(new_hand, card_order_low_to_high_with_joker) < 0:
                idx_with_joker = i
                break
        hands.insert(idx, new_hand)
        hands_with_joker.insert(idx_with_joker, new_hand)
    total_winnings = 0
    for idx, hand in enumerate(hands):
        total_winnings += (idx+1)*hand.get_bid()
    print("Total_winnings: ", total_winnings)
    total_winnings_with_jokers = 0
    for idx, hand in enumerate(hands_with_joker):
        total_winnings_with_jokers += (idx+1)*hand.get_bid()
    print("Total_winnings_with_jokers: ", total_winnings_with_jokers)
