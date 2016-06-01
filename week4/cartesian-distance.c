#include <stdio.h>
#include <math.h>

struct point {
	double x, y;
};

double
distance(struct point const *p1, struct point const *p2)
{
	return sqrt(pow(p1->x - p2->x, 2) + pow(p1->y - p2->y, 2));
}

int
main(void)
{
	struct point p[2];
	for (size_t i = 0; i < sizeof p / sizeof *p; i++) {
		printf("Enter x and y coordinates for point %zu\n", i);
		scanf("%lf %lf", &p[i].x, &p[i].y);
	}
	printf("The distance between them is %lf\n", distance(&p[0], &p[1]));
	return 0;
}
