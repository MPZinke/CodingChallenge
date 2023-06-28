

all:
	g++ --std=c++17 uint_t/*.cpp -o Uint_tTest
# 	gcc --std=c11 -g Challenge.c -o Challenge


checker:
	gcc --std=c11 -g Testing/MathChecker.c -o MathChecker


multiply:
	gcc --std=c11 -g Testing/MultiplyTest.c -o MultiplyTest


add:
	gcc --std=c11 -g Testing/AddTest.c -o AddTest


div:
	gcc --std=c11 -g Testing/DivideTest.c -o DivideTest


sub:
	gcc --std=c11 -g Testing/SubtractTest.c -o SubtractTest


uint:
	g++ --std=c++17 uint_t/*.cpp -o Uint_tTest
