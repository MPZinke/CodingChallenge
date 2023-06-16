

#include <stdarg.h>
#include <stdint.h>
#include <iostream>


#define DIGIT_SHIFT 30
#define DIGIT_SUBSECTIONS 3
#define DIGIT_MASK (((uint64_t)1 << DIGIT_SHIFT) - 1)

#define input_t uint64_t
#define input_t_size sizeof(uint64_t)
#define input_t_bits (input_t_size * 8)
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
	uint8_t limit = (input_t_bits / DIGIT_SHIFT) + (uint8_t)(input_t_bits % DIGIT_SHIFT);
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


uint_t::uint_t(uint16_t bits, digit_t initial_value)
: _bits{bits}, _size{static_cast<uint8_t>(bits / DIGIT_SHIFT + (uint8_t)((bits % DIGIT_SHIFT) != 0))}
{
	_digits = new digit_t[_size];
	std::cout << "Initial value: " << initial_value << "\n";
	_digits[0] = initial_value;
	std::cout << "Digits[0]: " << _digits[0] << "\n";
	assert((_digits[0] >> DIGIT_SHIFT) == 0);  // Don't let me accidentally lost information

	for(uint8_t x = 1; x < _size; x++)
	{
		_digits[x] = 0;
	}
}


uint_t::uint_t(uint16_t bits, ...)
: _bits{bits}, _size{static_cast<uint8_t>(bits / DIGIT_SHIFT + (uint8_t)((bits % DIGIT_SHIFT) != 0))}
{
	_digits = new digit_t[_size];
	for(uint8_t x = 0; x < _size; x++)
	{
		_digits[x] = 0;
	}

	va_list variable_list;
	va_start(variable_list, _bits / input_t_bits + _bits % input_t_bits);

	uint64_t carry = 0;

	for(int written_bits = 0; written_bits < ???; written_bits += input_t_bits)
	{
		uint64_t next_value = va_arg(variable_list, input_t);
		int remaining_bits = input_t_bits;
		// For x in range(ceil(input_t_bits/ DIGIT_SHIFT))
		for(int x = 0; x < ((input_t_bits + DIGIT_SHIFT - 1) / DIGIT_SHIFT); x++)
		{
			int last_written_bit = written_bits % DIGIT_SHIFT;
			int last_read_bit = remaining_bits;
			int number_of_bits_to_read_from_input_and_write_to_digit = DIGIT_SHIFT - last_written_bit;
			int digit_index = written_bits / DIGIT_SHIFT;
			_digits[digit_index] |= next_value >> (???)
			remaining_bits -= number_of_bits_to_read_from_input_and_write_to_digit;
		}
	}


	for(int bits_read = 0; bits_read < ((bits + input_t_bits - 1) / input_t_bits); bits_read += input_t_bits)
	{
		
		for(int bits_written = 0; bits_written < )
	}


	for(uint8_t x = 0; x < _size; x++)
	{
		uint64_t value = 
		_digits[x] = va_arg(variable_list, digit_t);
		assert((_digits[x] >> DIGIT_SHIFT) == 0);  // Don't let me accidentally lost information
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
