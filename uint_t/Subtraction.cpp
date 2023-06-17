

#include "uint_t.hpp"


// —————————————————————————————————————————————— OPERATORS::SUBTRACT  —————————————————————————————————————————————— //

uint_t uint_t::operator-(input_t right)
{
	uint_t right_uint_t(right);
	return *this - right_uint_t;
}


uint_t operator-(uint_t& left, uint_t& right)
{
	uint_t& a = left._size >= right._size ? left : right;
	uint_t& b = left._size >= right._size ? right : left;

	uint_t result;

	uint8_t size_a = a._size, size_b = b._size;
	if(a._size == b._size)
	{
		for(; size_a > 0 && a._digits[size_a-1] == b._digits[size_a-1]; size_a--)
		{}

		if(size_a == 0)
		{
			return result;
		}

		assert(a._digits[size_a] >= b._digits[size_a]);

		size_b = size_a;
	}

	result.size(size_a);

	digit_t borrow = 0;
	uint8_t x;
	for(x = 0; x < size_b; x++)
	{
		borrow = a._digits[x] - b._digits[x] - borrow;
		result._digits[x] = borrow & DIGIT_MASK;
		borrow = borrow >> DIGIT_SHIFT;
		borrow = borrow & 1;
	}
	for(; x < size_a; x++)
	{
		borrow = a._digits[x] - borrow;
		result._digits[x] = borrow & DIGIT_MASK;
		borrow = borrow >> DIGIT_SHIFT;
		borrow = borrow & 1;
	}

	assert(borrow == 0);

	return result;
}
// friend uint_t& operator-=(uint_t& left, input_t right);
// friend uint_t& operator-=(uint_t& left, uint_t& right);
