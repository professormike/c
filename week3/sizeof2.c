#include <stdio.h>

int
main(void)
{
	int x[] = { 2, 3, 4 };
	printf("%zu\n", sizeof x);
	printf("%zu\n", sizeof *x);
	printf("%zu\n", sizeof x / sizeof *x);
	// above is the number of elements in x
	return 0;
}
