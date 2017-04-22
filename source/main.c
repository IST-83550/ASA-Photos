#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#include "graph.h"

int main() {

	int V, E;
	graph_t *graph;

	/* Reads number of vertexs and edges. */
	assert(scanf("%d %d", &V, &E) == 2);
 	assert(V > 0 && E > 0);

 	graph = graph_new(V);
 	assert(graph != NULL);

	/* Reads edges. */
 	while(E-- > 0) {
		int u, v;
		assert(scanf("%d %d", &u, &v) == 2);
		graph_add_edge(graph, u, v);
	}

	dfs_main(graph);

	graph_free(graph);

	return EXIT_SUCCESS;
}
