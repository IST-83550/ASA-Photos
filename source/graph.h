/*

	Graph Representation
	(adjacency lists)

*/
#ifndef _GRAPH_H_
#define _GRAPH_H_

/* NIL value representation. */
#define NIL -1

/* White colour. */
#define WHITE 1

/* Gray colour. */
#define GRAY 2

/* Black colour. */
#define BLACK 3

/* DFS auxiliary matrix index macros. */
/* Vertex Color. */
#define COLOR 0

/* Data Array. */
#define DATA 1

/* Graph vertex type (integer). */
typedef int graph_vertex_t;

/* Adjacency list node type. */
typedef struct graph_node graph_node_t;

/* Graph structure type. */
typedef struct _graph graph_t;

/* Create a new graph. */
graph_t *graph_new(int V);

/* Free memory allocated with graph. */
void graph_free(graph_t *graph);

/* Add an edge to the graph. */
void graph_add_edge(graph_t *graph, graph_vertex_t u, graph_vertex_t v);

/* Main DFS function. */
void dfs_main(graph_t *graph);

/* DFS function (visit). */
void dfs(graph_t *graph, graph_vertex_t u, int **aux);

#endif /* _GRAPH_H_ */