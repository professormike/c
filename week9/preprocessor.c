#include <stdio.h>

#define MIN(x,y)	((x) < (y) ? (x) : (y))

#define until(x)	while(!(x))

char
letter_grade(double numeric_grade)
{
#define GRADE(number, letter) if (numeric_grade > number) return letter
	GRADE(80, 'A');
	GRADE(70, 'B');
	GRADE(60, 'C');
	GRADE(50, 'D');
	GRADE(0, 'F');
#undef GRADE
}

int
main(void)
{
	int x = 5;
	int y = 1;
	until (x > 0) {
		y *= 2;
		x--;
	}
	return 0;
}
