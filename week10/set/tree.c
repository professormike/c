#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct node {
	long long data;
	struct node *left, *right;
};
struct tree {
	struct node *root;
};

static
struct node **
search_in_node(struct node **n, long long x)
{
	if (*n == NULL) {
		return n;
	} else if ((*n)->data > x) {
		return search_in_node(&(*n)->left, x);
	} else if ((*n)->data < x) {
		return search_in_node(&(*n)->right, x);
	} else {	// n->data == x
		return n;
	}
}

bool
element_exists(void *t_, long long x)
{
	struct tree *t = t_;
	return *search_in_node(&t->root, x) != NULL;
}

void
insert_element(void *t_, long long x)
{
	struct tree *t = t_;
	struct node **n = search_in_node(&t->root, x);
	if (*n == NULL) {	// need to insert the node
		*n = malloc(sizeof **n);
		(*n)->data = x;
		(*n)->left = NULL;
		(*n)->right = NULL;
	} else {	// data already exists
		// do nothing
	}
}

static
void
destroy_from_node(struct node *n)
{
	if (n == NULL) {
		// do nothing
	} else {
		destroy_from_node(n->left);
		destroy_from_node(n->right);
		free(n);
	}
}

void
free_set(void *t_)
{
	struct tree *t = t_;
	destroy_from_node(t->root);
	free(t);
}

void *
empty_set(void)
{
	struct tree *t = malloc(sizeof *t);
	t->root = NULL;
	return t;
}







