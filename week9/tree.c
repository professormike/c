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
bool
search_in_node(struct node const *n, long long x)
{
	if (n == NULL) {
		return false;
	} else if (n->data > x) {
		return search_in_node(n->left, x);
	} else if (n->data < x) {
		return search_in_node(n->right, x);
	} else {	// n->data == x
		return true;
	}
}

bool
search_in_tree(struct tree const *t, long long x)
{
	return search_in_node(t->root, x);
}

static
struct node *
insert_in_node(struct node *n, long long x)
{
	if (n == NULL) {
		n = malloc(sizeof *n);
		n->data = x;
		n->left = NULL;
		n->right = NULL;
	} else if (n->data > x) {
		n->left = insert_in_node(n->left, x);
	} else if (n->data < x) {
		n->right = insert_in_node(n->right, x);
	} else {		// n->data == x
		// do nothing
	}
	return n;
}

void
insert_in_tree(struct tree *t, long long x)
{
	t->root = insert_in_node(t->root, x);
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
	return 0;
}






