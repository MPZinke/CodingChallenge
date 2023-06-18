

#include "uint_t.hpp"


// ————————————————————————————————————————————————— OPERATORS::ADD ————————————————————————————————————————————————— //

digit_t add(uint_t& a, uint_t& b, digit_t* result_digits)
/*
RETURNS: The carry digit.
*/
{
	digit_t carry = 0;

	size_t x;
	for(x = 0; x < b._size; x++)
	{
		carry += a._digits[x] + b._digits[x];
		result_digits[x] = carry & DIGIT_MASK;
		carry = carry >> DIGIT_SHIFT;
	}
	for(; x < a._size; x++)
	{
		carry += a._digits[x];
		result_digits[x] = carry & DIGIT_MASK;
		carry = carry >> DIGIT_SHIFT;
	}

	return carry;
}


uint_t uint_t::operator+(input_t right)
{
	uint_t right_uint_t(right);
	return *this + right_uint_t;
}


uint_t operator+(uint_t& left, uint_t& right)
{
	uint_t& a = left._size >= right._size ? left : right;
	uint_t& b = left._size >= right._size ? right : left;

	uint_t result;
	result.size(a._size);

	digit_t carry = add(a, b, result._digits);

	if(carry != 0)
	{
		result.resize(1);
		result._digits[a._size] = carry;
	}

	return result;
}


uint_t& operator+=(uint_t& left, input_t right)
{
	uint_t right_uint_t(right);
	return left += right_uint_t;
}


uint_t& operator+=(uint_t& left, uint_t& right)
{
	uint_t& a = left._size >= right._size ? left : right;
	uint_t& b = left._size >= right._size ? right : left;

	digit_t* temp = new digit_t[a._size]();
	digit_t carry = add(a, b, temp);

	left.swap_digits(temp, a._size);

	if(carry != 0)
	{
		left.resize(1);
		left._digits[a._size] = carry;
	}

	return left;
}
