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
void
recalculate_height(struct node *n)
{
	int lh = n->left == NULL ? 0 : n->left->height;
	int rh = n->right == NULL ? 0 : n->right->height;
	if (lh > rh) {
		n->height = lh + 1;
	} else {
		n->height = rh + 1;
	}
}

static
struct node *
rebalance(struct node *n)
{
	if (balance_factor(n) == -2 && balance_factor(n->left) == +1) {	// LR
		struct node *x = n,
			*y = x->left,
			*d = x->right,
			*a = y->left,
			*z = y->right,
			*b = z->left,
			*c = z->right;
		x->left = z;
		x->right = d;
		z->left = y;
		z->right = c;
		y->left = a;
		y->right = b;
		n = x;	// root of this subtree is still x
		recalculate_height(z);
		recalculate_height(y);
		recalculate_height(x);
	}
	if (balance_factor(n) == -2 && balance_factor(n->left) <= 0) {	// LL
		struct node *x = n,
			*y = x->left,
			*d = x->right,
			*z = y->left,
			*c = y->right,
			*a = z->left,
			*b = z->right;
		y->left = z;
		y->right = x;
		z->left = a;
		z->right = b;
		x->left = c;
		x->right = d;
		n = y;	// the new root of this subtree is y
/* this is the smart way to do it
		struct node *new_root = n->left;
		n->left = new_root->right;
		new_root->right = n;
		n = new_root;
*/
		recalculate_height(z);
		recalculate_height(x);
		recalculate_height(y);
	}

	if (balance_factor(n) == +2 && balance_factor(n->right) == -1) {	// RL
		struct node *x = n,
			*y = x->right,
			*d = x->left,
			*a = y->right,
			*z = y->left,
			*b = z->right,
			*c = z->left;
		x->right = z;
		x->left = d;
		z->right = y;
		z->left = c;
		y->right = a;
		y->left = b;
		n = x;	// root of this subtree is still x
		recalculate_height(z);
		recalculate_height(y);
		recalculate_height(x);
	}
	if (balance_factor(n) == +2 && balance_factor(n->right) >= 0) {	// RR
		struct node *x = n,
			*y = x->right,
			*d = x->left,
			*z = y->right,
			*c = y->left,
			*a = z->right,
			*b = z->left;
		y->right = z;
		y->left = x;
		z->right = a;
		z->left = b;
		x->right = c;
		x->left = d;
		n = y;	// the new root of this subtree is y
		recalculate_height(z);
		recalculate_height(x);
		recalculate_height(y);
	}

	return n;
}

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
	recalculate_height(n);
	return rebalance(n);
	//return n;
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
		if (n->left == NULL && n->right == NULL) {
			free(n);
			return NULL;
		} else if (n->left == NULL) {	// only right child
			struct node *t = n->right;
			free(n);
			n = t;
		} else if (n->right == NULL) {	// only left child
			struct node *t = n->left;
			free(n);
			n = t;
		} else {	// we have 2 children :(
			struct node *replacement = immediate_successor(n);
			long long new_value = replacement->data;
			n->right = remove_from_node(n->right, new_value);
			n->data = new_value;
		}
	}
	recalculate_height(n);
	return rebalance(n);
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
	long long x;
	while (scanf("%lld", &x) == 1) {
		insert_in_tree(&t, x);
	}
	destroy_tree(&t);
	return 0;
}






