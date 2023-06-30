

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


uint_t divide_by_digit(uint_t& numerator, digit_t denominator)
/*
FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L2861
THEN: https://github.com/python/cpython/blob/a8ae73965b02302b7661ea07a6e4f955a961aca9/Objects/longobject.c#L1641
THEN: https://github.com/python/cpython/blob/a8ae73965b02302b7661ea07a6e4f955a961aca9/Objects/longobject.c#L1619
PROTOTYPE: `static PyLongObject* divrem1(PyLongObject *a, digit n, digit *prem)`
           `a` — Numerator
           `n` — Denominator
*/
{
	if(numerator._size == 1)
	{
		return uint_t(1, numerator._digits[0] / numerator._digits[0]);
	}


	digit remainder = 0;

    assert(n > 0 && n <= PyLong_MASK);
    while (--size >= 0) {
        twodigits dividend;
        dividend = ((twodigits)remainder << PyLong_SHIFT) | pin[size];
        digit quotient;
        quotient = (digit)(dividend / n);
        remainder = dividend % n;
        pout[size] = quotient;
    }
    return remainder;
}


uint_t divide_by_uint_t(uint_t& numerator, uint_t& denominator)
/*
FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L2873
THEN: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L2947
PROTOTYPE: `static PyLongObject* x_divrem(PyLongObject *v1, PyLongObject *w1, PyLongObject **prem)`
           `v1` — Numerator
           `w1` — Denominator
*/
{
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

	// FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L2992
	// Denominator size is guaranteed to be > 1:
	//    https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L2872
	size_t delta = numerator_shift._size - denominator_shift._size;
	assert(delta >= 0);
	uint_t 

}


uint_t operator/(input_t right)
{
	uint_t right_uint_t(1, right);
	return *this / right_uint_t;
}


uint_t operator/(uint_t& numerator, uint_t& denominator)

/*
FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L2838
PROTOTYPE: `static int long_divrem(PyLongObject *a, PyLongObject *b, PyLongObject **pdiv, PyLongObject **prem)`
           `a` — Numerator
           `b` — Denominator
           `prem` — Remainder destination
*/
{
	// Trivial conditions
	if(numerator == denominator)
	{
		return uint_t(1, 1);
	}
	else if(numerator < denominator)
	{
		return uint_t(1, 0);
	}

	if(denominator._size == 1)
	{
		return divide_by_digit(numerator, denominator._digits[0]);
	}
	else
	{
		return divide_by_uint_t(numerator, denominator);
	}
}

// uint_t& operator/=(uint_t& left, input_t right);
// uint_t& operator/=(uint_t& left, uint_t& right);