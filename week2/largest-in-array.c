#include <stdio.h>

int
main(void)
{
	// read in 5 integers from the user and store them in an array
	int x[5];
	for (int i = 0; i < 5; i++) {
		if (scanf("%d", &x[i]) != 1) {
			fprintf(stderr, "That was not an integer\n");
			return 1;
		}
	}

	// find the largest number in the array and print it out
	int largest = x[0];
	for (int i = 0; i < 5; i++) {
		if (x[i] > largest) {
			largest = x[i];
		}
	}
	printf("largest is %d\n", largest);
	return 0;
}
