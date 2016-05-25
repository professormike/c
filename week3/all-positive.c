#include <stdio.h>
#include <stdbool.h>

bool
all_positive(intordouble *array, size_t n, bool (*positive)(intordouble))
{
	for (size_t i = 0; i < n; i++) {
		if (!(*positive)(x[i])) {	// checking if x[i] is < 0
			return false;
		}
	}
	return true;
}

bool int_positive(int x) { return x > 0; }
bool double_positive(double x) { return x > 0; }

int
main(void)
{
	int x[] = { 4, 8, 19, -5, 6, 2 },
		y[] = { 7, 1, 0, 14, 35 };
	double z[] = { 5.5, -6.5, 19.5 };
	printf("%d\n", all_positive(x, sizeof x / sizeof *x, &int_positive));
	printf("%d\n", all_positive(y, sizeof y / sizeof *y, &int_positive));
	printf("%d\n", all_positive(z, sizeof z / sizeof *z, &double_positive));
	return 0;
}

