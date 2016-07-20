#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int
main(void)
{
	srand(time(0));
	while (1) {
		printf("%d\n", rand());
	}
}
