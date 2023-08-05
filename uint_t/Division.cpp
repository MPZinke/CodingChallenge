

#include "uint_t.hpp"


uint_t uint_t::divide_by_digit(digit_t denominator)
/*
FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L2861
THEN: https://github.com/python/cpython/blob/a8ae73965b02302b7661ea07a6e4f955a961aca9/Objects/longobject.c#L1641
THEN: https://github.com/python/cpython/blob/a8ae73965b02302b7661ea07a6e4f955a961aca9/Objects/longobject.c#L1619
PROTOTYPE: `static PyLongObject* divrem1(PyLongObject *a, digit n, digit *prem)`
           `a` — Numerator
           `n` — Denominator
*/
{
	return uint_t();
	// if(_size == 1)
	// {
	// 	return uint_t(1, (*this)[0] / (*this)[0]);
	// }


	// digit_t remainder = 0;

    // assert(n > 0 && n <= DIGIT_MASK);
    // while (--size >= 0) {
    //     double_digit_t dividend;
    //     dividend = ((double_digit_t)remainder << DIGIT_SHIFT) | pin[size];
    //     digit quotient;
    //     quotient = (digit)(dividend / n);
    //     remainder = dividend % n;
    //     pout[size] = quotient;
    // }
    // return remainder;
}


uint_t uint_t::divide_by_uint_t(uint_t& denominator)
/*
FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L2873
      THEN: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L2947
PROTOTYPE: `static PyLongObject* x_divrem(PyLongObject *v1, PyLongObject *w1, PyLongObject **prem)`
           `v1` — Numerator
           `w1` — Denominator
*/
{
	int shift_amount = DIGIT_SHIFT - needed_bits(denominator[-1]);  // `d`
	uint_t denominator_shift = denominator << shift_amount;  // `w`
	uint_t numerator_shift = (*this) << shift_amount;  // `v`

	digit_t shift_overflow = (*this)[-1] >> (DIGIT_SHIFT - (shift_amount % DIGIT_SHIFT));
	if(shift_overflow != 0 || numerator_shift[-1] >= denominator_shift[-1]
	)
	{
		numerator_shift.resize(1);
		numerator_shift[-1] = shift_overflow;
	}

	// FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L2992
	// Denominator size is guaranteed to be > 1:
	//    https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L2872
	size_t delta = numerator_shift._size - denominator_shift._size;  // `k`
	assert(delta >= 0);
	uint_t result(delta);

	digit_t* numerator_digits = numerator_shift._digits;
	digit_t* denominator_digits = denominator_shift._digits;

	for(size_t iteration = 0; iteration < delta; iteration++)
	{
		digit_t* numerator_digit = numerator_shift._digits + (delta-iteration);
		digit_t* result_digit = result._digits + (delta-iteration);

		// FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L3018
		digit_t top_numerator_digit = numerator_digit[denominator_shift._size];
		assert(top_numerator_digit <= numerator_shift._digits[denominator_shift._size-1]);
		double_digit_t double_digit_top_numerator = ((double_digit_t)top_numerator_digit) << DIGIT_SHIFT;
		double_digit_top_numerator |= numerator_digits[denominator_shift._size-1];

		digit_t quotient = (digit_t)(double_digit_top_numerator / denominator_shift[-1]);
		digit_t remainder = (digit_t)(double_digit_top_numerator % denominator_shift[-1]);

		for(uint64_t x = 0; x < 0xFFFFFFFFFFFFFFFF; x++)
		{

			if(!(double_digit_t)denominator_shift[-2] * quotient >
			     (((double_digit_t)remainder << DIGIT_SHIFT) | [denominator_shift._size-2])
			   )
		}
	}
}


uint_t uint_t::operator/(input_t right)
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
		return this->divide_by_digit(numerator, denominator._digits[0]);
	}
	else
	{
		return this->divide_by_uint_t(numerator, denominator);
	}
}

// uint_t& operator/=(uint_t& left, input_t right);
// uint_t& operator/=(uint_t& left, uint_t& right);