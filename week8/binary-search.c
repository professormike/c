#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool
binary_search(double const *haystack, size_t n, double needle)
/*
 * 'haystack' is an array of SORTED ELEMENTS. We repeatedly cut the array
 * in half to search for the 'needle'
 */
{
	if (n == 1) {
		return haystack[0] == needle;
	} else {
		size_t midpoint = n / 2;
		if (haystack[midpoint] <= needle) {
			return binary_search(&haystack[midpoint], n - midpoint,
				needle);
		} else {
			return binary_search(&haystack[0], midpoint, needle);
		}
	}
}

#include "big-sorted-array.c"

int
main(int argc, char **argv)
{
//	double x[] = { -14, 0, 3, 6, 9, 90, 100 };
	size_t n = strtoul(argv[1], 0, 0);
	for (long i = 0; i < 1000000; i++) {
		printf("0 exists? %d\n",
			binary_search(x, n, 0));
		printf("1 exists? %d\n",
			binary_search(x, n, 1));
	}
	return 0;
}
