#ifndef pagerank_h
#define pagerank_h

#include <stdio.h>
#include "Graph.h"

void PageRankW(Graph g, double d, double diffPR, int maxIterations);
void outputPageRankW(Graph g);
#endif /* pagerank_h */
