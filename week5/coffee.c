#include <stdio.h>
#include <stdlib.h>

enum coffee_size { SMALL, MEDIUM, LARGE };

struct coffee {
	enum coffee_size size;
	int num_sugars, num_creams;
};

struct coffee *
new_coffee(enum coffee_size size, int num_sugars, int creams)
{
	struct coffee *c = malloc(sizeof *c);
	c->size = size;
	c->num_sugars = num_sugars;
	c->num_creams = creams;
	return c;
}

double
price(struct coffee const *c)
{
	if (c->size == SMALL) {
		return 1.00;
	} else if (c->size == MEDIUM) {
		return 1.50;
	} else {
		return 2.00;
	}
}

double
calories(struct coffee const *c)
{
	return c->num_sugars * 16 + c->num_creams * 20;
}

int
main(void)
{
	printf("Enter size: (s)mall, (m)edium, (l)arge\n");
	char size_char;
	scanf("%c", &size_char);
	enum coffee_size size = size_char == 's' ? SMALL
		: size_char == 'm' ? MEDIUM : LARGE;
	printf("Enter number of sugars:\n");
	int sugars;
	scanf("%d", &sugars);
	printf("Enter number of creams:\n");
	int creams;
	scanf("%d", &creams);
	struct coffee *c = new_coffee(size, sugars, creams);
	printf("Price: $%.2lf\n", price(c));
	printf("Calories: %lf\n", calories(c));
	free(c);
	return 0;
}



