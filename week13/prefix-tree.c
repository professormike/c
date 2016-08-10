#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

struct prefix_tree_node {
	bool is_word;
	struct prefix_tree_node *children[26];
};
struct prefix_tree {
	struct prefix_tree_node *root;
};

static
struct prefix_tree_node *
insert_nodes(struct prefix_tree_node *n, char const *s)
{
	if (n == NULL) {
		n = malloc(sizeof *n);
		n->is_word = false;
		for (int i = 0; i < sizeof n->children / sizeof *n->children; i++) {
			n->children[i] = NULL;
		}
	}
	if (*s == '\0') {
		n->is_word = true;
	} else {
		// to figure out which child number we need to follow, we take
		// the ASCII value of the character we're currently pointing at
		// and subtract the ASCII value for 'a'
		int child_index = *s - 'a';	// 0 <= child_index <= 25
		assert(child_index >= 0 && child_index <= 25);
		n->children[child_index] = insert_nodes(n->children[child_index],
			s + 1);
	}
	return n;
}

void
insert_word(struct prefix_tree *tree, char const *s)
{
	tree->root = insert_nodes(tree->root, s);
}


static
bool
word_exists_node(struct prefix_tree_node const *n, char const *s)
{
	if (n == NULL) {
		return false;
	} else if (*s == '\0') {
		return n->is_word;
	} else {
		int child_index = *s - 'a';	// 0 <= child_index <= 25
		assert(child_index >= 0 && child_index <= 25);
		return word_exists_node(n->children[child_index], s + 1);
	}
}

bool
word_exists(struct prefix_tree const *tree, char const *s)
{
	return word_exists_node(tree->root, s);
}

int
main(int argc, char **argv)
{
#define I(x)	insert_word(&tree, x)
	struct prefix_tree tree = { .root = NULL };
	I("a");	I("an");	I("ant");	I("ants");	I("bag");
	I("battle");	I("bat");	I("xylophone");
	if (word_exists(&tree, argv[1])) {
		printf("%s exists\n", argv[1]);
	} else {
		printf("%s does not exist\n", argv[1]);
	}
	return 0;
}

