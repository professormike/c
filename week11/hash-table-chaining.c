#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

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

struct hash_entry_node {
	uint32_t key_hash;
	char *key;
	double value;
	struct hash_entry_node *next;
};

struct hash_entry {
	struct hash_entry_node *head;
};

void
insert_key_value(struct hash_entry *table, size_t table_size,
char *key, double value)
{
	uint32_t h = hash(key);
	size_t position = h % table_size;
	struct hash_entry_node *n = malloc(sizeof *n);
	n->key_hash = h;
	n->key = key;
	n->value = value;
	n->next = table[position].head;
	table[position].head = n;
}

double
retrieve_value(struct hash_entry const *table, size_t table_size,
char const *key)
{
	uint32_t h = hash(key);
	size_t position = h % table_size;
	for (struct hash_entry_node *n = table[position].head; n != NULL;
	n = n->next) {
		if (n->key_hash == h && strcmp(n->key, key) == 0) {
			return n->value;
		}
	}
	return NAN;
}

void
free_table(struct hash_entry *table, size_t table_size)
{
	for (size_t i = 0; i < table_size; i++) {
		struct hash_entry_node *n = table[i].head;
		while (n != NULL) {
			struct hash_entry_node *next = n->next;
			free(n);
			n = next;
		}
	}
}

int
main(void)
{
#define N	5		// size of the hash table
	struct hash_entry table[N];
	for (size_t i = 0; i < N; i++) {
		table[i].head = NULL;
	}
	insert_key_value(table, N, "apples", 0.79);
	insert_key_value(table, N, "bananas", 0.65);
	insert_key_value(table, N, "cherries", 1.50);
	printf("apples are %0.2lf\n", retrieve_value(table, N, "apples"));
	printf("bananas are %0.2lf\n",
		retrieve_value(table, N, "bananas"));
	printf("cherries are %0.2lf\n", retrieve_value(table, N, "cherries"));
	printf("elephants are %0.2lf\n",
		retrieve_value(table, N, "elephants"));
	free_table(table, N);
	return 0;
}
