#include <stdio.h>

int
main(void)
{
	double total = 0;
	double x;
	while (scanf("%lf", &x) == 1) {
		total += x;
	}
	printf("%lf\n", total);
	return 0;
}
