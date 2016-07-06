#include <stdio.h>

void
selection_sort(int *arr, size_t n)
{
	for (size_t j = 0; j < n - 1; j++) {
		int first_element = arr[j];
		// find the smallest element in the array
		int *smallest = &arr[j];
		for (size_t i = j; i < n; i++) {
			if (arr[i] < *smallest) {
				smallest = &arr[i];
			}
		}
		// swap the smallest element with the first element
		arr[j] = *smallest;
		*smallest = first_element;
	}
}

#include "big-array.c"

int
main(void)
{
	//int x[] = { 9, 0, -5, 6, 18, 20, 11, -3, 7 };
	selection_sort(x, sizeof x / sizeof *x);
	for (size_t i = 0; i < sizeof x / sizeof *x; i++) {
		printf("%d ", x[i]);
	}
	printf("\n");
	return 0;
}
