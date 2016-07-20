#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct node {
	long long data;
	struct node *left, *right;
	int height;
};
struct tree {
	struct node *root;
};

static
int
balance_factor(struct node const *n)
{
	/*
	if (n->left == NULL && n->right == NULL) {
		return 0;
	} else if (n->right == NULL) {
		return -n->left->height;
	} else if (n->left == NULL) {
		return n->right->height;
	} else {
		return n->right->height - n->left->height;
	}
	*/
	int r = n->right == NULL ? 0 : n->right->height;
	int l = n->left == NULL ? 0 : n->left->height;
	return r - l;
}

static
bool
search_in_node(struct node const *n, long long x)
{
	if (*n == NULL) {
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
search_in_tree(struct tree *t, long long x)
{
	return search_in_node(t->root, x);
}

static
struct node *
insert_in_node(struct node *n, long long x)
{
	if (n == NULL) {	// need to insert the node here
		n = malloc(sizeof *n);
		n->data = x;
		n->left = NULL;
		n->right = NULL;
		n->height = 1;
	} else if (n->data > x) {
		n->left = insert_in_node(n->left, x);
	} else if (n->data < x) {
		n->right = insert_in_node(n->right, x);
	}
	return n;
}

void
insert_in_tree(struct tree *t, long long x)
{
	t->root = insert_in_node(t->root, x);
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

static
struct node *
remove_from_node(struct node *n, long long x)
{
	if (n == NULL) {	// wasn't found
		// do nothing
	} else if (n->data > x) {
		n->left = remove_from_node(n->left, x);
	} else if (n->data < x) {
		n->right = remove_from_node(n->right, x);
	} else {
		if (node_tbd->left == NULL && node_tbd->right == NULL) {
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
	return n;
}

void
remove_from_tree(struct tree *t, long long x)
{
	t->root = remove_from_node(t->root, x);
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
	remove_from_tree(&t, 8);
	printf("14 exists? %d\n", search_in_tree(&t, 14));
	printf("15 exists? %d\n", search_in_tree(&t, 15));
	printf("8 exists? %d\n", search_in_tree(&t, 8));
	destroy_tree(&t);
	return 0;
}






