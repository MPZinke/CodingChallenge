

#include <stdio.h>
#include <stdint.h>


#define DIGIT_COUNT 2  // The number of uint8_t "digits" a uint20_t has
#define DIGIT_SHIFT 6  // The number of bits of the uint8_t that are used
// FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Include/cpython/longintrepr.h#LL61C1-L61C1
#define DIGIT_MASK (((uint8_t)1 << DIGIT_SHIFT) - 1);


typedef struct
{
	uint8_t digits[DIGIT_COUNT];
} uint20_t;


uint20_t new_uint20_t(uint8_t digit0, uint8_t digit1)
{
	uint20_t new_value = {digit0, digit1};
	return new_value;
}


uint20_t new_uint20_t_equaling_0()
{
	return new_uint20_t(0, 0);
}


void print(uint20_t value)
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


uint20_t abs_sub(uint20_t a, uint20_t b)
/*
FROM: https://github.com/python/cpython/blob/12b6d844d8819955508bd86db106f17516be3f77/Objects/longobject.c#L3421
*/
{
	uint20_t result = new_uint20_t(0, 0);
	uint64_t borrow = 0;

	uint8_t x;
	for(x = 0; x < DIGIT_COUNT; x++)
	{
		borrow = a.digits[x] - b.digits[x] - borrow;
		result.digits[x] = borrow & DIGIT_MASK;
		borrow = borrow >> DIGIT_SHIFT;
		borrow = borrow & 1;
	}

	return result;
}


int main()
{
	// uint20_t a = new_uint20_t(63, 61);
	uint20_t a = new_uint20_t(5, 0);
	uint20_t b = new_uint20_t(63, 0);

	uint20_t result = abs_sub(a, b);

	print(a);
	printf("\n");
	print(b);
	printf("\n");

	print(result);
	printf("\n");
}