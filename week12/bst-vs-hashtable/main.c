#include "key-value-store.h"
#include <stdio.h>

int
main(int argc, char **argv)
{
	void *store = empty_key_value_store();

	FILE *f = fopen(argv[1], "r");
	char k[100];
	double v;
	while (fscanf(f, "%99s %lf", k, &v) == 2) {
		insert_key_value(store, k, v);
	}
	fclose(f);

	f = fopen(argv[2], "r");
	while (fscanf(f, "%99s", k) == 1) {
		printf("%lf\n", retrieve_value(store, k));
	}
	fclose(f);

	free_key_value_store(store);

	return 0;
}
