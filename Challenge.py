#!/opt/homebrew/bin/python3
# -*- coding: utf-8 -*-
__author__ = "MPZinke"

########################################################################################################################
#                                                                                                                      #
#   created by: MPZinke                                                                                                #
#   on 2023.06.15                                                                                                      #
#                                                                                                                      #
#   DESCRIPTION:                                                                                                       #
#       - Index: The index at which a permutation is found in lexigraphical order.                                     #
#       - Order: The order of a card in the lexigraphical order.                                                       #
#       - Rank: The order of a card within a suit.                                                                     #
#       - Suit: The order of a card based on the four, (♣, ♦, ♥, ♠)                                                    #
#       - Permutation: The specific ordering of cards' orders.                                                         #
#       - Message: The base27 string that James Bond reads.                                                            #
#                                                                                                                      #
########################################################################################################################


# Playing Cards
SUITS = "♣♦♥♠"
RANKS = "A23456789TJQK"

DECK_SIZE = len(SUITS) * len(RANKS)

# Message
CHARACTER_MAPPINGS = " ABCDEFGHIJKLMNOPQRSTUVWXYZ"


# ———————————————————————————————————————————— CARD INT-STRING CONVERSION ———————————————————————————————————————————— #

def card_order(card_string: str) -> int:
	return RANKS.index(card_string[0]) + len(RANKS) * SUITS.index(card_string[1])


def card_string(card_order: int) -> str:
	return f"{RANKS[card_order % len(RANKS)]}{SUITS[card_order // len(RANKS)]}"


# ————————————————————————————————————————————— MESSAGE-INDEX CONVERSION ————————————————————————————————————————————— #

def message_to_permutation_index(message: str) -> int:
	permutation_index = 0

	for x, character in enumerate(message):
		character_value = CHARACTER_MAPPINGS.index(character)
		permutation_index = permutation_index * len(CHARACTER_MAPPINGS) + character_value

	return permutation_index


def permutation_index_to_message(permutation_index: int) -> str:
	message = ""

	for x in range(0xFFFFFFFF):
		if(permutation_index == 0):
			break

		character = CHARACTER_MAPPINGS[permutation_index % len(CHARACTER_MAPPINGS)]
		message += character
		permutation_index //= len(CHARACTER_MAPPINGS)

	return message[::-1]


# ——————————————————————————————————————————— INDEX-PERMUTATION CONVERSION ——————————————————————————————————————————— #

def factorial(n: int) -> int:
	product = 1
	for x in range(1, n+1):
		product *= x

	return product


def index_to_permutation(permutation_index: int) -> list[int]:
	"""
	FROM: https://stackoverflow.com/a/34532109
	"""
	card_orders = []

	unchosen_cards_orders = [x for x in range(DECK_SIZE)]
	for x in range(DECK_SIZE):
		# Number of permutations index falls within based on currently term of n for permutation
		permutation_group_size = factorial(DECK_SIZE - x - 1)
		# Index of card order in unchosen card list
		unchosen_cards_orders_index = permutation_index // permutation_group_size
		card_orders.append(unchosen_cards_orders[unchosen_cards_orders_index])

		unchosen_cards_orders.pop(unchosen_cards_orders_index)  # remove chosen card

		permutation_index = permutation_index % permutation_group_size  # Continue with remaining permutations

	return card_orders


def permutation_to_index(card_orders: list[int]) -> int:
	"""
	FROM: https://stackoverflow.com/a/12147386
	"""
	permutation_index = 0
	for x, card_order in enumerate(card_orders):
		term_multiplier = 0
		# Determine offset of term to multiply by possibilities
		for y in range(x+1, DECK_SIZE):
			if(card_orders[y] < card_order):
				term_multiplier += 1

		permutation_index += term_multiplier * factorial(DECK_SIZE - x - 1)

	return permutation_index


# ——————————————————————————————————————————— INDEX-PERMUTATION CONVERSION ——————————————————————————————————————————— #

def decode(cards: list[str]) -> str:
	card_orders = [card_order(card) for card in cards]
	permutation_index = permutation_to_index(card_orders)
	message = permutation_index_to_message(permutation_index)
	return message


def encode(message: str) -> list[str]:
	permutation_index = message_to_permutation_index(message)
	card_orders = index_to_permutation(permutation_index)
	cards = [card_string(card_order) for card_order in card_orders]
	return cards


# ——————————————————————————————————————————————————————— MAIN ——————————————————————————————————————————————————————— #

def main():
	cards_input = ['K♣', '7♣', '3♣', 'T♦', '2♣', '9♥', '4♦', 'Q♠', '8♥', 'A♥', 'K♥', '8♠', 'T♠', '4♠', '2♠', '5♦', '9♦', '4♥', '5♥', 'A♣', '7♠', 'J♦', '5♣', '2♥', 'Q♣', 'T♥', 'J♠', '6♠', '6♣', '6♦', 'Q♥', '6♥', '9♠', '3♦', '5♠', '7♥', '2♦', '8♦', 'K♦', 'A♠', '4♣', '3♥', 'A♦', 'J♥', '8♣', 'K♠', 'J♣', '9♣', 'T♣', '3♠', '7♦', 'Q♦']
	message = decode(cards_input)
	print(message)
	cards_output = encode(message)
	print(cards_output)
	assert(cards_input == cards_output)


if(__name__ == "__main__"):
	main()
