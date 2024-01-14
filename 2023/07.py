#!/usr/bin/python3

import sys
from enum import Enum

# Global variable
card_order_low_to_high = "23456789TJQKA"

# Enum to order hand types
class Hand_type(Enum):
    FIVE_OF_A_KIND = 7
    FOUR_OF_A_KIND = 6
    FULL_HOUSE = 5
    THREE_OF_A_KIND = 4
    TWO_PAIRS = 3
    ONE_PAIR = 2
    HIGH_CARD = 1

# Class to represent a "poker" hand
class Card_hand:
    def __init__ (self, hand, bid):
        self.hand = hand
        self.bid = int(bid)
        # find hand_type, initialise self.hand_type with value
        hand_dict = dict()
        for c in list(hand):
            if c in hand_dict:
                hand_dict[c] += 1
            else:
                hand_dict[c] = 1
        match len(hand_dict.keys()):
            case 1:
                self.hand_type = Hand_type.FIVE_OF_A_KIND
            case 2:
                if max(hand_dict.values()) == 4:
                    self.hand_type = Hand_type.FOUR_OF_A_KIND
                else:
                    self.hand_type = Hand_type.FULL_HOUSE
            case 3:
                if max(hand_dict.values()) == 3:
                    self.hand_type = Hand_type.THREE_OF_A_KIND
                else:
                    self.hand_type = Hand_type.TWO_PAIRS
            case 4:
                self.hand_type = Hand_type.ONE_PAIR
            case 5:
                self.hand_type = Hand_type.HIGH_CARD
        # find hand_type with J being a Joker, initialise self.hand_type with value, TODO for part 2
        self.hand_type_joker = Hand_type.HIGH_CARD
    
    def __str__ (self):
        return f"Hand: {self.hand}, hand type: {str(self.hand_type.name)}, bid: {self.bid}"
    
    def get_hand_type (self):
        return self.hand_type
    
    def get_bid (self):
        return self.bid

    def compare (self, hand):
        if self.hand_type.value > hand.get_hand_type().value:
            return -1
        if self.hand_type.value < hand.get_hand_type().value:
            return 1
        for i in range(len(self.hand)):
            if card_order_low_to_high.index(self.hand[i]) > card_order_low_to_high.index(hand.hand[i]):
                return -1
            elif card_order_low_to_high.index(self.hand[i]) < card_order_low_to_high.index(hand.hand[i]):
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
        for i in range(len(hands)):
            if hands[i].compare(new_hand) < 0:
                idx = i
                break
        hands.insert(idx, new_hand)
    total_winnings = 0
    for idx, hand in enumerate(hands):
        total_winnings += (idx+1)*hand.get_bid()
    print("Total_winnings: ", total_winnings)
    total_winnings_with_jokers = 0
    for idx, hand in enumerate(hands_with_joker):
        total_winnings_with_jokers += (idx+1)*hand.get_bid()
    print("Total_winnings_with_jokers: ", total_winnings_with_jokers)
