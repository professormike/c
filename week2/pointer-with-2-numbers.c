#include <stdio.h>

int
main(void)
{
	printf("Please enter 2 numbers\n");
	double x, y;
	scanf("%lf %lf", &x, &y);	// not checking if scanf succeeded
	printf("Would you like to change (1) x; or (2) y?\n");
	int choice;
	scanf("%d", &choice);		// not checking if scanf succeeded
	double *p;
	if (choice == 1) {
		p = &x;
	} else {
		p = &y;
	}
	*p = 0;		// this will either set x to 0 or y to 0
	printf("x=%lf\ty=%lf\tp=%p\n", x, y, p);
	printf("&x=%p\t&y=%p\t&p=%p\n", &x, &y, &p);
	return 0;
}
