#include <stdio.h>
#include <stdlib.h>

struct heap {
	int *elements;
	size_t num_elements;
};

static
int
left_child(int parent)
{
	return 2 * parent + 1;
}

static
int
right_child(int parent)
{
	return 2 * parent + 2;
}

static
int
parent(int child)
{
	return (child - 1) / 2;
}

static
void
swap(struct heap *h, size_t p1, size_t p2)
{
	int temp = h->elements[p1];
	h->elements[p1] = h->elements[p2];
	h->elements[p2] = temp;
}

void
insert_element(struct heap *h, int new_element)
{
	h->elements = realloc(h->elements,
		++h->num_elements * sizeof *h->elements);
	size_t current_position = h->num_elements - 1;
	h->elements[current_position] = new_element;

	// heapify up
	while (current_position != 0) {	// 0 is the position of the root
		size_t p = parent(current_position);
		if (h->elements[current_position] > h->elements[p]) {
			swap(h, current_position, p);
		}
		current_position = p;
	}
}

static
int
val(struct heap const *h, int position)
{
	if (position < h->num_elements) {
		return h->elements[position];
	} else {
		return -1;
	}
}

int
get_maximum_element(struct heap *h)
{
	int const maximum_value = h->elements[0];
	size_t current_position = 0;
	h->elements[current_position] = h->elements[h->num_elements - 1];
	h->elements = realloc(h->elements,
		--h->num_elements * sizeof *h->elements);

	// heapify down
	while (current_position < h->num_elements) {
		int left_index = left_child(current_position);
		int right_index = right_child(current_position);
		int best_child = val(h, left_index) > val(h, right_index)
			? left_index : right_index;
		if (val(h, current_position) < val(h, best_child)) {
			swap(h, current_position, best_child);
		}
		current_position = best_child;
	}

	return maximum_value;
}

int
main(void)
{
	struct heap h = { .elements = NULL, .num_elements = 0 };
	int x;
	while (1) {
		if (scanf("%d", &x) == 1) {
			printf("Adding %d to the heap...\n", x);
			insert_element(&h, x);
		} else {
			printf("%d was returned from the heap\n",
				get_maximum_element(&h));
			while (getchar() != '\n')
				;
		}
	}
}





