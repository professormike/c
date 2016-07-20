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

static
struct node *
immediate_successor(struct node *n)
{
	n = n->right;
	while (n->left != NULL) {
		n = n->left;
	}
	return n;
}

void
remove_from_tree(struct tree *t, long long x)
{
	struct node **n = search_in_node(&t->root, x);
	struct node * const node_tbd = *n;
	if (node_tbd == NULL) {	// number we searched for doesn't exist
		return;
	} else if (node_tbd->left == NULL && node_tbd->right == NULL) {
		free(node_tbd);
		*n = NULL;	// update pointer in parent node
	} else if (node_tbd->left == NULL) {	// only right child
		*n = node_tbd->right;
		free(node_tbd);
	} else if (node_tbd->right == NULL) {	// only left child
		*n = node_tbd->left;
		free(node_tbd);
	} else {	// we have 2 children :(
		struct node *replacement = immediate_successor(node_tbd);
		long long new_value = replacement->data;
		remove_from_tree(t, new_value);
		node_tbd->data = new_value;
	}
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
	remove_from_tree(&t, 16);
	printf("14 exists? %d\n", search_in_tree(&t, 14));
	printf("15 exists? %d\n", search_in_tree(&t, 15));
	printf("16 exists? %d\n", search_in_tree(&t, 16));
	destroy_tree(&t);
	return 0;
}






