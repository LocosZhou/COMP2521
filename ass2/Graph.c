// ADT GRAPH
//refer to the lecture material week04a/exercises
#include "Graph.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Graph newGraph(List L) {
    int nV = getLenLL(L);
    assert(nV >= 0);

    Graph g = malloc(sizeof(GraphRep));
    assert(g != NULL);
    g->nV = nV;

    int i = 0;
    List tmp = L;
    for (; i < nV; i++,tmp = tmp->next){
        g->adj[i].data = (char*)malloc(sizeof(char)*(strlen(tmp->v)+1));
        strcpy(g->adj[i].data, tmp->v);
        g->adj[i].firstarc = NULL;
        g->adj[i].w_out = 0;
        g->adj[i].w_in = 0;
        g->adj[i].sum_adjs_in = 0;
        g->adj[i].sum_adjs_out = 0;
        g->adj[i].PR_ = 0;
        g->adj[i].PR = 0;
    }
    return g;
}

void insertEdge(Graph g, char* src, char* dest) {
    assert(g != NULL);
    int isrc = 0, idest = 0;
    int i = 0;
    for(; i<g->nV; i+=1){
        if(strcmp(g->adj[i].data, src) == 0) isrc = i;
        if(strcmp(g->adj[i].data, dest) == 0) idest = i;
    }
    List firstNode = g->adj[isrc].firstarc;
    List curfirstNode = insertLL(firstNode, dest);
    g->adj[isrc].firstarc = curfirstNode;

    // cal Node_in and Node_out
    g->adj[isrc].w_out += 1;
    g->adj[idest].w_in += 1;

}

// count in-out degree
void count_adjs_in_out(Graph g){
    int i = 0;
    for( ; i<g->nV; i+=1){
        List tmp = g->adj[i].firstarc;
        for(;tmp;tmp=tmp->next){
            int j = 0;
            for (; j<g->nV; j+=1){
                if(strcmp(g->adj[j].data,tmp->v)==0){
                    break;
                }
            }
            g->adj[i].sum_adjs_in += g->adj[j].w_in;

            // by Note: out_degree will not be zero
            if(g->adj[j].w_out==0){
                g->adj[i].sum_adjs_out += 0.5;
            }else{
                g->adj[i].sum_adjs_out += g->adj[j].w_out;
            }

        }
        // debug
        // printf("nodeid %d sumin: %f sumout:%f\n", i, g->adj[i].sum_adjs_in, g->adj[i].sum_adjs_out);
    }
}
