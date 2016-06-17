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
add_to_beginning(struct linked_list *l, int x)
{
	// create the new node
	struct node *new_node = malloc(sizeof *new_node);
	new_node->data = x;

	// add the new node to the head of the list
	new_node->next = l->head;
	l->head = new_node;	
}

void
add_at_position(struct linked_list *l, int x, size_t position)
/*
 * 'l' is a pointer to a linked list
 * 'x' is a new element to insert into the linked list
 * 'position' is a number (starting counting from 0) indicating where in
 *		the linked list to insert the element. The head of the list is
 *		position 0, the next element is 1, and so on...
 * if 'position' is out of bounds, do not do any insertion
 */
{
	if (position == 0) {	// make a special case for this so that we
							// don't have to use pointers to pointers
		add_to_beginning(l, x);
	} else {
		// create the new node
		struct node *new_node = malloc(sizeof *new_node);
		new_node->data = x;

		// find the node that comes immediately before the insertion, then
		// insert the new node in
		struct node *current_node = l->head;
		for (size_t i = 0; i < position - 1; i++) {
			current_node = current_node->next;
			if (current_node == NULL) {	// unexpectedly hit end of the list
				free(new_node);
				return;
			}
		}
		new_node->next = current_node->next;
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

void
remove_from_end(struct linked_list *l)
{
	struct node *current_node = l->head;
	if (current_node == NULL) {	// empty list
		// do nothing
	} else if (current_node->next == NULL) {	// only 1 element
		free(l->head);
		l->head = NULL;
	} else {
		// loop will stop at the 2nd last node
		while (current_node->next->next != NULL) {
			current_node = current_node->next;
		}
		free(current_node->next);	// deallocate the last node
		current_node->next = NULL;
	}
}

void
remove_from_beginning(struct linked_list *l)
{
	if (l->head == NULL) {
		// do nothing
	} else {
		struct node *second_node = l->head->next;
		free(l->head);	// deallocates the first node
		l->head = second_node;	// update pointer to point at 2nd node
	}
}

int
main(void)
{
	struct linked_list l = { .head = NULL };	// initially an empty list
	add_to_beginning(&l, 0);
	add_to_end(&l, 2);
	add_to_end(&l, 9);
	add_to_end(&l, 1);
	add_to_end(&l, 6);
	add_to_beginning(&l, 10);
	add_at_position(&l, 20, 3);
	add_at_position(&l, 30, 1000000);	// this should not insert anything
	remove_from_end(&l);
	remove_from_beginning(&l);
	print_list(&l);
	free_list(&l);
	return 0;
}









