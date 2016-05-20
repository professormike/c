#include <stdio.h>

int
main(void)
{
	char x[] = "hello";
	char *y = "hello";
	x[0] = 'j';
	y[0] = 'j';	// this will fail because y is pointing to a read-only
				// section of memory
	printf("%s %s\n", x, y);
	return 0;
}
