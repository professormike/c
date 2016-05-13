#include <stdio.h>

int
main(void)
{
	int n;
	if (scanf("%d", &n) == 1) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				printf("*");
			}
			printf("\n");
		}
	} else {
		printf("That was not an integer\n");
		return 1;
	}
	return 0;
}
