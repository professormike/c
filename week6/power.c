#include <stdio.h>

int
power(int x, int y)
/* returns x to the power of y */
{
	if (y == 0) {
		return 1;
	} else if (y % 2 == 1) {	// odd exponent
		return x * power(x, y - 1);
	} else {		// even exponent
		int z = power(x, y / 2);
		return z * z;
	}
}

int
main(void)
{
	printf("%d\n", power(2, 4));	// should print 16
	printf("%d\n", power(3, 3));	// should print 27
	printf("%d\n", power(7, 0));	// should print 1
	printf("%d\n", power(2, 16));	// should print 65536
	return 0;
}
