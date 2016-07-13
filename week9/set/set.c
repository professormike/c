#include "set.h"
#include <stdlib.h>

// representing the set as an
// UNSORTED array, for which
// inserting is fast, but searching
// is slow
struct array_set {
	short *array;
	size_t num_elements;
};

void *
empty_set(void)
{
	struct array_set *r = malloc(sizeof *r);
	r->array = malloc(0);
	r->num_elements = 0;
	return r;
}

void
insert_element(void *s_, short x)
{
	struct array_set *s = s_;
	s->array = realloc(s->array, ++s->num_elements * sizeof *s->array);
	s->array[s->num_elements - 1] = x;
}

bool
element_exists(void const *s_, short x)
{
	struct array_set const *s = s_;
	for (size_t i = 0; i < s->num_elements; i++) {
		if (s->array[i] == x) {
			return true;
		}
	}
	return false;
}

void
free_set(void *s_)
{
	struct array_set *s = s_;
	free(s->array);
	free(s);
}







