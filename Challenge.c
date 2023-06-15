
/***********************************************************************************************************************
*                                                                                                                      *
*   created by: MPZinke                                                                                                *
*   on 2023.06.13                                                                                                      *
*                                                                                                                      *
*   DEFINITIONS:                                                                                                       *
*       - Index: The index at which a permutation is found in lexigraphical order.                                     *
*       - Order: The order of a card in the lexigraphical order.                                                       *
*       - Rank: The order of a card within a suit.                                                                     *
*       - Suit: The order of a card based on the four, (♣, ♦, ♥, ♠)                                                    *
*       - Permutation: The specific ordering of cards' orders.                                                         *
*       - Message: The base27 string that James Bond reads.                                                            *
*                                                                                                                      *
***********************************************************************************************************************/


#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define uint240_t uint64_t


// ——————————————————————————————————————————————————— CONSTANTS  ——————————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

// ERRORS
enum ERRORS
{
	INVALID_SUIT_ERROR,
	INVALID_RANK_ERROR,
	STRING_TOO_LONG_ERROR,
	CHARACTER_NOT_FOUND
};


// ———————————————————————————————————————————————— CONSTANTS::CARDS ———————————————————————————————————————————————— //

#define DECK_SIZE 52
#define UNICODE_CHARACTER_SIZE 3


// ♣ — 226 153 163
// ♦ — 226 153 166
// ♥ — 226 153 165
// ♠ — 226 153 160
// Ordered by normality index, where offset from normality indicates the bit value
const char SUITS[] = "♣♦♥♠";
const char RANKS[] = "A23456789TJQK";
const uint8_t RANKS_LENGTH = sizeof(RANKS) - 1;


// ——————————————————————————————————————————————— CONSTANTS::MESSAGE ——————————————————————————————————————————————— //

const char CHARACTER_MAPPINGS[] = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const uint8_t CHARACTER_MAPPINGS_LENGTH = sizeof(CHARACTER_MAPPINGS) - 1;


// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

// ——————————————————————————————————————————— CARD INT-STRING CONVERSION ——————————————————————————————————————————— //

uint8_t rank_value(char rank)
{
	for(uint8_t x = 0; x < RANKS_LENGTH; x++)
	{
		if(rank == RANKS[x])
		{
			return x;
		}
	}

	fprintf(stderr, "INVALID_RANK_ERROR\n");
	exit(INVALID_RANK_ERROR);
}


uint8_t suit_value(char* suit_set)
{
	for(uint8_t x = 0; x < (sizeof(SUITS) / UNICODE_CHARACTER_SIZE); x++)
	{
		if(  suit_set[0] == SUITS[x*UNICODE_CHARACTER_SIZE]
		  && suit_set[1] == SUITS[x*UNICODE_CHARACTER_SIZE + 1]
		  && suit_set[2] == SUITS[x*UNICODE_CHARACTER_SIZE + 2]
		)
		{
			return x;
		}
	}

	fprintf(stderr, "INVALID_SUIT_ERROR\n");
	exit(INVALID_SUIT_ERROR);
}


uint8_t card_order(char* card)
/*
SUMMARY: Convert a card string to its order.
*/
{
	return RANKS_LENGTH * suit_value(card+1) + rank_value(card[0]);
}


void card_string(uint8_t order, char card[5])
{
	card[0] = RANKS[order % RANKS_LENGTH];
	uint8_t suit = order / RANKS_LENGTH;
	card[1] = SUITS[suit*UNICODE_CHARACTER_SIZE];
	card[2] = SUITS[suit*UNICODE_CHARACTER_SIZE + 1];
	card[3] = SUITS[suit*UNICODE_CHARACTER_SIZE + 2];
}


// ———————————————————————————————————————————— MESSAGE-INDEX CONVERSION ———————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

uint8_t character_index(char character)
{
	for(uint8_t index = 0; index < CHARACTER_MAPPINGS_LENGTH; index++)
	{
		if(CHARACTER_MAPPINGS[index] == character)
		{
			return index;
		}
	}

	fprintf(stderr, "CHARACTER_NOT_FOUND\n");
	exit(CHARACTER_NOT_FOUND);
}


uint240_t message_to_permutation_index(char* message)
/*
SUMMARY: Converts the message to a unique base 27 value.
*/
{
	uint240_t permutation_index = 0.0;

	// Iterate through message
	for(uint32_t message_index = 0; message[message_index] && message_index < 0xFFFFFFFF; message_index++)
	{
		char current_character = message[message_index];
		uint8_t base27_value = character_index(current_character);
		permutation_index = (uint240_t)((uint240_t)CHARACTER_MAPPINGS_LENGTH * permutation_index) + (uint240_t)base27_value;
	}

	return permutation_index;
}


