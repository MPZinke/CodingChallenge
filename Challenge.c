
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
*                                                                                                                      *
***********************************************************************************************************************/


#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// ERRORS
enum ERRORS
{
	INVALID_SUIT_ERROR,
	INVALID_RANK_ERROR,
	STRING_TOO_LONG_ERROR,
	CHARACTER_NOT_FOUND
};


// ——————————————————————————————————————————————————— CONSTANTS  ——————————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //


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


// ———————————————————————————————————————————— CARD INTEGER  CONVERSION ———————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

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


uint8_t card_order_func(char* card)
/*
SUMMARY: Convert a card string to its order.
*/
{
	return RANKS_LENGTH * suit_value(card+1) + rank_value(card[0]);
}


void card_string(uint8_t order, char card[4])
{
	card[0] = RANKS[order % RANKS_LENGTH];
	uint8_t suit = order / RANKS_LENGTH;
	card[1] = SUITS[suit*UNICODE_CHARACTER_SIZE];
	card[2] = SUITS[suit*UNICODE_CHARACTER_SIZE + 1];
	card[3] = SUITS[suit*UNICODE_CHARACTER_SIZE + 2];
}


void print_card(uint8_t card_order)
{
	char card[5] = {0, 0, 0, 0, 0};
	card_string(card_order, card);
	printf("%s", card);
}


// ———————————————————————————————————————————— PERMUTATION  ENUMERATION ———————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

double factorial(uint8_t n)
{
	double product = 1.0;
	for(uint8_t x = n; x > 0; x--)
	{
		product *= (double)x;
	}

	return product;
}


void shift_array(uint8_t remaining_cards_values[DECK_SIZE], uint8_t starting_index)
{
	printf("shift_array::starting_index: %hhu\n", starting_index);
	for(uint8_t x = 0; x < DECK_SIZE; x++)
	{
		printf("%2hhu, ", remaining_cards_values[x]);
	}
	printf("\n");

	for(uint8_t x = starting_index; x < DECK_SIZE-1; x++)
	{
		remaining_cards_values[x] = remaining_cards_values[x+1];
	}

	for(uint8_t x = 0; x < DECK_SIZE; x++)
	{
		printf("%2hhu, ", remaining_cards_values[x]);
	}
	printf("\n");
}


void index_to_permutation(double permutation_index, uint8_t cards[])
/*
FROM: https://stackoverflow.com/a/34532109
*/
{
	printf("index_to_permutation\n");
	// uint8_t cards[DECK_SIZE];  // Array of cards' orders, ordered by output.

	uint8_t remaining_cards_orders[DECK_SIZE];  // Sliding array of remaining card orders. Size determined by `x`.
	for(uint8_t x = 0; x < DECK_SIZE; x++)
	{
		remaining_cards_orders[x] = x;
	}

	for(uint8_t x = 0; x < DECK_SIZE; x++)
	{
		double possible_permutation_group_size = factorial(DECK_SIZE - x - 1);
		uint32_t cards_orders_index = (uint32_t)(permutation_index / possible_permutation_group_size);
		assert(0 <= cards_orders_index && cards_orders_index < DECK_SIZE - x);
		printf("permutation_index: %f, possible_permutation_group_size: %f, cards_orders_index: %u\n", permutation_index, possible_permutation_group_size, cards_orders_index);

		uint8_t card_order = remaining_cards_orders[cards_orders_index];
		cards[x] = card_order;

		shift_array(remaining_cards_orders, cards_orders_index);
		permutation_index = permutation_index - (floor(permutation_index / possible_permutation_group_size) * possible_permutation_group_size);

		print_card(card_order);
		printf("\n\n");
	}
}


// https://stackoverflow.com/questions/12146910/finding-the-lexicographic-index-of-a-permutation-of-a-given-array
// Determine permutation from each character offset
double permutation_to_index(char* cards[])
{
	// Iterate cards
	uint8_t card_values[DECK_SIZE];  // Array of cards' values ordered by when received.
	for(uint8_t x = 0; x < DECK_SIZE; x++)
	{
		card_values[x] = card_order_func(cards[x]);
	}

	double permutation_index = 0.0;
	for(uint8_t x = 0; x < DECK_SIZE; x++)
	{
		double z = 0.0;
		for(uint8_t y = x+1; y < DECK_SIZE; y++)
		{
			if(card_values[y] < card_values[x])
			{
				z += 1.0;
			}
		}

		permutation_index += z * factorial(DECK_SIZE - x - 1);
	}

	return permutation_index;
}


