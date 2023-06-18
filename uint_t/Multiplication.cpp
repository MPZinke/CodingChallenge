
/***********************************************************************************************************************
*                                                                                                                      *
*   created by: MPZinke                                                                                                *
*   on 2023.06.17                                                                                                      *
*                                                                                                                      *
*   DESCRIPTION: TEMPLATE                                                                                              *
*   BUGS:                                                                                                              *
*   FUTURE:                                                                                                            *
*                                                                                                                      *
***********************************************************************************************************************/


#include "uint_t.hpp"


	// uint12_t result = new_uint12_t_equaling_0();

	// uint8_t carry = 0;
	// for(uint16_t x = 0; x < DIGIT_COUNT * DIGIT_SHIFT; x++)
	// {
	// 	uint16_t a_digit = x / DIGIT_SHIFT, a_bit = x % DIGIT_SHIFT;  // 16 bit for x = 240 + y = 240
	// 	uint32_t a_bit_value = (a._digits[a_digit] >> a_bit) & 0b1;

	// 	uint12_t product = new_uint12_t_equaling_0();
	// 	for(uint16_t y = 0; y < DIGIT_COUNT * DIGIT_SHIFT; y++)
	// 	{
	// 		uint16_t b_digit = y / DIGIT_SHIFT, b_bit = y % DIGIT_SHIFT;  // 16 bit for x = 240 + y = 240

	// 		register uint32_t b_bit_value = (b._digits[b_digit] >> b_bit) & 0b1;
	// 		register uint8_t bit_value = a_bit_value & b_bit_value ^ carry;
	// 		carry = ((a_bit_value & b_bit_value + carry) & 0b10) >> 1;

	// 		uint16_t product_digit = (y+x) / DIGIT_SHIFT, product_bit = (y+x) % DIGIT_SHIFT;
	// 		if(DIGIT_COUNT <= product_digit || DIGIT_SHIFT <= product_bit)
	// 		{
	// 			break;
	// 		}

	// 		product._digits[product_digit] |= (bit_value << product_bit) & DIGIT_MASK;
	// 	}

	// 	result = abs_add(result, product);
	// }

	// return result;

uint_t uint_t::operator*(input_t right)
{
}


uint_t operator*(uint_t& left, uint_t& right)
{
	uint_t& a = left._size >= right._size ? left : right;
	uint_t& b = left._size >= right._size ? right : left;

	uint_t sum;  // sum of sub_products
	digit_t carry = 0;

	const uint64_t a_iterations = a._size * DIGIT_SHIFT;
	const uint64_t b_iterations = b._size * DIGIT_SHIFT;
	for(uint64_t x = 0; x < a_iterations; x++)
	{
		double_digit_t a_digit = x / DIGIT_SHIFT, a_bit = x % DIGIT_SHIFT;  // double for x=240 + y=240 or similar
		digit_t a_bit_value = (a._digits[a_digit] >> a_bit) & 0b1;

		uint_t sub_product;
		for(uint64_t y = 0; y < b_iterations; y++)
		{
			double_digit_t b_digit = y / DIGIT_SHIFT, b_bit = y % DIGIT_SHIFT;  // double for x=240 + y=240 or similar

			digit_t b_bit_value = (b._digits[b_digit] >> b_bit) & 0b1;
			digit_t sub_product_bit_value = a_bit_value & b_bit_value ^ carry;
			carry = ((a_bit_value & b_bit_value + carry) & 0b10) >> 1;

			uint64_t iteration = x + y;
			double_digit_t sub_product_digit = iteration / DIGIT_SHIFT, sub_product_bit = iteration % DIGIT_SHIFT;
			if(a._size <= sub_product_digit || DIGIT_SHIFT <= sub_product_bit)
			{
				break;
			}

			sub_product._digits[sub_product_digit] |= (sub_product_bit_value << sub_product_digit) & DIGIT_MASK;
		}
	}
}
// uint_t& operator*=(uint_t& left, input_t right);
// uint_t& operator*=(uint_t& left, uint_t& right);