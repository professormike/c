#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;	// this is the data that's stored in the list
	struct node *next;	// a reference to the next node in the list
};
struct linked_list {
	struct node *head;
};

void
add_to_end(struct linked_list *l, int x)
/*
 * 'l' is a pointer to an existing linked list (maybe empty, maybe not)
 * 'x' is a number that will be inserted at the end of the list
 */
{
	// create the new node
	struct node *new_node = malloc(sizeof *new_node);
	new_node->data = x;
	new_node->next = NULL;

	if (l->head == NULL) {	// the list is empty
		l->head = new_node;
	} else {				// the list is non-empty
		// search for the last node and update it to point to the new node
		struct node *current_node = l->head;
		while (current_node->next != NULL) {
			current_node = current_node->next;
		}
		current_node->next = new_node;
	}
}

void
print_list(struct linked_list const *l)
{
	struct node const *current_node = l->head;
	while (current_node != NULL) {
		printf("%d ", current_node->data);
		current_node = current_node->next;
	}
	printf("\n");
}

void
free_list(struct linked_list *l)
/*
 * deallocate all nodes in the linked list pointed to by 'l'
 */
{
	struct node *current_node = l->head;
	while (current_node != NULL) {
		struct node *temp = current_node->next;
		free(current_node);
		current_node = temp;
	}
}

int
main(void)
{
	struct linked_list l = { .head = NULL };	// initially an empty list
	add_to_end(&l, 2);
	add_to_end(&l, 9);
	add_to_end(&l, 1);
	add_to_end(&l, 6);
	print_list(&l);
	free_list(&l);
	return 0;
}









