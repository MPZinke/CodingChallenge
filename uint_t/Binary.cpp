

#include "uint_t.hpp"


uint_t uint_t::operator<<(input_t right)
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
	uint_t shifted(this->_size);
	if(this->_size * DIGIT_SHIFT <= right)
	{
		return shifted;
	}

	size_t right_bits_shift = right % DIGIT_SHIFT;  // shift of bits that will move/stay right of the digit split
	size_t left_bits_shift = DIGIT_SHIFT - right_bits_shift;  // shift of bits that will move left of the digit split
	size_t digit_shift = right / DIGIT_SHIFT;  // number of full digits a digit will move over

	size_t iterations = _size - digit_shift - 1;
	for(size_t x = 0; x < iterations; x++)
	{
		// Move the bits that stay right
		shifted._digits[x+digit_shift] |= (this->_digits[x] << right_bits_shift) & DIGIT_MASK;
		shifted._digits[x+digit_shift+1] = this->_digits[x] >> left_bits_shift;
	}

	shifted._digits[iterations+digit_shift] |= (this->_digits[iterations] << right_bits_shift) & DIGIT_MASK;

	return shifted;
}
