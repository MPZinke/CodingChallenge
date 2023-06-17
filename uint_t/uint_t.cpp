

#include "uint_t.hpp"



// —————————————————————————————————————————————————— CONSTRUCTORS —————————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

uint_t::uint_t(input_t initial_value/*=0*/)
{
	for(uint8_t x = 1/* 1 because default to 1 already set */; x < (INPUT_T_BITS + DIGIT_SHIFT - 1) / DIGIT_SHIFT; x++)
	{
		if((initial_value >> (DIGIT_SHIFT * x)) != 0)
		{
			_size = x+1;
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

	trim();
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


// ————————————————————————————————————————————————————— SIZING ————————————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

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


void uint_t::trim()
{
	uint8_t leading_zeros;
	for(leading_zeros = 0; leading_zeros < _size-1; leading_zeros++)
	{
		if(_digits[_size - leading_zeros - 1] != 0)
		{
			break;
		}
	}

	resize(-(int)leading_zeros);
}


// ——————————————————————————————————————————————————— OPERATORS  ——————————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

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
