

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
#define double_digit_t uint64_t
#define DOUBLE_DIGIT_T_SIZE sizeof(double_digit_t)
#define INPUT_T_SIZE_TO_DIGIT_T_SIZE ((INPUT_T_BITS + DIGIT_SHIFT - 1) / DIGIT_SHIFT)
#define size_t uint8_t  // Limits the max number of digits to sizeof(uint8_t)


static_assert(DOUBLE_DIGIT_T_SIZE >= (DIGIT_T_SIZE * 2), "'double_digit_t' must be at least double the size of 'digit_t'");
static_assert(DIGIT_SHIFT < DIGIT_T_BITS, "'DIGIT_SHIFT' must be less than the number of bits in 'DIGIT_T_SIZE'");
static_assert(INPUT_T_BITS >= DIGIT_T_BITS, "'INPUT_T_BITS' must be greater than or equal to 'DIGIT_T_BITS'");


class uint_t
{
	public:
		uint_t(size_t count=1, uint64_t initial_value=0);
		uint_t(size_t count, input_t initial_value1, input_t initial_value2, ...);
		~uint_t();
		uint_t(const uint_t& object);

		// ——————————————————— DIGITS ——————————————————— //
		// —————————————————————————————————————————————— //
		void swap_digits(digit_t* new_digits, size_t new_digits_size);
		// ——————————————————— SIZING ——————————————————— //
		// —————————————————————————————————————————————— //
		uint64_t most_significant_bit();
		void resize(int additional_size=1);
		void size(size_t new_size);
		void trim();

		// ————————————————— OPERATORS —————————————————— //
		// —————————————————————————————————————————————— //
		uint_t operator=(uint_t& right);
		// —————————————————— ADDITION —————————————————— //
		uint_t operator+(input_t right);
		friend uint_t operator+(uint_t& left, uint_t& right);
		friend uint_t& operator+=(uint_t& left, input_t right);
		friend uint_t& operator+=(uint_t& left, uint_t& right);
		// ———————————————— SUBTRACTION  ———————————————— //
		uint_t operator-(input_t right);
		friend uint_t operator-(uint_t& left, uint_t& right);
		friend uint_t& operator-=(uint_t& left, input_t right);
		friend uint_t& operator-=(uint_t& left, uint_t& right);
		// ——————————————— MULTIPLICATION ——————————————— //
		uint_t operator*(input_t right);
		friend uint_t operator*(uint_t& left, uint_t& right);
		friend uint_t& operator*=(uint_t& left, input_t right);
		friend uint_t& operator*=(uint_t& left, uint_t& right);
		// —————————————————— DIVISION —————————————————— //
		uint_t operator/(input_t right);
		friend uint_t operator/(uint_t& left, uint_t& right);
		friend uint_t& operator/=(uint_t& left, input_t right);
		friend uint_t& operator/=(uint_t& left, uint_t& right);
		// —————————————————— MODULUS  —————————————————— //
		uint_t operator%(input_t right);
		friend uint_t operator%(uint_t& left, uint_t& right);
		friend uint_t& operator%=(uint_t& left, input_t right);
		friend uint_t& operator%=(uint_t& left, uint_t& right);
		// —————————————————— BOOLEAN  —————————————————— //
		bool operator>(input_t right);
		bool operator>(uint_t& right);
		bool operator>=(input_t right);
		bool operator>=(uint_t& right);
		bool operator<(input_t right);
		bool operator<(uint_t& right);
		bool operator<=(input_t right);
		bool operator<=(uint_t& right);
		bool operator==(input_t right);
		bool operator==(uint_t& right);

		friend std::ostream& operator<<(std::ostream& stream, uint_t& value);


	private:
		digit_t* _digits;
		size_t _size = 1;  // number of digits
};
