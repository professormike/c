#include <stdio.h>

static char *nodes[] = { "A", "B", "C", "D", "E", "F", "G", "H" };
#define N	(sizeof nodes / sizeof *nodes)
static int matrix_rows[][N] = {
	{ 0, 5, 3, -1, -1, -1, -1, -1 },	// nodes reachable from A
	{ -1, 0, -1, -1, -1, -1, -1, -1 },	// nodes reachable from B
	{ -1, -1, 0, -1, 4, 80, -1, -1 },	// nodes reachable from C
	{ 10, 10, -1, 0, -1, -1, -1, -1 },	// nodes reachable from D
	{ -1, -1, 2, 13, 0, -1, -1, -1 },	// nodes reachable from E
	{ 20, 7, -1, -1, -1, 0, -1, -1 },	// nodes reachable from F
	{ -1, -1, 3, -1, -1, -1, 0, 10 },	// nodes reachable from G
	{ -1, -1, -1, -1, -1, -1, 6, 0 }	// nodes reachable from H
};

int
main(void)
{
	int *edges[N];
	for (size_t i = 0; i < N; i++) {
		edges[i] = matrix_rows[i];
	}
	return 0;
}
