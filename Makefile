

all:
	gcc --std=c11 -g Challenge.c -o Challenge


checker:
	gcc --std=c11 -g Testing/MathChecker.c -o MathChecker


multiply:
	gcc --std=c11 -g Testing/MultiplyTest.c -o MultiplyTest


add:
	gcc --std=c11 -g Testing/AddTest.c -o AddTest
