#include "key-value-store.h"
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
		//s += x[i] * s * (int)pow(10, i);	// hash1
		s += x[i] * s * i;					// hash2
	}
	return s;
}

struct hash_entry {
	uint32_t key_hash;
	char *key;
	double value;
	struct hash_entry *next;
};

struct hash_table {
	struct hash_entry **table;
	size_t size;
};

void
insert_key_value(void *table_, char const *key, double value)
{
	struct hash_table *table = table_;
	uint32_t h = hash(key);
	size_t position = h % table->size;
	struct hash_entry *e = malloc(sizeof *e);
	e->key_hash = h;
	e->key = strdup(key);
	e->value = value;
	e->next = table->table[position];
	table->table[position] = e;
}

double
retrieve_value(void const *table_, char const *key)
{
	struct hash_table const *table = table_;
	uint32_t h = hash(key);
	size_t position = h % table->size;
	for (struct hash_entry const *e = table->table[position]; e != NULL; e = e->next) {
		if (e->key_hash == h && strcmp(e->key, key) == 0) {
			return e->value;
		}
	}
	return NAN;
}

void *
empty_key_value_store(void)
{
	struct hash_table *table = malloc(sizeof *table);
	table->table = malloc((table->size = 1000000000) * sizeof *table->table);
	for (size_t i = 0; i < table->size; i++) {
		table->table[i] = NULL;
	}
	return table;
}

void
free_key_value_store(void *table_)
{
	struct hash_table *table = table_;
	for (size_t i = 0; i < table->size; i++) {
		struct hash_entry *e = table->table[i];
		while (e != NULL) {
			free(e->key);
			struct hash_entry *ne = e->next;
			free(e);
			e = ne;
		}
	}
	free(table->table);
	free(table);
}

