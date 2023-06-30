

#include "uint_t.hpp"


int bit_length(digit_t digit)
{
	static_assert(DIGIT_SHIFT <= sizeof(unsigned long) * 8, "digit is larger than unsigned long");
	int d;
	// FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L2981
	// PyLong_SHIFT - bit_length_digit(w1->long_value.ob_digit[size_w-1])
	if(denominator.digits[DIGIT_COUNT-1] == 0)
	{
		return DIGIT_SHIFT;
	}

	// __builtin_clzl() is available since GCC 3.4.
	return (int)sizeof(unsigned long) * 8 - __builtin_clzl(digit);
}


digit_t array_left_shift(digit_t* destination, digit_t* source, size_t size, int shift_amount)
/*
PROTOTYPE: `static digit v_lshift(digit *z, digit *a, Py_ssize_t m, int d)`
           `z` — Destination
           `a` — Source
           `m` — Array size
           `d` — shift_amount
DETAILS:
         Divide the bits into where they land across digits
         EG. Bits:     0 1 2 3 4 5 6 7 | 0 1 2 3 4 5 6 7 | 0 1 2 3 4 5 6 7
                       ----------------|-----------------|----------------
             Used as:  - - 0 1 2 3 4 5 | - - 0 1 2 3 4 5 | - - 0 1 2 3 4 5
             Shifted:  - - 3 4 5 0 1 2 | - - 3 4 5 0 1 2 | - - 3 4 5 0 x x
         Bits 0, 1, 2 are moved left of the split and 3, 4, 5 remain right of the split.
FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L1564
*/

{
	uint_t shifted_uint_t(this->_size);

	size_t right_bits_shift = shift_amount % DIGIT_SHIFT;  // shift of bits that will move/stay right of the digit split
	size_t left_bits_shift = DIGIT_SHIFT - right_bits_shift;  // shift of bits that will move left of the digit split
	size_t digit_shift = shift_amount / DIGIT_SHIFT;  // number of full digits a digit will move over

	size_t iterations = _size - digit_shift;
	for(size_t x = 0; x < iterations; x++)
	{
		destination[x+digit_shift] |= (source[x] << right_bits_shift) & MASK;  // move the bits that stay right
		destination[x+digit_shift+1] = source[x] >> left_bits_shift;
	}
	destination[iterations+digit_shift] |= source[iterations] >> left_bits_shift;

	return (source[_size-1] << shift_amount) & MASK;
}


// uint_t operator/(input_t right);
uint_t operator/(uint_t& numerator, uint_t& denominator)

/*
PROTOTYPE: `static PyLongObject* x_divrem(PyLongObject *v1, PyLongObject *w1, PyLongObject **prem)`
FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L2947
*/
{
	if(numerator == denominator)
	{
		return uint_t(1, 1);
	}
	else if(numerator < denominator)
	{
		return uint_t(1);
	}

	int d = DIGIT_SHIFT - bit_length(denominator.digits[DIGIT_COUNT-1])
}

// uint_t& operator/=(uint_t& left, input_t right);
// uint_t& operator/=(uint_t& left, uint_t& right);