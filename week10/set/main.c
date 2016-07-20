#include "set.h"
#include <stdio.h>

int
main(int argc, char **argv)
// argc = number of command-line arguments
// argv = array of strings, which hold the actual command-line arguments
// argv[0] is the name of the executable, so actual command-line arguments
//	start at argv[1]
{
	void *set = empty_set();

	// open the file indicated by the first command-line argument, read in
	// all numbers, and add them to our set
	FILE *f = fopen(argv[1], "r");
	long long x;
	while (fscanf(f, "%lld ", &x) == 1) {
		insert_element(set, x);
	}
	fclose(f);

	// open the second file, and check to see if those numbers are in
	// our set
	f = fopen(argv[2], "r");
	while (fscanf(f, "%lld ", &x) == 1) {
		if (element_exists(set, x)) {
			printf("exists\n");
		} else {
			printf("does not exist\n");
		}
	}
	fclose(f);

	free_set(set);
	return 0;
}
