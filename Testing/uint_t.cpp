

#include <stdarg.h>
#include <stdint.h>
#include <iostream>


#define DIGIT_SHIFT 30
#define DIGIT_SUBSECTIONS 3
#define DIGIT_MASK (((uint64_t)1 << DIGIT_SHIFT) - 1)

#define input_t uint64_t
#define input_t_size sizeof(uint64_t)
#define INPUT_T_BITS (input_t_size * 8)
#define digit_t uint32_t
#define digit_t_size sizeof(digit_t)
#define digit_t_bits (digit_t_size * 8)


static_assert(DIGIT_SHIFT < (digit_t_size * 8), "'DIGIT_SHIFT' must be less than the number of bits in 'digit_t_size'");


class uint_t
{
	public:
		uint_t(uint64_t initial_value);
		uint_t(uint16_t bits, ...);
		~uint_t();
		uint_t(const uint_t& object);

		void resize(int additional_size=1);

		uint_t operator=(uint_t& right);
		uint_t operator+(uint32_t right);
		friend uint_t operator+(uint_t& left, uint_t& right);
		friend std::ostream& operator<<(std::ostream& stream, uint_t& value);

	private:
		digit_t* _digits;
		uint16_t _bits;  // number of bits
		uint8_t _size;  // number of digits
};


// —————————————————————————————————————————————————— CONSTRUCTORS —————————————————————————————————————————————————— //

uint_t::uint_t(input_t initial_value)
{
	uint8_t limit = (INPUT_T_BITS / DIGIT_SHIFT) + (uint8_t)(INPUT_T_BITS % DIGIT_SHIFT);
	for(uint8_t x = 0; x < limit; x++)
	{
		if((initial_value >> DIGIT_SHIFT) != 0)
		{
			_size = x;
		}
	}

	_digits = new digit_t[_size];
	for(uint8_t x = 0; x < _size; x++)
	{
		_digits[x] = (initial_value >> (DIGIT_SHIFT * x)) & DIGIT_MASK;
	}
}


uint_t::uint_t(uint16_t count, ...)
/*

*/
// Zero initialization from: https://stackoverflow.com/a/2204380
: _digits{new digit_t[_size]()} _size{static_cast<uint8_t>(((INPUT_T_BITS * count) + DIGIT_SHIFT - 1) / DIGIT_SHIFT)}
{
	va_list variable_list;
	va_start(variable_list, count);

	for(int ints_read = 0, bits_read = 0; ints_read < count; ints_read++)
	{
		uint64_t next_value = va_arg(variable_list, input_t);

		int digit_remainder = DIGIT_SHIFT - (bits_read % DIGIT_SHIFT);
		int int_remainder = INPUT_T_BITS - (bits_read % INPUT_T_BITS);

		// Determine number of "pigeon holes" input goes into based on remainder of digit
		int iterations = (INPUT_T_BITS / DIGIT_SHIFT) + (int)(digit_remainder < (INPUT_T_BITS % DIGIT_SHIFT))
		  + (int)((INPUT_T_BITS % DIGIT_SHIFT) != 0);

		for(uint8_t x = 0; x < iterations; x++)
		{
			int bits_to_read = digit_remainder < int_remainder ? digit_remainder : int_remainder;

			int digit_index = bits_read / DIGIT_SHIFT;
			int digit_offset = bits_read % DIGIT_SHIFT;

			int int_offset = bits_read % INPUT_T_BITS;
			// TODO: shift int bits to match digit place and mask
			uint64_t mask = (1 << bits_to_read) - 1;

			bits_read += bits_to_read;
			digit_remainder = DIGIT_SHIFT - (bits_read % DIGIT_SHIFT)
			int_remainder = INPUT_T_BITS - (bits_read % INPUT_T_BITS)
		}
	}
}


uint_t::uint_t(const uint_t& object)
/*
SUMMARY: Copy Constructor.
*/
: _bits{object._bits}, _size{object._size}
{
	_digits = new digit_t[_size];
	for(uint8_t x = 0; x < _size; x++)
	{
		_digits[x] = object._digits[x];
	}
}


