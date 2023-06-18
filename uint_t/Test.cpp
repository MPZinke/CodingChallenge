

#include "uint_t.hpp"


int main()
{
	// uint_t a(0b1000000000000000000000000000000000000000000000000000000000000000);
	uint_t a(4);
	std::cout << a;

	uint_t b(4);
	std::cout << b;

	uint_t c = a * b;
	std::cout << c;

	return 0;
}
