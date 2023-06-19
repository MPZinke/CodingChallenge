

#include "uint_t.hpp"


// uint_t operator/(input_t right);
uint_t operator/(uint_t& left, uint_t& right)
{
	if(left == right)
	{
		return uint_t(1);
	}
	else if(left < right)
	{
		return uint_t(0);
	}
}

// uint_t& operator/=(uint_t& left, input_t right);
// uint_t& operator/=(uint_t& left, uint_t& right);