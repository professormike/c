#include <stdio.h>
#include <stdbool.h>

static char *nodes[] = { "A", "B", "C", "D", "E", "F", "G", "H" };
#define N	8
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

void
reachable(int current_node, char **nodes, int **edges, bool *visited)
{
	if (visited[current_node]) {
		// do nothing
	} else {
		printf("visited %s\n", nodes[current_node]);
		visited[current_node] = true;
		for (size_t i = 0; i < N; i++) {
			if (edges[current_node][i] > 0) {	// found a node to visit
				reachable(i, nodes, edges, visited);
			}
		}
	}
}

bool
can_reach(int from, int to, char **nodes, int **edges)
{
	bool visited[N];
	for (size_t i = 0; i < N; i++) {
		visited[i] = false;
	}
	reachable(from, nodes, edges, visited);
	return visited[to];
}

int
main(void)
{
	int *edges[N];
	for (size_t i = 0; i < N; i++) {
		edges[i] = matrix_rows[i];
	}
	printf("A to D? %d\n", can_reach(0, 3, nodes, edges));
	printf("A to G? %d\n", can_reach(0, 6, nodes, edges));
	return 0;
}
