#include <stdio.h>

int
main(void)
{
	char a = 'h';
	int b = 5;
	long c = 10;
	printf("%zu %zu %zu\n", sizeof a, sizeof b, sizeof c);
	char *ap = &a;
	long *cp = &c;
	printf("%zu %zu\n", sizeof ap, sizeof cp);
	return 0;
}
