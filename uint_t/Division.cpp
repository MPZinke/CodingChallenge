

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


digit_t array_left_shift(digit_t* destination, digit_t* source, size_t size, int d)
/*
PROTOTYPE: `static digit v_lshift(digit *z, digit *a, Py_ssize_t m, int d)`
           `z` — Destination
           `a` — Source
           `m` — Array size
           `d` — bits
FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L1564
*/
{
    Py_ssize_t i;
    digit carry = 0;

    assert(0 <= d && d < PyLong_SHIFT);
    for (i=0; i < m; i++) {
        twodigits acc = (twodigits)a[i] << d | carry;
        z[i] = (digit)acc & PyLong_MASK;
        carry = (digit)(acc >> PyLong_SHIFT);
    }
    return carry;
}
{
	digit_t carry = 0;
	for(size_t x = 0; x < size; x++)
	{
		double_digit_t 
	}

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