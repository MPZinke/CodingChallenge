

#include "uint_t.hpp"


int bit_length(digit_t digit)
{
	static_assert(DIGIT_SHIFT <= sizeof(unsigned long) * 8, "digit is larger than unsigned long");
	int d;
	// FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L2981
	// PyLong_SHIFT - bit_length_digit(w1->long_value.ob_digit[size_w-1])
	if(digit == 0)
	{
		return DIGIT_SHIFT;
	}

	// __builtin_clzl() is available since GCC 3.4.
	return (int)sizeof(unsigned long) * 8 - __builtin_clzl(digit);
}


// uint_t operator/(input_t right);
uint_t operator/(uint_t& numerator, uint_t& denominator)

/*
PROTOTYPE: `static PyLongObject* x_divrem(PyLongObject *v1, PyLongObject *w1, PyLongObject **prem)`
           `v1` — Numerator
           `w1` — Denominator
FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L2947
*/
{
	if(numerator == denominator)
	{
		return uint_t(1, 1);
	}
	else if(numerator < denominator)
	{
		return uint_t(1, 0);
	}

	int shift_amount = DIGIT_SHIFT - bit_length(denominator._digits[denominator._size-1]);
	uint_t denominator_shift = denominator << shift_amount;
	uint_t numerator_shift = numerator << shift_amount;
	digit_t shift_overflow = numerator._digits[numerator._size-1] >> (DIGIT_SHIFT - (shift_amount % DIGIT_SHIFT));
	if(shift_overflow != 0
	  || numerator_shift._digits[numerator_shift._size-1] >= denominator_shift._digits[denominator_shift._size-1]
	)
	{
		numerator_shift.resize(1);
		numerator_shift._digits[numerator_shift._size-1] = shift_overflow;
	}
}

// uint_t& operator/=(uint_t& left, input_t right);
// uint_t& operator/=(uint_t& left, uint_t& right);