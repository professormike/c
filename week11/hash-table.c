#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <string.h>
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

struct hash_entry {
	bool empty;
	uint32_t key_hash;
	char *key;
	double value;
};

void
insert_key_value(struct hash_entry *table, size_t table_size,
char *key, double value)
{
	uint32_t h = hash(key);
	size_t start_position = h % table_size;
	for (size_t i = 0; i < table_size; i++) {
		size_t position = (start_position + i) % table_size;
		if (table[position].empty) {
			table[position].key_hash = h;
			table[position].key = key;
			table[position].value = value;
			table[position].empty = false;
			return;
		}
	}
}

double
retrieve_value(struct hash_entry const *table, size_t table_size,
char const *key)
{
	uint32_t h = hash(key);
	size_t start_position = h % table_size;
	for (size_t i = 0; i < table_size; i++) {
		size_t position = (start_position + i) % table_size;
		if (table[position].key_hash == h
		&& strcmp(table[position].key, key) == 0) {
			return table[position].value;
		}
	}
	return NAN;
}

int
main(void)
{
#define N	5		// size of the hash table
	struct hash_entry table[N];
	for (size_t i = 0; i < N; i++) {
		table[i].empty = true;
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
	return 0;
}