void permutation_index_to_message(uint240_t permutation_index, char* message)
{
	uint32_t x = 0;
	for(; permutation_index > 0.0 && x < 0xFFFFFFFF; x++)
	{
		uint240_t mod = fmod(permutation_index, (uint240_t)CHARACTER_MAPPINGS_LENGTH);
		assert(mod < 0xFF);
		message[x] = CHARACTER_MAPPINGS[mod];
		permutation_index = (permutation_index - mod) / CHARACTER_MAPPINGS_LENGTH;
	}
	message[x--] = 0;

	// String is reversed; unreverse it
	for(uint32_t left_index = 0; left_index < (x+1) / 2; left_index++)
	{
		uint32_t right_index = x - left_index;
		message[left_index] ^= message[right_index];
		message[right_index] ^= message[left_index];
		message[left_index] ^= message[right_index];
	}
}


// —————————————————————————————————————————— INDEX-PERMUTATION CONVERSION —————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

uint240_t factorial(uint8_t n)
{
	uint240_t product = 1.0;
	for(uint8_t x = n; x > 0; x--)
	{
		product *= (uint240_t)x;
	}

	return product;
}


void shift_array(uint8_t remaining_cards_values[DECK_SIZE], uint8_t starting_index)
{
	for(uint8_t x = starting_index; x < DECK_SIZE-1; x++)
	{
		remaining_cards_values[x] = remaining_cards_values[x+1];
	}
}


void index_to_permutation(uint240_t permutation_index, uint8_t card_orders[])
/*
FROM: https://stackoverflow.com/a/34532109
*/
{
	uint8_t unchosen_cards_orders[DECK_SIZE];  // Sliding array of remaining card orders. Size determined by `x`.
	for(uint8_t x = 0; x < DECK_SIZE; x++)
	{
		unchosen_cards_orders[x] = x;
	}

	for(uint8_t x = 0; x < DECK_SIZE; x++)
	{
		uint240_t permutation_group_size = factorial(DECK_SIZE - x - 1);
		uint32_t unchosen_cards_orders_index = (uint32_t)(permutation_index / permutation_group_size);
		assert(0 <= unchosen_cards_orders_index && unchosen_cards_orders_index < DECK_SIZE - x);

		uint8_t card_order = unchosen_cards_orders[unchosen_cards_orders_index];
		card_orders[x] = card_order;

		shift_array(unchosen_cards_orders, unchosen_cards_orders_index);
		permutation_index = permutation_index - (floor(permutation_index / permutation_group_size) * permutation_group_size);
	}
}


uint240_t permutation_to_index(uint8_t card_orders[])
/*
https://stackoverflow.com/a/12147386
*/
{
	uint240_t permutation_index = 0.0;
	for(uint8_t x = 0; x < DECK_SIZE; x++)
	{
		uint240_t z = 0.0;
		for(uint8_t y = x+1; y < DECK_SIZE; y++)
		{
			if(card_orders[y] < card_orders[x])
			{
				z += 1.0;
			}
		}

		permutation_index += z * factorial(DECK_SIZE - x - 1);
	}

	return permutation_index;
}


void decode(char* cards[], char* message)
{
	uint8_t card_orders[DECK_SIZE];
	for(uint8_t x = 0; x < DECK_SIZE; x++)
	{
		card_orders[x] = card_order(cards[x]);
	}

	uint240_t permutation_index = permutation_to_index(card_orders);

	permutation_index_to_message(permutation_index, message);
}


void encode(char* message, char* cards[])
{
	uint240_t permutation_index = message_to_permutation_index(message);

	uint8_t card_orders[DECK_SIZE];
	index_to_permutation(permutation_index, card_orders);

	for(uint8_t x = 0; x < DECK_SIZE; x++)
	{
		card_string(card_orders[x], cards[x]);
	}
}


// —————————————————————————————————————————————————————— MAIN —————————————————————————————————————————————————————— //

int main()
{
	char* cards[] = {"A♣", "2♣", "3♣", "4♣", "5♣", "6♣", "7♣", "8♣", "9♣", "T♣", "J♣", "Q♣", "K♣", "A♦", "2♦", "3♦",
	  "4♦", "5♦", "6♦", "8♦", "K♠", "A♥", "Q♥", "J♥", "T♦", "T♠", "K♥", "7♠", "9♠", "6♠", "9♥", "2♠", "7♦", "7♥", "6♥",
	  "Q♦", "8♠", "3♥", "K♦", "5♥", "Q♠", "T♥", "A♠", "5♠", "J♠", "2♥", "4♥", "3♠", "4♠", "J♦", "8♥", "9♦"};

	return 0;
}
