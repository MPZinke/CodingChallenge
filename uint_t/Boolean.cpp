

#include "uint_t.hpp"


bool uint_t::operator>(input_t right)
{
	uint_t right_uint_t(right);
	return *this > right_uint_t;
}


bool uint_t::operator>(uint_t& right)
{
	if(_size == right._size)
	{
		return _digits[_size-1] > right._digits[_size-1];
	}

	return _size > right._size;
}


bool uint_t::operator<(input_t right)
{
	uint_t right_uint_t(right);
	return *this < right_uint_t;
}


bool uint_t::operator<(uint_t& right)
{
	if(_size == right._size)
	{
		return _digits[_size-1] < right._digits[_size-1];
	}

	return _size < right._size;
}


bool uint_t::operator==(input_t right)
{
	uint_t right_uint_t(right);
	return *this == right_uint_t;
}


bool uint_t::operator==(uint_t& right)
{
	if(_size == right._size)
	{
		return _digits[_size-1] == right._digits[_size-1];
	}

	return _size == right._size;
}
