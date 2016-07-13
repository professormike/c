#include <stdio.h>
#include <math.h>

double
f(double x)
{
	return sqrt(x);
}

int
main(void)
{
	printf("%lf\n", f(2));
	return 0;
}
