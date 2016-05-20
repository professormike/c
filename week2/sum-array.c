#include <stdio.h>

double
sum_array(double *a, int n)
/*
 * 'a' is the pointer to the first element of an array
 * 'n' is the length of that array
 */
{
	double sum = 0;
	for (int i = 0; i < n; i++) {
		sum += a[i];
	}
	return sum;
}

int
main(void)
{
	double x[] = { 3, 9, -5.6, 18.3, 20 };
	printf("sum: %lf\n", sum_array(x, 5));
	return 0;
}
