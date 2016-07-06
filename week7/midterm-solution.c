#include <stdio.h>
#include <stdlib.h>

struct factors {
	int two, three;
};

struct factors
factor(int n)
{
	struct factors r = { .two = 0, .three = 0 };
	while (n % 2 == 0) {
		r.two++;
		n /= 2;
	}
	while (n % 3 == 0) {
		r.three++;
		n /= 3;
	}
	return r;
}

struct factors
max_factors(int const *nums, size_t n)
{
	struct factors r = { .two = 0, .three = 0 };
	for (size_t i = 0; i < n; i++) {
		struct factors fi = factor(nums[i]);
		if (fi.two > r.two) {
			r.two = fi.two;
		}
		if (fi.three > r.three) {
			r.three = fi.three;
		}
	}
	return r;
}

int
main(void)
{
	size_t n = 0;
	int *arr = malloc(0 * sizeof *arr);
	int x;
	while (scanf("%d", &x) == 1 && x > 0) {
		arr = realloc(arr, ++n * sizeof *arr);
		arr[n - 1] = x;
	}
	struct factors f = max_factors(arr, n);
	free(arr);
	printf("The number of twos is %d\n", f.two);
	printf("The number of threes is %d\n", f.three);
	return 0;
}

