

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


uint12_t new_uint12_t(uint8_t digit0, uint8_t digit1)
{
	uint12_t new_value = {digit0, digit1};
	return new_value;
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
	uint12_t result = new_uint12_t(0, 0);
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


int main()
{
	uint12_t a = new_uint12_t(63, 61);
	uint12_t b = new_uint12_t(2, 0);

	uint12_t result = abs_add(a, b);

	print(a);
	printf("\n");
	print(b);
	printf("\n");

	print(result);
	printf("\n");
}