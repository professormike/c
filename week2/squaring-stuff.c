#include <stdio.h>

double
square1(double n)
{
	return n * n;
}

void
square2(double *n)
{
	*n *= *n;
}

int
main(void)
{
	double x;
	scanf("%lf", &x);
	printf("%lf\n", square1(x));
	square2(&x);
	printf("%lf\n", x);
	return 0;
}
