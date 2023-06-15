

#include <stdarg.h>
#include <stdint.h>
#include <iostream>


#define DIGIT_SHIFT 30
#define DIGIT_MASK (((uint64_t)1 << DIGIT_SHIFT) - 1)

#define digit_t uint32_t
#define digit_t_size sizeof(digit_t)


static_assert(DIGIT_SHIFT < (digit_t_size * 8), "'DIGIT_SHIFT' must be less than the number of bits in 'digit_t_size'");


class uint_t
{
	public:
		uint_t(uint8_t bits, digit_t initial_value);
		uint_t(uint8_t bits, ...);
		~uint_t();

		friend std::ostream& operator<<(std::ostream& stream, uint_t& value);

	private:
		digit_t* _digits;
		const uint8_t _bits;  // number of digits
		uint8_t _size;  // number of digits
};


uint_t::uint_t(uint8_t bits, digit_t initial_value)
: _bits{bits}, _size{static_cast<uint8_t>(bits / DIGIT_SHIFT + (uint8_t)((bits % DIGIT_SHIFT) != 0))}
{
	std::cout << std::to_string(_size) << "1\n";
	_digits = new digit_t[_size];
	_digits[0] = initial_value;
	assert((_digits[0] >> DIGIT_SHIFT) == 0);  // Don't let me accidentally lost information

	for(uint8_t x = 1; x < _size; x++)
	{
		_digits[x] = 0;
	}
}


uint_t::uint_t(uint8_t bits, ...)
: _bits{bits}, _size{static_cast<uint8_t>(bits / DIGIT_SHIFT + (uint8_t)((bits % DIGIT_SHIFT) != 0))}
{
	std::cout << std::to_string(_size) << "2\n";
	_digits = new digit_t[_size];

	va_list variable_list;
	char* size_types = new char[_size+1];
	for(uint8_t x = 0; x < _size; x++)
	{
		size_types[x] = 'u';
	}

	va_start(variable_list, size_types);
	delete[] size_types;

	for(uint8_t x = 0; x < _size; x++)
	{
		_digits[x] = va_arg(variable_list, digit_t);
		assert((_digits[x] >> DIGIT_SHIFT) == 0);  // Don't let me accidentally lost information
	}
}


std::ostream& operator<<(std::ostream& stream, uint_t& value)
{
	stream << value._size << "\n";
	return stream;
}


uint_t::~uint_t()
{
	delete[] _digits;
}


int main()
{
	std::cout << "Hello\n";
	uint_t a(120, 0b0);
	std::cout << a;

	return 0;
}
