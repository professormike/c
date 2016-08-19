#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

static
uint32_t
hash(char const *s, uint32_t start_value)
{
	for (size_t i = 0; s[i] != '\0'; i++) {
		start_value += i * s[i];
		start_value *= start_value;
	}
	return start_value;
}

static
uint32_t
hash1(char const *s)
{
	return hash(s, 5000);
}

static
uint32_t
hash2(char const *s)
{
	return hash(s, 500000000);
}

struct bloom_filter {
	uint8_t *table;	// array of bytes, with 8 bools per byte
	size_t table_size;
};

static
bool
get_bool(uint8_t const *array, size_t index)
{
	uint8_t byte = array[index / 8];
	byte >>= (index % 8);	// shift right by a few bits
	return (byte & 1) == 1;	// check to see if the rightmost bit is 1
}

static
void
set_bool(uint8_t *array, size_t index)
{
	uint8_t bit_to_set = 1 << (index % 8);
	array[index / 8] |= bit_to_set;
}

void
add_to_set(struct bloom_filter *b, char const *s)
{
	set_bool(b->table, hash1(s) % b->table_size);
	set_bool(b->table, hash2(s) % b->table_size);
}

bool
is_in_set(struct bloom_filter const *b, char const *s)
{
	return get_bool(b->table, hash1(s) % b->table_size)
		&& get_bool(b->table, hash2(s) % b->table_size);
}

static uint8_t table[50];

int
main(void)
{
	struct bloom_filter b = { table, 400 };
	char lne[100];
	while (fgets(lne, sizeof lne, stdin)) {
		if (lne[0] == '+') {
			add_to_set(&b, &lne[1]);
		} else if (lne[0] == '=') {
			printf("%d\n", is_in_set(&b, &lne[1]));
		}
	}
	return 0;
}

