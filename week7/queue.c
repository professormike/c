#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>	// for isalpha

struct node {
	char data;
	struct node *next;
};
struct queue {
	struct node *head, *tail;
};

void
enqueue(struct queue *q, char new_data)
{
	struct node *new_node = malloc(sizeof *new_node);
	new_node->data = new_data;
	new_node->next = NULL;

	if (q->head == NULL) {	// the list is empty
		q->head = new_node;
	} else {
		q->tail->next = new_node;
	}
	q->tail = new_node;
}

char
serve(struct queue *q)
/*
 * if the queue is empty, this code will crash
 */
{
	char data_to_serve = q->head->data;
	struct node *next_node = q->head->next;
	free(q->head);
	q->head = next_node;
	if (q->head == NULL) {	// we have just become empty
		q->tail = NULL;
	}
	return data_to_serve;
}

int
main(void)
{
	struct queue q = { .head = NULL, .tail = NULL };
	do {
		char c;
		scanf("%c", &c);
		getchar();	// consume the newline character after it
		if (isalpha(c)) {
			enqueue(&q, c);
		} else {	// enter a non-letter (like -) to serve from the queue
			printf("served element: %c\n", serve(&q));
		}
	} while (q.head != NULL);	// keep looping until the queue is empty
	return 0;
}













