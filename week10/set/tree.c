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
search_in_tree(struct tree *t, long long x)
{
	return *search_in_node(&t->root, x) != NULL;
}

void
insert_in_tree(struct tree *t, long long x)
{
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
destroy_tree(struct tree *t)
{
	destroy_from_node(t->root);
}

int
main(void)
{
	struct tree t = { .root = NULL };
	insert_in_tree(&t, 8);
	insert_in_tree(&t, 4);
	insert_in_tree(&t, 2);
	insert_in_tree(&t, 6);
	insert_in_tree(&t, 16);
	insert_in_tree(&t, 12);
	insert_in_tree(&t, 18);
	insert_in_tree(&t, 10);
	insert_in_tree(&t, 14);
	printf("14 exists? %d\n", search_in_tree(&t, 14));
	printf("15 exists? %d\n", search_in_tree(&t, 15));
	destroy_tree(&t);
	return 0;
}






