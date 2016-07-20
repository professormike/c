#include "set.h"
#include <stdio.h>

int
main(void)
{
	void *set = empty_set();
#define ADD(x)	insert_element(set, x)
	ADD(3);
	ADD(-15);
	ADD(106);
	ADD(0);
	ADD(14);
#define CHECK(x)	printf("%d exists? %d\n", x, element_exists(set, x))
	CHECK(-15);
	CHECK(-16);
	free_set(set);
	return 0;
}
