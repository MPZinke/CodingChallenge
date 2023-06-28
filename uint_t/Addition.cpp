

#include "uint_t.hpp"


// ————————————————————————————————————————————————— OPERATORS::ADD ————————————————————————————————————————————————— //

uint_t uint_t::operator+(input_t right)
{
	uint_t right_uint_t(1, right);
	return *this + right_uint_t;
}


uint_t operator+(uint_t& left, uint_t& right)
{
	uint_t& a = left._size >= right._size ? left : right;
	uint_t& b = left._size >= right._size ? right : left;

	uint_t result(a._size);
	digit_t carry = 0;

	size_t x;
	for(x = 0; x < b._size; x++)
	{
		carry += a._digits[x] + b._digits[x];
		result._digits[x] = carry & DIGIT_MASK;
		carry = carry >> DIGIT_SHIFT;
	}
	for(; x < a._size; x++)
	{
		carry += a._digits[x];
		result._digits[x] = carry & DIGIT_MASK;
		carry = carry >> DIGIT_SHIFT;
	}

	if(carry != 0)
	{
		result.resize(1);
		result._digits[a._size] = carry;
	}

	return result;
}


uint_t& operator+=(uint_t& left, input_t right)
{
	uint_t right_uint_t(1, right);
	return left += right_uint_t;
}


uint_t& operator+=(uint_t& left, uint_t& right)
{
	uint_t result = left + right;
	left = result;
	return left;
}
