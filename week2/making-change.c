#include <stdio.h>

void
make_change(int total, int *l, int *q, int *d, int *n)
/*
 * 'total' is an input parameter, which tells us the number of cents to
 *		make change for
 * l, q, d and n are output parameters (reference parameters), which are
 *		pointers to variables to return back the number of loonies, quarters,
 *		dimes and nickels
 */
{
	*l = total / 100;
	total -= *l * 100;	// subtract the value of the loonies
	*q = total / 25;
	total -= *q * 25;
	*d = total / 10;
	total -= *d * 10;
	*n = total / 5;
}

int
main(void)
{
	printf("Please enter a number of cents:\n");
	int total_cents;
	scanf("%d", &total_cents);
	int loonies, quarters, dimes, nickels;
	make_change(total_cents, &loonies, &quarters, &dimes, &nickels);
	printf("%d loonies, %d quarters, %d dimes, %d nickels\n",
		loonies, quarters, dimes, nickels);
	return 0;
}
