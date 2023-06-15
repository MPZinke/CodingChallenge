

#include <stdio.h>
#include <stdint.h>



#define DIGIT_COUNT 2  // The number of uint8_t "digits" a uint12_t has
#define DIGIT_SHIFT 6  // The number of bits of the uint8_t that are used
// FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Include/cpython/longintrepr.h#LL61C1-L61C1
#define DIGIT_MASK (((uint8_t)1 << DIGIT_SHIFT) - 1);


typedef struct
{
	uint8_t digits[DIGIT_COUNT];
} uint12_t;


typedef struct
{
	uint8_t digits[DIGIT_COUNT+1];
} uint24_t;


uint12_t new_uint12_t(uint8_t digit0, uint8_t digit1)
{
	uint12_t new_value = {digit0, digit1};
	return new_value;
}


uint12_t new_uint12_t_copy(uint12_t original)
{
	return new_uint12_t(original.digits[0], original.digits[1]);
}


uint12_t new_uint12_t_equaling_0()
{
	return new_uint12_t(0, 0);
}


void print(uint12_t value)
{
	for(uint8_t x = 1; x <= DIGIT_COUNT; x++)
	{
		for(uint8_t y = 1; y <= DIGIT_SHIFT; y++)
		{
			printf("%d", (value.digits[DIGIT_COUNT - x] >> (DIGIT_SHIFT - y)) & 0b1);
		}
		printf(" ");
	}
	printf("[%2hhu %2hhu] %u", value.digits[1], value.digits[0], (((uint16_t)value.digits[1]) << DIGIT_SHIFT) + value.digits[0]);
}


uint12_t abs_add(uint12_t a, uint12_t b)
/*
FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L3352
*/
{
	uint12_t result = new_uint12_t_equaling_0();
	uint64_t carry = 0;

	uint8_t x;
	for(x = 0; x < DIGIT_COUNT; x++)
	{
		carry += a.digits[x] + b.digits[x];
		result.digits[x] = carry & DIGIT_MASK;
		carry = carry >> DIGIT_SHIFT;
	}

	return result;
}


#define digit uint8_t
#define double_digit uint16_t
digit /* Type of digit */ vector_left_shift(digit* b, digit* a, int d)
/*
PROTOTYPE: `static digit v_lshift(digit *z, digit *a, Py_ssize_t m, int d)`
*/
{
	uint8_t x;
	digit carry = 0;

	assert(0 <= d && d < DIGIT_SHIFT);
	for(x = 0; x < DIGIT_COUNT; x++)
	{
		double_digit acc = (double_digit)a[i] << d | carry;
        b[i] = (digit)acc & DIGIT_MASK;
        carry = (digit)(acc >> DIGIT_SHIFT);
    }

    return carry;
}


uint12_t abs_div(uint12_t numerator, uint12_t denominator)
/*
PROTOTYPE: `static PyLongObject* x_divrem(PyLongObject *v1, PyLongObject *w1, PyLongObject **prem)`
FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L2947
*/
{
	int d;
	// FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L2981
	// PyLong_SHIFT - bit_length_digit(w1->long_value.ob_digit[size_w-1])
	if(denominator.digits[DIGIT_COUNT-1] != 0)
	{
        // __builtin_clzl() is available since GCC 3.4.
        d = DIGIT_SHIFT - (int)sizeof(unsigned long) * 8 - __builtin_clzl(denominator.digits[DIGIT_COUNT-1]);
    }
    else
    {
        d = DIGIT_SHIFT;
    }

	uint12_t denominator_copy = new_uint12_t_equaling_0();
	uint24_t numerator_copy = new_uint12_t_equaling_0();
	digit carry;
    carry = vector_left_shift(denominator_copy.digits, denominator.digits, d);
    assert(carry == 0);
    carry = vector_left_shift(numerator_copy.digits, numerator.digits, d);

	uint8_t numerator_copy_size = DIGIT_COUNT;
    if (carry != 0 || numerator_copy.digits[DIGIT_COUNT-1] >= denominator_copy.digits[DIGIT_COUNT-1])
    {
        numerator_copy.digits[DIGIT_COUNT] = carry;
        numerator_copy_size++;
    }

    int size_difference = numerator_copy_size - DIGIT_COUNT;
    assert(size_difference >= 0);
    
}


int main()
{
	uint12_t a = new_uint12_t(63, 0);
	uint12_t b = new_uint12_t(1, 0);

	uint12_t result = abs_mul(a, b);

	print(a);
	printf("\n");
	print(b);
	printf("\n");

	print(result);
	printf("\n");
}

