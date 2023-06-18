

#include "uint_t.hpp"


// —————————————————————————————————————————————— OPERATORS::SUBTRACT  —————————————————————————————————————————————— //

void subtract(digit_t* left_digits, size_t left_size, digit_t* right_digits, size_t right_size, digit_t* result_digits)
/*
Result size should always equal left_size
*/
{
	digit_t borrow = 0;
	size_t x;
	for(x = 0; x < right_size; x++)
	{
		borrow = left_digits[x] - right_digits[x] - borrow;
		result_digits[x] = borrow & DIGIT_MASK;
		borrow = borrow >> DIGIT_SHIFT;
		borrow = borrow & 1;
	}
	for(; x < left_size; x++)
	{
		borrow = left_digits[x] - borrow;
		result_digits[x] = borrow & DIGIT_MASK;
		borrow = borrow >> DIGIT_SHIFT;
		borrow = borrow & 1;
	}

	assert(borrow == 0);
}


void calculate_subtraction_size(uint_t& left, size_t& left_size, uint_t& right, size_t& right_size)
{
	left_size = left._size;
	right_size = right._size;

	if(left._size == right._size)
	{
		for(; left_size > 0 && left._digits[left_size-1] == right._digits[left_size-1]; left_size--)
		{}

		if(left_size == 0)
		{
			return;
		}

		assert(left._digits[left_size] >= right._digits[left_size]);

		right_size = left_size;
	}
}


uint_t uint_t::operator-(input_t right)
{
	uint_t right_uint_t(right);
	return *this - right_uint_t;
}


uint_t operator-(uint_t& left, uint_t& right)
{
	assert(left._size >= right._size);

	uint_t result;

	size_t left_size, right_size;
	calculate_subtraction_size(left, left_size, right, right_size);
	if(left_size == 0)
	{
		return result;
	}

	result.size(left_size);
	subtract(left._digits, left_size, right._digits, right_size, result._digits);

	return result;
}


uint_t& operator-=(uint_t& left, input_t right)
{
	uint_t right_uint_t(right);
	return left -= right_uint_t;
}


uint_t& operator-=(uint_t& left, uint_t& right)
{
	assert(left._size >= right._size);

	size_t left_size, right_size;
	calculate_subtraction_size(left, left_size, right, right_size);
	if(left_size == 0)
	{
		left.swap_digits(new digit_t[1](), 1);
		return left;
	}

	digit_t* temp = new digit_t[left_size]();
	subtract(left._digits, left_size, right._digits, right_size, temp);

	left.swap_digits(temp, left_size);

	return left;
}