// ——————————————————————————————————————————————————— OPERATORS  ——————————————————————————————————————————————————— //

void uint_t::resize(int additional_size/*=1*/)
{
	assert((int)_size + additional_size <= sizeof(uint8_t) * 8);  // Ensure we don't overflow _size
	assert((int)_size + additional_size >= 0);  // Ensure we don't go negative

	int new_size = additional_size + (int)_size;

	digit_t* temp = new digit_t[_size+additional_size];
	uint8_t x, limit;
	for(x = 0, limit = additional_size < 0 ? new_size : _size; x < limit; x++)
	{
		temp[x] = _digits[x];
	}
	for(limit = new_size; x < limit; x++)
	{
		temp[x] = 0;
	}

	delete[] _digits;
	_digits = temp;
	_size = (uint8_t)new_size;
	_bits = (uint16_t)DIGIT_SHIFT * (uint16_t)_size;
}


// ——————————————————————————————————————————————————— OPERATORS  ——————————————————————————————————————————————————— //

uint_t uint_t::operator=(uint_t& right)
{
	assert(_size >= right._size);

	uint8_t x;
	for(x = 0; x < right._size; x++)
	{
		_digits[x] = right._digits[x];
	}
	for(; x < _size; x++)
	{
		_digits[x] = 0;
	}

	return *this;
}


uint_t uint_t::operator+(uint32_t right)
{
	if((right >> DIGIT_SHIFT) == 0)
	{
		uint_t right_uint_t(30, right);
		return *this + right_uint_t;
	}
	else
	{
		uint_t right_uint_t(32, right & DIGIT_MASK, right >> DIGIT_SHIFT);
		return *this + right_uint_t;
	}
}


// uint_t uint_t::operator+=(uint32_t right)
// {
// 	if((right >> DIGIT_SHIFT) == 0)
// 	{
// 		uint_t result(30, )
// 	}
// 	else
// 	{
// 		return *this + uint_t(32, right & DIGIT_MASK, right >> DIGIT_SHIFT);
// 	}
// }


uint_t operator+(uint_t& left, uint_t& right)
{
	uint_t& a = left._size > right._size ? left : right;
	uint_t& b = left._size > right._size ? right : left;

	uint_t result(a._size, 0);
	uint64_t carry = 0;

	uint8_t x;
	for(x = 0; x < b._size; x++)
	{
		carry += a._digits[x] + b._digits[x];
		result._digits[x] = carry & DIGIT_MASK;
		carry = carry >> DIGIT_SHIFT;
	}
	for(x = 0; x < a._size; x++)
	{
		carry += a._digits[x];
		result._digits[x] = carry & DIGIT_MASK;
		carry = carry >> DIGIT_SHIFT;
	}

	if(carry != 0)
	{
		// Resize for carry
		result.resize();
		result._digits[x] = carry;
	}

	return result;
}


std::ostream& operator<<(std::ostream& stream, uint_t& value)
{
	char* base10_digits = new char[value._bits / 3];
	// digit_t current_base = 0;

	// uint8_t x;
	// for(x = 0; x < _bits / (DIGIT_SHIFT / DIGIT_SUBSECTIONS); x++)
	// {

	// 	uint8_t digit = x / DIGIT_SUBSECTIONS;
	// 	uint8_t shift = x % DIGIT_SUBSECTIONS;
	// 	current_base = (current_base >> (x / DIGIT_SUBSECTIONS)) | ;
	// }

	for(uint8_t x = 1; x <= value._size; x++)
	{
		for(uint8_t y = 1; y <= DIGIT_SHIFT; y++)
		{
			stream << ((value._digits[value._size-x] >> (DIGIT_SHIFT - y)) & 0b1);
		}
		stream << " ";
	}
	stream << std::endl;
	return stream;
}


uint_t::~uint_t()
{
	delete[] _digits;
}


int main()
{
	std::cout << "Hello\n";
	uint_t a(120, 14);
	std::cout << a;

	uint_t b = a + 2;
	std::cout << b;

	uint_t c()
	std::cout

	return 0;
}
