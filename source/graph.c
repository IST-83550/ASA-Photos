#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "graph.h"

int data_pointer;

struct graph_node {
	graph_vertex_t vertex;
  	graph_node_t *next;
};

struct _graph {
  	int V, E;
  	graph_node_t **adjlist;
};

graph_t *graph_new(int V) {
	graph_t *graph = NULL;

	if( V > 0 && (graph = (graph_t*)malloc(sizeof(struct _graph))) != NULL) {
		graph->V = V;
		graph->E = 0;
		graph->adjlist = (graph_node_t**)malloc(V * sizeof( struct graph_node*));
	}
	return graph;
}

void graph_free(graph_t *graph) {
	int i;

	for(i = 0; i < graph->V; ++i) {
		graph_node_t *head = graph->adjlist[i];
		while (head != NULL) {
			graph_node_t *t = head;
			head = head->next;
			free(t);
		}
	}
	free(graph->adjlist);
	free(graph);
}

void graph_add_edge(graph_t *graph, graph_vertex_t u, graph_vertex_t v) {

	if((u > 0 && u <= graph->V) && (v > 0 && v <= graph->V)) {
    	graph_node_t *w = (graph_node_t*)malloc(sizeof(struct graph_node));

	/* Directed graph. */
    	if(w != NULL) {
      		w->vertex = v;
      		w->next = graph->adjlist[u - 1];
      		graph->adjlist[u - 1] = w;
    	}
    	else {
    		exit(EXIT_FAILURE);
    	}
    	graph->E++;
    }
}

void dfs_main(graph_t *graph) {
	int **aux, i;
	data_pointer = graph->V - 1;

	/* Creates auxiliary array. */
	aux = (int**)malloc(2 * sizeof(int*));
	if(aux != NULL){
	    aux[COLOR] = (int*)malloc(graph->V * sizeof(int));
	    aux[DATA] = (int*)malloc(graph->V * sizeof(int));
		if(!aux[COLOR] || !aux[DATA]){
      		exit(EXIT_FAILURE);
		}
	}
	else {
		exit(EXIT_FAILURE);
	}

	/* Initializations. */
	for(i = 0; i < graph->V; i++){
	    aux[COLOR][i] = WHITE;
	}

	/* Visits all unvisited vertexs (DFS). */
	for(i = 0; i < graph->V; i++){
	    if(aux[COLOR][i] == WHITE){
	    	dfs(graph, i + 1, aux);
	    }
	}

	/* Checks if DFS topological order is an hamiltonian path. */
	for(i = 0; i < ((graph->V)-1) ; i++){
		graph_node_t *node = graph->adjlist[aux[DATA][i] - 1];
		bool flag = false;

		while(node != NULL){
			if(aux[DATA][i + 1] == (node->vertex)){
				flag = true;
				break;
			}
			node = node->next;
		}

    	/* If vertex i+1 was not found on vertex i adjlist then
         it's not an hamiltonian path for the graph. */
		if(flag == false){
			printf("Insuficiente\n");

	        	free(aux[DATA]);
	        	free(aux[COLOR]);
	        	free(aux);
	        	graph_free(graph);			
			exit(EXIT_SUCCESS);
		}
	}

	for(i = 0; i < ((graph->V)-1) ; i++){
	    printf("%d ", aux[DATA][i]);
	}
	printf("%d", aux[DATA][i]);
	printf("\n");

	free(aux[DATA]);
	free(aux[COLOR]);
	free(aux);
}

void dfs(graph_t *graph, graph_vertex_t u, int **aux) {
	graph_node_t *node = graph->adjlist[u - 1];
	graph_vertex_t adj;

	aux[COLOR][u - 1] = GRAY;

	while(node != NULL){
		adj = node->vertex;
		
		/* If adj wasn't visited yet, visit it. */
	    if(aux[COLOR][adj - 1] == WHITE){
	    	dfs(graph, adj, aux);
		}
		/* If a back-edge was found a cycle was detected. */
		 else if (aux[COLOR][adj - 1] == GRAY){
			printf("Incoerente\n");
			exit(EXIT_SUCCESS);
		}
		node = node->next;
	}
	
	aux[COLOR][u - 1] = BLACK;
	aux[DATA][data_pointer--] = u;
}