// ——————————————————————————————————————————— MESSAGE INTEGER CONVERSION ——————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

uint64_t message_length(char* message)
{
	uint64_t length = 0;
	for(uint64_t length = 0; length < 0xFFFFFFFFFFFFFFFF; length++)
	{
		if(message[length] == '\0')
		{
			return length;
		}
	}

	fprintf(stderr, "STRING_TOO_LONG_ERROR\n");
	exit(STRING_TOO_LONG_ERROR);
}


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


double message_to_unique_int(char* message)
/*
SUMMARY: Converts the message to a unique base 27 value.
*/
{
	double permutation_index = 0.0;

	// Iterate through message
	for(uint32_t message_index = 0; message[message_index] && message_index < 0xFFFFFFFF; message_index++)
	{
		char current_character = message[message_index];
		uint8_t base27_value = character_index(current_character);
		printf("%c [%2d of %2d]  ", CHARACTER_MAPPINGS[base27_value], base27_value, CHARACTER_MAPPINGS_LENGTH);
		permutation_index = (double)((double)CHARACTER_MAPPINGS_LENGTH * permutation_index) + (double)base27_value;
		printf("%f\n", permutation_index);
	}

	return permutation_index;
}


void unique_int_to_message(double permutation_index, char* message)
{
	uint32_t x = 0;
	for(; permutation_index > 0.0 && x < 0xFFFFFFFF; x++)
	{
		double mod = fmod(permutation_index, (double)CHARACTER_MAPPINGS_LENGTH);
		assert(mod < 0xFF);
		message[x] = CHARACTER_MAPPINGS[(uint8_t)fabs(mod)];
		printf("%f %% %hhu = %f\n", permutation_index, CHARACTER_MAPPINGS_LENGTH, mod);
		permutation_index = (permutation_index - mod) / CHARACTER_MAPPINGS_LENGTH;
	}
	message[x--] = 0;

	// for(uint32_t left_index = 0; left_index < (x+1) / 2; left_index++)
	// {
	// 	uint32_t right_index = x - left_index;
	// 	message[left_index] ^= message[right_index];
	// 	message[right_index] ^= message[left_index];
	// 	message[left_index] ^= message[right_index];
	// }
}


int main()
{
	char* cards[] = {"A♣", "2♣", "3♣", "4♣", "5♣", "6♣", "7♣", "8♣", "9♣", "T♣", "J♣", "Q♣", "K♣", "A♦", "2♦", "3♦",
	  "4♦", "5♦", "6♦", "8♦", "K♠", "A♥", "Q♥", "J♥", "T♦", "T♠", "K♥", "7♠", "9♠", "6♠", "9♥", "2♠", "7♦", "7♥", "6♥",
	  "Q♦", "8♠", "3♥", "K♦", "5♥", "Q♠", "T♥", "A♠", "5♠", "J♠", "2♥", "4♥", "3♠", "4♠", "J♦", "8♥", "9♦"};
	// for(uint8_t x = 0; x < DECK_SIZE; x++)
	// {
	// 	uint8_t card = card_order_func(cards[x]);
	// 	printf("%s\n", cards[x]);
	// 	printf(" %hhu\n", card);
	// 	card_string(card, cards[x]);

	// 	printf("%s\n", cards[x]);
	// }

	char message[] = "WAYNEWANTEDTHISTOBEHARDER";
	double permutation_index1 = message_to_unique_int(message);
	// double permutation_index1 = permutation_to_index(cards);
	char message_result[512];
	message_result[500] = 0;
	printf("%s\n", message_result);
	unique_int_to_message(permutation_index1, message_result);
	printf("%s\n", message_result);
	// uint8_t cards_result[DECK_SIZE];
	// index_to_permutation(permutation_index1, cards_result);
	// for(uint8_t x = 0; x < DECK_SIZE; x++)
	// {
	// 	// print_card(cards_result[x]);
	// 	// printf("\n");
	// 	char card[5];
	// 	card_string(cards_result[x], card);
	// 	if(strcmp(cards[x], card) == 0)
	// 	{
	// 		printf("True\n");
	// 	}
	// 	else printf("False\n");
	// }

	// char message[512];
	// unique_int_to_message(permutation_index1, message);


	// double permutation_index2 = message_to_unique_int("WAYNEWANTEDTHISTOBEHARDER");

	// uint8_t cards2[DECK_SIZE];
	// index_to_permutation((double)permutation_index2, cards2);
	// printf("%f\n", permutation_index1);
	// printf("%f\n", permutation_index2);


	return 0;
}
