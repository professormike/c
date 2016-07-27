#include <stdio.h>
#include <stdint.h>	// needed for uint32_t
#include <math.h>
#include <string.h>	// needed for strcmp
#include <stdbool.h>

static
uint32_t
hash(char const *x)
{
	uint32_t s = 1345874409;
	for (size_t i = 0; x[i] != '\0'; i++) {
		s += x[i] * s * (int)pow(10, i);
	}
	return s;
}

struct node {
	char *value;
	uint32_t hash;
	struct node *left, *right;
};
struct hash_tree {
	struct node *root;
};

static
struct node *
insert_node(struct node *n, char *x, uint32_t h)
{
	if (n == NULL) {
		n = malloc(sizeof *n);
		n->left = NULL;
		n->right = NULL;
		n->value = x;
		n->hash = h;
	} else if (n->hash > h) {
		n->left = insert_node(n->left, x, h);
	} else if (n->hash < h) {
		n->right = insert_node(n->right, x, h);
	} else {	// the hashes are equal
		if (strcmp(n->value, x) == 0) {	// the strings are equal
			// do nothing
		} else {	// we've found a collision. Store it on our right
			n->right = insert_node(n->right, x, h);
		}
	}
	return n;
}

void
insert_into_tree(struct hash_tree *t, char *x)
{
	uint32_t h = hash(x);
	t->root = insert_node(t->root, x, h);
}

static
bool
exists_from_node(struct node const *n, char const *x, uint32_t h)
{
	if (n == NULL) {
		return false;
	} else if (n->hash > h) {
		return exists_from_node(n->left, x, h);
	} else if (n->hash < h) {
		return exists_from_node(n->right, x, h);
	} else {	// the hashes are equal
		if (strcmp(n->value, x) == 0) {	// strings are equal
			return true;
		} else {	// in case of collision, we inserted on the right
			return exists_from_node(n->right, x, h);
		}
	}
}

bool
exists_in_tree(struct hash_tree const *t, char const *x)
{
	uint32_t h = hash(x);
	return exists_from_node(t->root, x, h);
}

int
main(void)
{
	char lne[100];
	fgets(lne, sizeof lne, stdin);
	printf("%08x\n", hash(lne));
	return 0;
}
