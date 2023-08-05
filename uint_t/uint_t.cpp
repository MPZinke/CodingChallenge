

#include "uint_t.hpp"



int highest_bit(digit_t digit)
/*
Gets the highest bit index by using __builtin_clzl and this gets the opposite.
__builtin_clzl: Gets the leading zeros.
*/
{
	// FROM: https://github.com/python/cpython/blob/d32e8d6070057eb7ad0eb2f9d9f1efab38b2cff4/Objects/longobject.c#L2981
	// PyLong_SHIFT - bit_length_digit(w1->long_value.ob_digit[size_w-1])
	if(digit == 0)
	{
		return DIGIT_SHIFT;
	}

	// __builtin_clzl() is available since GCC 3.4.
	return (int)DIGIT_T_BITS - __builtin_clzl(digit);
}


// —————————————————————————————————————————————————— CONSTRUCTORS —————————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

uint_t::uint_t(size_t size/*=1*/, input_t initial_value/*=0*/)
{
	// `INPUT_T_BITS - __builtin_clzl(initial_value)` is the highest bit for input_t input.
	size_t initial_value_size = (INPUT_T_BITS - __builtin_clzl(initial_value) + DIGIT_SHIFT - 1) / DIGIT_SHIFT;
	if(initial_value_size == 0)
	{
		initial_value_size = 1;
	}

	_size = (size < initial_value_size) ? initial_value_size : size;
	_digits = new digit_t[_size]();

	for(size_t x = 0; x < initial_value_size; x++)
	{
		_digits[x] = (initial_value >> (DIGIT_SHIFT * x)) & DIGIT_MASK;
	}
}


uint_t::uint_t(size_t count, input_t initial_value1, input_t initial_value2, ...)
/*
Zero initialization from: https://stackoverflow.com/a/2204380
*/
: _digits{new digit_t[static_cast<size_t>(((INPUT_T_BITS * count) + DIGIT_SHIFT - 1) / DIGIT_SHIFT)]()},
  _size{static_cast<size_t>(((INPUT_T_BITS * count) + DIGIT_SHIFT - 1) / DIGIT_SHIFT)}
{
	assert(count >= 2);  // Otherwise, we know I'm a "DAMN LIAR!"


	va_list variable_list;
	va_start(variable_list, "");

	std::vector<input_t> inputs = {initial_value1, initial_value2};
	for(size_t x = 2; x < count; x++)
	{
		inputs.push_back(va_arg(variable_list, input_t));
	}

	for(input_t bits_read = 0, x = 0; bits_read < INPUT_T_BITS * count && x < INPUT_T_BITS * count; x++)
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
	for(size_t x = 0; x < _size; x++)
	{
		_digits[x] = object._digits[x];
	}
}


// ————————————————————————————————————————————————————— DIGITS ————————————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

void uint_t::swap_digits(digit_t* new_digits, size_t new_digits_size)
{
	delete[] _digits;
	_digits = new_digits;
	_size = new_digits_size;
}


// ————————————————————————————————————————————————————— SIZING ————————————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

uint64_t uint_t::most_significant_bit()
{
	for(uint64_t bit_index = _size * DIGIT_SHIFT; bit_index > 0; bit_index--)
	{
		size_t digit_index = bit_index / DIGIT_SHIFT;
		size_t current_bit_index = bit_index % DIGIT_SHIFT;  // min:255; size_t ok: digits can't have more than 64 bits

		if((_digits[digit_index] >> current_bit_index) != 0)
		{
			return bit_index;
		}
	}

	return 0;
}


void uint_t::resize(int additional_size/*=1*/)
{
	assert((int)_size + additional_size <= sizeof(size_t) * 8);  // Ensure we don't overflow _size
	assert((int)_size + additional_size >= 0);  // Ensure we don't go negative

	int new_size = additional_size + (int)_size;

	digit_t* temp = new digit_t[_size+additional_size];
	size_t x, limit;
	for(x = 0, limit = additional_size < 0 ? new_size : _size; x < limit; x++)
	{
		temp[x] = _digits[x];
	}
	for(limit = new_size; x < limit; x++)
	{
		temp[x] = 0;
	}

	swap_digits(temp, (size_t)new_size);
}


void uint_t::size(size_t new_size)
{
	resize((int)new_size - (int)_size);
}


void uint_t::trim()
/*
Leaves at least 1 digit
*/
{
	size_t leading_zeros;
	for(leading_zeros = 0; leading_zeros < _size-1; leading_zeros++)
	{
		if(_digits[_size - leading_zeros - 1] != 0)
		{
			break;
		}
	}

	if(leading_zeros != 0)
	{
		resize(-(int)leading_zeros);
	}
}


// ——————————————————————————————————————————————————— OPERATORS  ——————————————————————————————————————————————————— //
// —————————————————————————————————————————————————————————————————————————————————————————————————————————————————— //

uint_t uint_t::operator=(uint_t& right)
{
	swap_digits(new digit_t[right._size], right._size);

	for(size_t x = 0; x < _size; x++)
	{
		_digits[x] = right._digits[x];
	}

	return *this;
}


digit_t uint_t::operator[](int index) const  // Getter
{
	if(index >= _size || (index < 0 && -index > _size))
	{
		exit(1);
	}
	if(index < 0)
	{
		index = _size + index;
	}

	return _digits[index];
}


digit_t& uint_t::operator[](int index)  // Setter
{
	if(index >= _size || (index < 0 && -index > _size))
	{
		exit(1);
	}
	if(index < 0)
	{
		index = _size + index;
	}

	return _digits[index];
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

	for(size_t x = 1; x <= value._size; x++)
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
