#include <stdio.h>

int
main(void)
{
	char x = 'a', y = 'b', z = 'c';
	char *p = &y;
	printf("%c\n", *p);
	p++;
	printf("%c\n", *p);
	return 0;
}
