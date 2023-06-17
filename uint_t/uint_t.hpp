

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

		// ——————————————————— SIZING ——————————————————— //
		// —————————————————————————————————————————————— //
		void resize(int additional_size=1);
		void size(uint8_t new_size);
		void trim();

		// ————————————————— OPERATORS —————————————————— //
		// —————————————————————————————————————————————— //
		uint_t operator=(uint_t& right);
		// ——————————————— OPERATORS::ADD ——————————————— //
		uint_t operator+(input_t right);
		friend uint_t operator+(uint_t& left, uint_t& right);
		friend uint_t& operator+=(uint_t& left, input_t right);
		friend uint_t& operator+=(uint_t& left, uint_t& right);
		// ———————————— OPERATORS::SUBTRACT  ———————————— //
		uint_t operator-(input_t right);
		friend uint_t operator-(uint_t& left, uint_t& right);
		friend uint_t& operator-=(uint_t& left, input_t right);
		friend uint_t& operator-=(uint_t& left, uint_t& right);

		friend std::ostream& operator<<(std::ostream& stream, uint_t& value);

	private:
		digit_t* _digits;
		uint8_t _size = 1;  // number of digits
};
