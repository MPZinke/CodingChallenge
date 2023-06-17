

#include <stdarg.h>
#include <stdint.h>
#include <iostream>


#define DIGIT_SHIFT 30
#define DIGIT_SUBSECTIONS 3
#define DIGIT_MASK (((uint64_t)1 << DIGIT_SHIFT) - 1)

#define input_t uint64_t
#define INPUT_T_SIZE sizeof(uint64_t)
#define INPUT_T_BITS (INPUT_T_SIZE * 8)
#define digit_t uint32_t
#define DIGIT_T_SIZE sizeof(digit_t)
#define DIGIT_T_BITS (DIGIT_T_SIZE * 8)


static_assert(DIGIT_SHIFT < DIGIT_T_BITS, "'DIGIT_SHIFT' must be less than the number of bits in 'DIGIT_T_SIZE'");
static_assert(INPUT_T_BITS >= DIGIT_T_BITS, "'INPUT_T_BITS' must be greater than or equal to 'DIGIT_T_BITS'");


class uint_t
{
	public:
		uint_t(uint64_t initial_value=0);
		uint_t(uint16_t bits, input_t initial_value1, input_t initial_value2, ...);
		~uint_t();
		uint_t(const uint_t& object);

		void resize(int additional_size=1);
		void size(uint8_t new_size);

		uint_t operator=(uint_t& right);
		uint_t operator+(input_t right);
		uint_t operator+=(input_t right);
		friend uint_t operator+(uint_t& left, uint_t& right);
		friend uint_t& operator+=(uint_t& left, uint_t& right);
		friend std::ostream& operator<<(std::ostream& stream, uint_t& value);

	private:
		digit_t* _digits;
		uint8_t _size = 1;  // number of digits
};


// —————————————————————————————————————————————————— CONSTRUCTORS —————————————————————————————————————————————————— //

uint_t::uint_t(input_t initial_value/*=0*/)
{
	for(uint8_t x = 1; x < (INPUT_T_BITS + DIGIT_SHIFT - 1) / DIGIT_SHIFT; x++)
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


uint_t::uint_t(uint16_t count, input_t initial_value1, input_t initial_value2, ...)
/*

*/
: _digits{nullptr}, _size{static_cast<uint8_t>(((INPUT_T_BITS * count) + DIGIT_SHIFT - 1) / DIGIT_SHIFT)}
{
	_digits = new digit_t[_size]();  // Zero initialization from: https://stackoverflow.com/a/2204380

	va_list variable_list;
	va_start(variable_list, "");

	std::vector<input_t> inputs = {initial_value1, initial_value2};
	for(uint8_t x = 2; x < count; x++)
	{
		inputs.push_back(va_arg(variable_list, input_t));
	}

	for(uint16_t bits_read = 0, x = 0; bits_read < INPUT_T_BITS * count && x < INPUT_T_BITS * count; x++)
	{
		int digit_index = bits_read / DIGIT_SHIFT;
		int digit_offset = bits_read % DIGIT_SHIFT;
		int input_index = bits_read / INPUT_T_BITS;
		int input_offset = bits_read % INPUT_T_BITS;

		int digit_remainder = DIGIT_SHIFT - digit_offset;
		int input_remainder = INPUT_T_BITS - input_offset;

		input_t number_of_bits_to_read = digit_remainder < input_remainder ? digit_remainder : input_remainder;
		input_t mask = ((1 << number_of_bits_to_read) - 1);
		input_t input_bits = (inputs[input_index] >> input_offset) & mask;
		input_t digit_bits = input_bits << digit_offset;
		_digits[digit_index] |= digit_bits;

		bits_read += number_of_bits_to_read;
	}
}


uint_t::uint_t(const uint_t& object)
/*
SUMMARY: Copy Constructor.
*/
: _size{object._size}
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
}


void uint_t::size(uint8_t new_size)
{
	resize((int)new_size - (int)_size);
}


// ——————————————————————————————————————————————————— OPERATORS  ——————————————————————————————————————————————————— //

uint_t uint_t::operator=(uint_t& right)
{
	_size = right._size;

	delete[] _digits;
	_digits = new digit_t[right._size];

	uint8_t x;
	for(uint8_t x = 0; x < _size; x++)
	{
		_digits[x] = right._digits[x];
	}

	return *this;
}


uint_t uint_t::operator+(input_t right)
{
	uint_t right_uint_t(right);
	return *this += right_uint_t;
}


uint_t operator+(uint_t& left, uint_t& right)
{
	uint_t& a = left._size > right._size ? left : right;
	uint_t& b = left._size > right._size ? right : left;

	uint_t result;
	result.size(a._size);
	uint64_t carry = 0;

	uint8_t x;
	for(x = 0; x < b._size; x++)
	{
		carry += a._digits[x] + b._digits[x];
		result._digits[x] = carry & DIGIT_MASK;
		carry = carry >> DIGIT_SHIFT;
	}
	for(; x < a._size; x++)
	{
		carry += a._digits[x];
		result._digits[x] = carry & DIGIT_MASK;
		carry = carry >> DIGIT_SHIFT;
	}

	if(carry != 0)
	{
		result.resize(1);
		result._digits[x] = carry;
	}

	return result;
}


uint_t& operator+=(uint_t& left, input_t right)
{
	uint_t right_uint_t(right);
	return left += right_uint_t;
}


uint_t& operator+=(uint_t& left, uint_t& right)
{
	uint_t& a = left._size > right._size ? left : right;
	uint_t& b = left._size > right._size ? right : left;


	digit_t* temp = new digit_t[a._size]();
	uint64_t carry = 0;

	uint8_t x;
	for(x = 0; x < b._size; x++)
	{
		carry += a._digits[x] + b._digits[x];
		temp[x] = carry & DIGIT_MASK;
		carry = carry >> DIGIT_SHIFT;
	}
	for(; x < a._size; x++)
	{
		carry += a._digits[x];
		temp[x] = carry & DIGIT_MASK;
		carry = carry >> DIGIT_SHIFT;
	}

	delete[] left._digits;
	left._digits = temp;

	if(carry != 0)
	{
		left.resize(1);
		left._digits[x] = carry;
	}

	return left;
}


std::ostream& operator<<(std::ostream& stream, uint_t& value)
{
	// char* base10_digits = new char[value._bits / 3];
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
	// stream << (int)value._size << std::endl;
	stream << std::endl;
	return stream;
}


uint_t::~uint_t()
{
	delete[] _digits;
}


int main()
{
	// uint_t + uint_t
	uint_t a(0b111111111111111111111111111111);
	std::cout << "a: " << a;
	uint_t b(1);
	std::cout << "b: " << b;
	uint_t c = a + b;
	std::cout << "a: " << a;
	std::cout << "c: " << c;

	// uint_t + uint64_t
	uint_t d = c + 16;
	std::cout << "d: " << d;

	// uint_t += uint_t
	uint_t e(0b1111111111111111111111111111111111111111111111111111111111111111);
	std::cout << "e: " << e;
	e += b;
	std::cout << "e: " << e;

	e = b;
	std::cout << "e: " << e;

	// uint_t += uint64_t
	// uint_t() + uint_t 
	// uint_t() + uint_t() 

	return 0;
}
