

#include "uint_t.hpp"


// —————————————————————————————————————————————— OPERATORS::SUBTRACT  —————————————————————————————————————————————— //

uint_t uint_t::operator-(input_t right)
{
	uint_t right_uint_t(right);
	return *this - right_uint_t;
}


uint_t operator-(uint_t& left, uint_t& right)
{
	assert(left._size >= right._size);

	uint8_t left_size = left_size, right_size = right_size;
	if(left_size == right_size)
	{
		for(; left_size > 0 && left[left_size-1] == right[left_size-1]; left_size--)
		{}

		if(left_size == 0)
		{
			return uint_t();
		}

		assert(left[left_size] >= right[left_size]);

		right_size = left_size;
	}

	uint_t result(left_size);
	digit_t borrow = 0;

	uint8_t x;
	for(x = 0; x < right_size; x++)
	{
		borrow = left[x] - right[x] - borrow;
		result[x] = borrow & DIGIT_MASK;
		borrow = borrow >> DIGIT_SHIFT;
		borrow = borrow & 1;
	}
	for(; x < left_size; x++)
	{
		borrow = left[x] - borrow;
		result[x] = borrow & DIGIT_MASK;
		borrow = borrow >> DIGIT_SHIFT;
		borrow = borrow & 1;
	}

	assert(borrow == 0);

	return result;
}


uint_t& operator-=(uint_t& left, input_t right)
{
	uint_t right_uint_t(right);
	return left -= right_uint_t;
}


uint_t& operator-=(uint_t& left, uint_t& right)
{
	uint_t result = left - right;
	left = result;
	return left;
}
