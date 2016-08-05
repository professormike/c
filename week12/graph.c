#include <stdio.h>
#include <stdbool.h>
#include <limits.h>	// needed for INT_MAX
#include <string.h>

static char *nodes[] = { "A", "B", "C", "D", "E", "F", "G" };
#define N	7
static int matrix_rows[][N] = {
    // A   B   C   D   E   F   G
	{  0, -1, -1, 20, -1, -1, 75 },
	{ -1,  0, -1, -1, -1, -1, -1 },
	{ -1, -1,  0, -1,  5, -1, 25 },
	{ -1, 40, -1,  0, 35, 10, 45 },
	{ -1, 10, -1, -1,  0, -1, 10 },
	{ -1,  5, 15, -1, 40,  0, -1 },
	{ -1, -1, -1, -1, -1, -1,  0 }
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

void
shortest_path(int from, int to, char **nodes, int **edges)
{
	bool visited[N];
	int parent[N];	// we store the parent as the position in the array
					// of nodes
	int cost[N];
	for (size_t i = 0; i < N; i++) {
		visited[i] = false;
		parent[i] = -1;	// -1 indicating there is no parent
		if (i == from) {
			cost[i] = 0;
		} else {
			cost[i] = INT_MAX;	// INT_MAX takes the place of infinity
		}
	}

	for (size_t i = 0; i < N; i++) {
		// search for the lowest-cost unvisited node
		int node_position = 0;	// start off at node #0
		for (size_t j = 0; j < N; j++) {
			// if node_position refers to a node that's already been
			// visited, change it. We also change it in the case that
			// we've found a lower-cost node
			if (!visited[j] &&
			(visited[node_position] || cost[node_position] > cost[j])) {
				node_position = j;
			}
		}

		// mark the node as visited
		visited[node_position] = true;

		// find immediately reachable nodes and update them in the table
		for (size_t j = 0; j < N; j++) {
			if (edges[node_position][j] > 0) {	// there's an edge to
												// another node
				int total_cost = cost[node_position] +
					edges[node_position][j];
				if (total_cost < cost[j]) {	// found a lower-cost path to j
					// update the table
					parent[j] = node_position;
					cost[j] = total_cost;
				}
			}
		}
	}

	// at this point we have a completed table. We now want to figure out
	// what the lowest-cost path is. We start at the end node and work
	// backwards
	printf("Lowest-cost path from %s to %s: ", nodes[from], nodes[to]);
	char output[1000] = "";
	while (to != from) {
		strcat(output, nodes[to]);
		strcat(output, " >- ");
		to = parent[to];
	}
	strcat(output, nodes[from]);
	// reverse the string
	for (size_t i = 0; i < strlen(output) / 2; i++) {
		char tmp = output[i];
		output[i] = output[strlen(output) - i - 1];
		output[strlen(output) - i - 1] = tmp;
	}
	printf("%s\n", output);
}

int
main(void)
{
	int *edges[N];
	for (size_t i = 0; i < N; i++) {
		edges[i] = matrix_rows[i];
	}
	//printf("A to D? %d\n", can_reach(0, 3, nodes, edges));
	//printf("A to G? %d\n", can_reach(0, 6, nodes, edges));
	shortest_path(0, 4, nodes, edges);
	return 0;
}
