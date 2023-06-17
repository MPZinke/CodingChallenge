

#include "uint_t.hpp"


int main()
{
	uint_t a(2, 0b11111111, 0b111);
	std::cout << a;

	uint_t b(2, 0b111, 0b111);
	std::cout << b;

	uint_t c = a - b;
	// uint_t a(4, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF, 0xFFFFFFFFFFFFFFFF);
	std::cout << c;
	uint_t d(3, 0, 0, 0);
	std::cout << d;

	return 0;
}
