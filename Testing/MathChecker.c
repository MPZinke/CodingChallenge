

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <float.h>


#define DIGIT_COUNT 4  // The number of uint64_t "digits" a uint240_t has
#define DIGIT_SHIFT 60  // The number of bits of the uint64_t that are used
// FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Include/cpython/longintrepr.h#LL61C1-L61C1
#define DIGIT_MASK (((uint64_t)1 << DIGIT_SHIFT) - 1)


typedef struct
{
	uint64_t digits[DIGIT_COUNT];
} uint240_t;


uint240_t new_uint240_t(uint64_t digit0, uint64_t digit1, uint64_t digit2, uint64_t digit3)
{
	uint240_t new_value = {digit0, digit1, digit2, digit3};
	return new_value;
}


uint240_t new_uint240_t_equaling_0()
{
	return new_uint240_t(0, 0, 0, 0);
}


void print(uint240_t value)
{
	for(uint8_t x = 1; x <= DIGIT_COUNT; x++)
	{
		for(uint8_t y = 1; y <= DIGIT_SHIFT; y++)
		{
			printf("%hhu", (uint8_t)((value.digits[DIGIT_COUNT - x] >> (DIGIT_SHIFT - y)) & 0b1));
		}
		printf(" ");
	}
}


uint240_t abs_add(uint240_t a, uint240_t b)
/*
FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L3352
*/
{
	uint240_t result = new_uint240_t(0, 0, 0, 0);
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


uint240_t abs_sub(uint240_t a, uint240_t b)
/*
FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L3386
*/
{}


uint240_t abs_mul(uint240_t a, uint240_t b)
/*
FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L3588
*/
{
	uint240_t result = new_uint240_t_equaling_0();

	uint8_t carry = 0;
	for(uint16_t x = 0; x < DIGIT_COUNT * DIGIT_SHIFT; x++)
	{
		uint16_t a_digit = x / DIGIT_SHIFT, a_bit = x % DIGIT_SHIFT;  // 16 bit for x = 240 + y = 240
		uint64_t a_bit_value = (a.digits[a_digit] >> a_bit) & 0b1;

		uint240_t product = new_uint240_t_equaling_0();
		for(uint16_t y = 0; y < DIGIT_COUNT * DIGIT_SHIFT; y++)
		{
			uint16_t b_digit = y / DIGIT_SHIFT, b_bit = y % DIGIT_SHIFT;  // 16 bit for x = 240 + y = 240

			register uint64_t b_bit_value = (b.digits[b_digit] >> b_bit) & 0b1;
			register uint64_t bit_value = a_bit_value & b_bit_value ^ carry;
			carry = ((a_bit_value & b_bit_value + carry) & 0b10) >> 1;

			uint16_t product_digit = (y+x) / DIGIT_SHIFT, product_bit = (y+x) % DIGIT_SHIFT;
			if(DIGIT_COUNT <= product_digit || DIGIT_SHIFT <= product_bit)
			{
				break;
			}

			product.digits[product_digit] |= (bit_value << product_bit) & DIGIT_MASK;
		}

		result = abs_add(result, product);
	}

	return result;
}


void to_string(uint240_t a, char* string)
/*
PARAMS:  Takes 240-Bit integer to convert, the string to write to that can hold up to 9e74 number as a string (IE 75
         characters).
RETURNS: Writes the value to a char*.
*/
{
	uint8_t string_index;
	for(uint8_t x = 0, string_index = 0; x < DIGIT_COUNT; x++)
	{
		// for(ui)
	}
}


int main()
{
	uint240_t a = new_uint240_t(0x10E066A5011401, 0, 0, 0);
	// uint240_t a = new_uint240_t(7, 0, 0, 0);
	uint240_t b = new_uint240_t(2, 0, 0, 0);

	// uint240_t result = add(a, b);
	uint240_t result = abs_mul(a, b);

	print(a);
	printf("\n");
	print(b);
	printf("\n");

	print(result);
	printf("\n");

	printf("%llu\n", a.digits[0]);
	printf("%llu\n", b.digits[0]);
	printf("%llu %llu\n", result.digits[0], result.digits[1]);

	return 0;
}
