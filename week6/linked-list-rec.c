#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;	// this is the data that's stored in the list
	struct node *next;	// a reference to the next node in the list
};
struct linked_list {
	struct node *head;
};

int
list_length_node(struct node const *n)
/*
 * returns the number of nodes in the list starting at 'n'
 */
{
	if (n == NULL) {
		return 0;
	} else {
		// we first calculate the length of the list starting at
		// n->next, then add 1 to it to account for the current node
		return list_length_node(n->next) + 1;
	}
}

int
list_length(struct linked_list const *l)
{
	return list_length_node(l->head);
}

struct node *
add_to_end_node(struct node *n, int x)
/*
 * 'n' represents the node that begins a section of a linked list.
 * We return the NEW node that begins the section of this linked list,
 *		which might just the same as 'n'
 */
{
	if (n == NULL) {
		n = malloc(sizeof *n);
		n->data = x;
		n->next = NULL;
		return n;
	} else {
		n->next = add_to_end_node(n->next, x);
		return n;
	}
}

void
add_to_end(struct linked_list *l, int x)
{
	l->head = add_to_end_node(l->head, x);
}

void
print_node(struct node const *n)
{
	if (n == NULL) {
		// do nothing
	} else {
		printf("%d\n", n->data);
		print_node(n->next);
	}
}

void
print_list(struct linked_list const *l)
{
	print_node(l->head);
}

void
free_node(struct node *n)
{
	if (n == NULL) {
		// do nothing
	} else {
		free_node(n->next);
		free(n);
	}
}

void
free_list(struct linked_list *l)
{
	free_node(l->head);
}

struct node *
remove_from_end_node(struct node *n)
{
	if (n == NULL) {	// there were no nodes to begin with
		return NULL;
	} else if (n->next == NULL) {	// we've found the last node
		free(n);
		return NULL;
	} else {
		n->next = remove_from_end_node(n->next);
		return n;
	}
}

void
remove_from_end(struct linked_list *l)
{
	l->head = remove_from_end_node(l->head);
}

int
main(void)
{
	struct linked_list l = { .head = NULL };
	add_to_end(&l, 1);
	add_to_end(&l, 2);
	add_to_end(&l, 3);
	remove_from_end(&l);
	print_list(&l);
	free_list(&l);
	return 0;
}




