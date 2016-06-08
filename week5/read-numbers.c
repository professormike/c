#include <stdio.h>
#include <stdlib.h>

int
main(void)
{
	size_t num_numbers = 0;
	double *array = malloc(num_numbers * sizeof *array);
	double inputted_number;
	while (scanf("%lf", &inputted_number) == 1 && inputted_number >= 0) {
		array = realloc(array, ++num_numbers * sizeof *array);
		array[num_numbers - 1] = inputted_number;
	}
	for (size_t i = 0; i < num_numbers; i++) {
		printf("%lf\n", array[i]);
	}
	free(array);
	return 0;
}
