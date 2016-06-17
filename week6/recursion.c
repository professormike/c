#include <stdio.h>

int
foo(int x)
{
	if (x < 3) {
		return x * 2;
	} else {
		return foo(x - 1) + foo(x / 2) + 1;
	}
}

int
main(void)
{
	printf("%d\n", foo(8));
	return 0;
}
