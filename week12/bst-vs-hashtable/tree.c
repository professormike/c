#include "key-value-store.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node {
	char *key;
	double value;
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
double
search_in_node(struct node const *n, char const *key)
{
	if (n == NULL) {
		return NAN;
	} else if (strcmp(n->key, key) > 0) {
		return search_in_node(n->left, key);
	} else if (strcmp(n->key, key) < 0) {
		return search_in_node(n->right, key);
	} else {	// n->data == x
		return n->value;
	}
}

double
retrieve_value(void const *t_, char const *key)
{
	struct tree const *t = t_;
	return search_in_node(t->root, key);
}

static
struct node *
insert_in_node(struct node *n, char const *key, double value)
{
	if (n == NULL) {	// need to insert the node here
		n = malloc(sizeof *n);
		n->key = strdup(key);
		n->value = value;
		n->left = NULL;
		n->right = NULL;
		n->height = 1;
	} else if (strcmp(n->key, key) > 0) {
		n->left = insert_in_node(n->left, key, value);
	} else if (strcmp(n->key, key) < 0) {
		n->right = insert_in_node(n->right, key, value);
	}
	recalculate_height(n);
	return rebalance(n);
}

void
insert_key_value(void *t_, char const *key, double value)
{
	struct tree *t = t_;
	t->root = insert_in_node(t->root, key, value);
}

static
void
destroy_from_node(struct node *n)
{
	if (n == NULL) {
		// do nothing
	} else {
		free(n->key);
		destroy_from_node(n->left);
		destroy_from_node(n->right);
		free(n);
	}
}

void
free_key_value_store(void *t_)
{
	struct tree *t = t_;
	destroy_from_node(t->root);
	free(t);
}

void *
empty_key_value_store(void)
{
	struct tree *t = malloc(sizeof *t);
	t->root = NULL;
	return t;
}
