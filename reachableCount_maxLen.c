#include <stdio.h>
#include <stdbool.h>
#include "Graph.h"

#define MAX_NODES 1000

int visited[MAX_NODES];  // array to store visiting order
                         // indexed by vertex 0..nV-1


int reachableCount(Graph g, int nV, Vertex v, int maxLen) {
	if (maxLen <= 0) 
		return 0;

	Vertex w;
	int total = 0;
	visited[v] = 1;

	for (w = 0; i < nV; i++) {
		if (adjacent(g, v , w) && visited[w] == -1) {
			visited[w] = 1;
			int countR = reachableCount(g, nV, w, maxLen);
			total = total + countR;			
		}
	}
	total = total + 1;		// current node
	return total;
}

int main(void) {
	int V = 6;
    Graph g = newGraph(V);

    Edge e;
    e.v = 0; e.w = 1; insertEdge(g, e);
    e.v = 0; e.w = 4; insertEdge(g, e);
    e.v = 0; e.w = 5; insertEdge(g, e);
    e.v = 5; e.w = 4; insertEdge(g, e);
    e.v = 4; e.w = 2; insertEdge(g, e);
    e.v = 4; e.w = 3; insertEdge(g, e);
    e.v = 5; e.w = 3; insertEdge(g, e);
    e.v = 1; e.w = 2; insertEdge(g, e);
    e.v = 3; e.w = 2; insertEdge(g, e);

	for (int i = 0; i < V; i++) {
		visited[i] = -1;
 	}

 	int src = 1;
 	int countReachable = reachableCount(g, V, src, 3);

 	printf(" src: %d, reachableCount: %d \n", src, countReachable);
	return 0;
}