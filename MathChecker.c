

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <float.h>


int main()
{
	long double a = 4750331086967809.0L;
	long double multiply = 27.0L;
	long double add = 20.0L;

	long double product = a * multiply;
	long double sum = product + add;

	printf("Size of double %ld\n", sizeof(__m256i));
	printf("Size of long double %ld\n", sizeof(__float128));
	printf("%Lf * %Lf = %Lf\n", a, multiply, product);  // Should 128_258_939_348_130_843.0000, but 128258939348130848.000000
	printf("%Lf + %Lf = %Lf\n", product, add, sum);

	return sum != 128258939348130863.0;
}
