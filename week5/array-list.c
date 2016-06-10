#include <stdio.h>
#include <stdlib.h>

struct array_list {
	double *array;
	size_t num_elements;
};

void add_to_end(struct array_list *list, double new_value) {
	list->array = realloc(list->array, ++list->num_elements
		* sizeof *list->array);
	list->array[list->num_elements - 1] = new_value;
}

void add_at_position(struct array_list *list, size_t p, double new_value) {
	list->array = realloc(list->array, ++list->num_elements
		* sizeof *list->array);
	for (size_t i = list->num_elements - 1; i > p; i--) {
		list->array[i] = list->array[i - 1];
	}
	list->array[p] = new_value;
}

void remove_at_position(struct array_list *list, size_t p) {
	for (size_t i = p; i < list->num_elements - 1; i++) {
		list->array[i] = list->array[i + 1];
	}
	list->array = realloc(list->array, --list->num_elements
		* sizeof *list->array);
}

int
main(void)
{
	struct array_list l = { .array = malloc(0), .num_elements = 0 };
	add_to_end(&l, 3);
	add_to_end(&l, 5.5);
	add_at_position(&l, 1, 0.0);
	remove_at_position(&l, 0);
	for (size_t i = 0; i < l.num_elements; i++) {
		printf("%lf\n", l.array[i]);	// should print 0.0, then 5.5
	}
	free(l.array);
	return 0;
}

