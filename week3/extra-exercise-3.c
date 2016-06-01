#include <stdio.h>
#include <stdlib.h>

int
compare_ints(void const *num1_, void const *num2_)
{
	int const *num1 = num1_;
	int const *num2 = num2_;
	return *num1 < *num2 ? -1 : *num1 > *num2 ? +1 : 0;
}

int
main(void)
{
	int array[9];
	for (size_t i = 0; i < sizeof array / sizeof *array; i++) {
		printf("Enter a number\n");
		scanf("%d", &array[i]);
	}
	qsort(array, sizeof array / sizeof *array, sizeof *array,
		&compare_ints);
	printf("The median is %d\n", array[sizeof array / sizeof *array / 2]);
	return 0;
}
