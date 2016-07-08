#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

bool
linear_search(double const *haystack, size_t n, double needle)
/*
 * returns 'true' if needle exists in the array 'haystack' and 'false'
 * otherwise
 */
{
	for (size_t i = 0; i < n; i++) {
		if (haystack[i] == needle) {
			return true;
		}
	}
	return false;
}

#include "big-sorted-array.c"

int
main(int argc, char **argv)
{
//	double x[] = { 7, 0, 8.5, -14, 90, 100, 6 };
	long n = strtoul(argv[1], 0, 0);
	for (long i = 0; i < 1000000; i++) {
		printf("0 exists? %d\n",
			linear_search(x, n, 0));
		printf("1 exists? %d\n",
			linear_search(x, n, 1));
	}
	return 0;
}
