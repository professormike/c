#include <stdio.h>
#include <stdlib.h>

int
compare_ints(void const *first_number, void const *second_number)
/*
 * This is the comparison function we have to give to the qsort function
 * to sort an array of ints. 'first_number' and 'second_number' are pointers
 * to ints. Don't worry about what the word 'const' means until Friday
 */
{
	int const *first = first_number;
	int const *second = second_number;
	if (*first < *second) {
		return -1;
	} else if (*first == *second) {
		return 0;
	} else {
		return +1;
	}
}

int
main(void)
{
	int x[] = { 7, 9, -15, 35, 17, 14, 20, -3, 6 };
	qsort(x, sizeof x / sizeof *x, sizeof *x, &compare_ints);
	for (size_t i = 0; i < sizeof x / sizeof *x; i++) {
		printf("%d ", x[i]);
	}
	printf("\n");
	return 0;
}
