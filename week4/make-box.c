#include <stdio.h>
#include <stdlib.h>

char *
produce_box(int size)
/*
 * 'size' is the length of each side of the box (square)
 * returns a new string allocated on the heap that can be printed out
 * This function does NOT print anything by itself
 */
{
	char *s = malloc((size * (size + 1) + 1) * sizeof *s);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			s[i * (size + 1) + j] = '*';
		}
		s[i * (size + 1) + size] = '\n';
	}
	s[size * (size + 1)] = '\0';
	return s;
}

int
main(void)
{
	char *b = produce_box(5);
	printf("%s\n", b);
	free(b);
	return 0;
}
