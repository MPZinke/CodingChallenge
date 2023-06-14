

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


uint20_t abs_add(uint20_t a, uint20_t b)
/*
FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L3352
*/
{
	uint20_t result = new_uint20_t(0, 0);
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


uint20_t abs_mul(uint20_t a, uint20_t b)
/*
FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L3588
*/
{
	uint20_t result = new_uint20_t_equaling_0();

	uint8_t carry = 0;
	for(uint16_t x = 0; x < DIGIT_COUNT * DIGIT_SHIFT; x++)
	{
		uint16_t a_digit = x / DIGIT_SHIFT, a_bit = x % DIGIT_SHIFT;  // 16 bit for x = 240 + y = 240
		uint32_t a_bit_value = (a.digits[a_digit] >> a_bit) & 0b1;

		uint20_t product = new_uint20_t_equaling_0();
		for(uint16_t y = 0; y < DIGIT_COUNT * DIGIT_SHIFT; y++)
		{
			uint16_t b_digit = y / DIGIT_SHIFT, b_bit = y % DIGIT_SHIFT;  // 16 bit for x = 240 + y = 240

			register uint32_t b_bit_value = (b.digits[b_digit] >> b_bit) & 0b1;
			register uint8_t bit_value = a_bit_value & b_bit_value ^ carry;
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


int main()
{
	uint20_t a = new_uint20_t(63, 0);
	uint20_t b = new_uint20_t(1, 0);

	uint20_t result = abs_mul(a, b);

	print(a);
	printf("\n");
	print(b);
	printf("\n");

	print(result);
	printf("\n");
}