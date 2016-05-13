#include <stdio.h>

int
main(void)
{
	int x, y;
	if (scanf("%d %d", &x, &y) == 2) {
		for (int i = x; i <= y; i++) {
			if (i % 2 == 0) {
				printf("%d\n", i);
			}
		}
	} else {
		printf("Your input was bad\n");
		return 1;
	}
	return 0;
}
