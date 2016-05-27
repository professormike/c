#include <stdio.h>
#include <stdbool.h>

bool
all_positive(void *x, size_t n, size_t element_size,
bool (*positive)(void *))
/*
 * 'x' is a pointer to the beginning of the array. It's void *
 *		(remember that void * is a 'pointer to anything') because we
 *		don't know the type of the elements in the array
 * 'n' is the number of the elements in the array
 * 'element_size' is the size (as measured in bytes) of one element
 *		in the array
 * 'positive' is a pointer to a function which tells us whether a
 *		given element is positive or not. Its return type is bool and
 *		it has one parameter, which is a void *, which will be a
 *		pointer to one element in the array
 * Returns true if every element in the array is considered positive.
 * Returns false if at least one element in the array is considered
 *		negative.
 */
{
	for (size_t i = 0; i < n; i++) {
		// each element is 'element_size' bytes in size, so to determine
		// where element 'i' begins, we multiply the 2 numbers together
		size_t element_start = i * element_size;
		// the below line of code will give a warning, saying that you
		// shouldn't use [] notation with void * variables, but that's
		// okay. Just ignore it
		if (!(*positive)(&x[element_start])) {	// checking if x[i] is < 0
			return false;
		}
	}
	return true;
}

bool int_positive(void *x) { int *real_x = x; return *real_x >= 0; }
bool double_positive(void *x) { double *real_x = x; return *real_x >= 0; }

int
main(void)
{
	int x[] = { 4, 8, 19, -5, 6, 2 },
		y[] = { 7, 1, 0, 14, 35 };
	double z[] = { 5.5, -6.5, 19.5 };
	printf("%d\n", all_positive(x, sizeof x / sizeof *x, sizeof *x,
		&int_positive));
	printf("%d\n", all_positive(y, sizeof y / sizeof *y, sizeof *y,
		&int_positive));
	printf("%d\n", all_positive(z, sizeof z / sizeof *z, sizeof *z,
		&double_positive));
	return 0;
}

