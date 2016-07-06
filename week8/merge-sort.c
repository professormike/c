#include <stdio.h>
#include <string.h>	// for memcpy

void
merge(int const *inp1, size_t n1, int const *inp2, size_t n2, int *out)
{
	size_t i1 = 0;
	size_t i2 = 0;
	for (size_t i = 0; i < n1 + n2; i++) {
		// if i2 has gone beyond the end of inp2, take from inp1
		// if i1 has gone beyond the end of inp1, take from inp2
		// otherwise, take whichever has the smaller value
		if (i2 >= n2 || (i1 < n1 && inp1[i1] < inp2[i2])) {
			out[i] = inp1[i1];
			i1++;
		} else {
			out[i] = inp2[i2];
			i2++;
		}
	}
}

void
merge_sort(int *arr, size_t n)
{
	if (n <= 1) {
		// do nothing
	} else {
		// divide the array into 2 halves
		int *first_half = &arr[0];
		size_t first_len = n / 2;
		int *second_half = &arr[first_len];
		size_t second_len = n - first_len;
		int first_half_temp[first_len];
		int second_half_temp[second_len];
		memcpy(first_half_temp, first_half, first_len * sizeof *first_half);
		memcpy(second_half_temp, second_half,
			second_len * sizeof *second_half);

		// sort the 2 halves
		merge_sort(first_half_temp, first_len);
		merge_sort(second_half_temp, second_len);
		// merge the 2 halves back together
		merge(first_half_temp, first_len, second_half_temp, second_len, arr);
	}
}

#include "big-array.c"

int
main(void)
{
//	int x[] = { 9, 0, -5, 6, 18, 20, 11, -3, 7 };
	merge_sort(x, sizeof x / sizeof *x);
	for (size_t i = 0; i < sizeof x / sizeof *x; i++) {
		printf("%d ", x[i]);
	}
	printf("\n");
	return 0;
}
