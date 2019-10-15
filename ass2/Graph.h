//reference with the lecture material week04a/exercises
#ifndef Graph_h
#define Graph_h

#include <stdio.h>
#include <stdbool.h>
#include "list.h"
#define MAX_VERTEX_NUM 100
/*
 defined max 100 urls
 */
typedef struct GraphRep *Graph;

typedef struct AdjList{
    char* data; // node info like url.
    double PR; // PRt
    double PR_; // PRt+1
    /*
     in degree && out degree, refer to
     http://www.cse.unsw.edu.au/~cs2521/19T2/assigns/ass2/page1725348.pdf
     */
    int w_in;
    int w_out;

    // add all w_in \ w_out of current node's neighbors
    double sum_adjs_in;
    double sum_adjs_out;

    // point to its' neighbors
    List firstarc;

} AdjList;

typedef struct GraphRep {
    AdjList adj[MAX_VERTEX_NUM];  // array of lists
    int   nV;     // number of vertices
} GraphRep;

// create a Graph by its all Node
Graph newGraph(List L);
void  insertEdge(Graph, char*, char*);
// calculate all w_in \ w_out of current node's neighbors
void  count_adjs_in_out(Graph);
#endif /* Graph_h */
