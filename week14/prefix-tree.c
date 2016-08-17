#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

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

static
struct prefix_tree_node const *
find_start_node(struct prefix_tree_node const *n, char const *s)
{
	if (n == NULL) {
		return NULL;
	} else if (*s == '\0') {
		return n;
	} else {
		int child_index = *s - 'a';	// 0 <= child_index <= 25
		assert(child_index >= 0 && child_index <= 25);
		return find_start_node(n->children[child_index], s + 1);
	}
}

static
int
num_words(struct prefix_tree_node const *n, int max_length)
{
	if (n == NULL || max_length < 0) {
		return 0;
	} else {
		int sum = n->is_word ? 1 : 0;
		for (size_t i = 0; i < 26; i++) {
			sum += num_words(n->children[i], max_length - 1);
		}
		return sum;
	}
}

int
num_words_begin_with(struct prefix_tree const *tree, char const *prefix,
int max_length)
{
	// follow the prefix to find the starting node
	struct prefix_tree_node const *start_node =
		find_start_node(tree->root, prefix);
	return num_words(start_node, max_length - strlen(prefix));
}

static
void
print_words_from_node(struct prefix_tree_node const *n, char const *prefix)
{
	if (n == NULL) {
		// do nothing
	} else {
		if (n->is_word) {
			printf("%s\n", prefix);
		}
		for (size_t i = 0; i < 26; i++) {
			// new_prefix is going to be the existing prefix, with one
			// more character added on to it, then the NUL character
			char new_prefix[strlen(prefix) + 2];
			// sprintf is "string printf". It's like printf but it writes
			// to a string instead of to the screen
			sprintf(new_prefix, "%s%c", prefix, (char)(i + 'a'));
			print_words_from_node(n->children[i], new_prefix);
		}
	}
}

void
print_words_with_prefix(struct prefix_tree const *tree, char const *prefix)
{
	struct prefix_tree_node const *start_node =
		find_start_node(tree->root, prefix);
	char word[50];
	strcpy(word, prefix);
	print_words_from_node(start_node, word);
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
	printf("words that begin with ba: %d\n",
		num_words_begin_with(&tree, "ba", 3));
	printf("words that begin with ba:\n");
	print_words_with_prefix(&tree, "ba");
	return 0;
}

