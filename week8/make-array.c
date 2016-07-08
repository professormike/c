#include <stdio.h>

int
main(void)
{
	printf("double x[] = {\n");
	for (int i = 0; i < 1000000; i++) {
		printf("%d,\n", i * 2);
	}
	printf("};\n");
	return 0;
}
