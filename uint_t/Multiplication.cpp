
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


uint_t uint_t::operator*(input_t right)
{
	uint_t right_uint_t(right);
	return *this * right_uint_t;
}


uint_t operator*(uint_t& left, uint_t& right)
{
	uint64_t required_bits = left.most_significant_bit()+1 + right.most_significant_bit()+1;
	size_t required_digits = (required_bits + DIGIT_SHIFT - 1) / DIGIT_SHIFT;

	uint_t sum;  // sum of sub_products
	sum.size(required_digits);

	digit_t carry = 0;
	for(uint64_t x = 0; x < required_bits; x++)
	{
		uint16_t left_digit = x / DIGIT_SHIFT, left_bit = x % DIGIT_SHIFT;  // shouln't have more than 65536 digits
		digit_t left_bit_value = (left._digits[left_digit] >> left_bit) & 0b1;

		uint_t sub_product;
		sub_product.size(required_digits);

		for(uint64_t y = 0; y < (required_bits - (x > required_bits ? 0 : x)); y++)
		{
			uint16_t right_digit = y / DIGIT_SHIFT, right_bit = y % DIGIT_SHIFT;  // shouldn't have more than 65536 digits

			digit_t right_bit_value = (right._digits[right_digit] >> right_bit) & 0b1;
			digit_t sub_product_bit_value = left_bit_value & right_bit_value ^ carry;
			carry = ((left_bit_value & right_bit_value + carry) & 0b10) >> 1;

			uint64_t iteration = x + y;
			double_digit_t sub_product_digit = iteration / DIGIT_SHIFT, sub_product_bit = iteration % DIGIT_SHIFT;
			sub_product._digits[sub_product_digit] |= (sub_product_bit_value << sub_product_bit) & DIGIT_MASK;
		}

		sum += sub_product;
	}

	sum.trim();
	return sum;
}


uint_t& operator*=(uint_t& left, input_t right)
{
	uint_t right_uint_t(right);
	return left *= right_uint_t;
}


uint_t& operator*=(uint_t& left, uint_t& right)
{
	uint_t result = left * right;
	left = result;
	return left;
}