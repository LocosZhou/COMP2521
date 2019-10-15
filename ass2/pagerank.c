#include "pagerank.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "readData.h"

int main(int argc, const char * argv[]) {
    // test pagerank
    // double d = 0.85;
    // double diffPR = 0.00001;
    // int maxIterations = 1000;

    assert(argc == 4);

    double d = atof(argv[1]);
    double diffPR = atof(argv[2]);
    int maxIterations = atoi(argv[3]);

    // readfile
    List L = getCollection();
    Graph g = getGraph(L);

    // count all node sum in\out degrees
    count_adjs_in_out(g);
    // calculate PR
    PageRankW(g, d, diffPR, maxIterations);
    // sort and save in file
    outputPageRankW(g);

    return 0;
}
void PageRankW(Graph g, double d, double diffPR, int maxIterations){
    int i = 0;

    // log file
    FILE *fp;
    fp = stdin;
    fp = fopen("page_log.txt", "w");
    assert( fp != NULL );
    fprintf(fp, "d: %f | diffPR: %f | maxIterations: %d\n", d, diffPR, maxIterations);
    for(; i < g->nV; i+=1) {
        fprintf(fp, "%d ---> %s | out: ", i, g->adj[i].data);
        List tmp = g->adj[i].firstarc;
        for(;tmp; tmp=tmp->next){
            fprintf(fp, "|%s|", tmp->v);
        }
        fprintf(fp, "\n");
    }
    fprintf(fp, "----------\n");
    for(i=0; i < g->nV; i+=1) {
        fprintf(fp, "nodeid: %d     w_in: %d    w_out:%d\n", i, g->adj[i].w_in, g->adj[i].w_out);
    }
    fprintf(fp, "----------\n");

    // init iteration
    for (i=0; i < g->nV; i+=1) {
        g->adj[i].PR = (double)1/(double)g->nV;
        // debug
        // printf(" %.7f  \n", g->adj[i].PR);
    }

    int iteration = 0;
    double _diff = diffPR;
    double tmp_diff = 0;
    double sum = 0;
    int j = 0;
    while(iteration < maxIterations && _diff >= diffPR) {

        fprintf(fp, "------ iter: %d ------\n", iteration);
        for(i = 0; i <g->nV; i+=1) {
            // update pagerank
            sum = 0;
            for(j =0; j <g->nV; j+=1) {
                if(inLL(g->adj[j].firstarc, g->adj[i].data)) {
                    double tmp_out = (double)g->adj[i].w_out==0?0.5:g->adj[i].w_out;
                    double w_in = (double)g->adj[i].w_in/g->adj[j].sum_adjs_in;
                    double w_out =  (double)tmp_out/g->adj[j].sum_adjs_out;
                    sum += g->adj[j].PR * w_in * w_out;
                    fprintf(fp, "Win[%d][%d]=%f  Wout[%d][%d]=%f\n",j,i,w_in, j,i,w_out);
                }
            }
            g->adj[i].PR_ = (((double)1.0-d)/(double)g->nV) + (d * sum);
            // debug
            // printf("idx:%d, %.7f, %.7f  \n",i ,g->adj[i].PR_, g->adj[i].PR);
        }
        // calculate eps
        tmp_diff = 0;
        i = 0;
        for(; i < g->nV; i+=1) {
            tmp_diff += fabs(g->adj[i].PR - g->adj[i].PR_);
            g->adj[i].PR = g->adj[i].PR_;
        }
        _diff = tmp_diff;

        iteration++;
    }
    // log close
    fclose(fp);
}

void outputPageRankW(Graph g){
    FILE *fp;
    fp = stdin;
    fp = fopen("pagerankList.txt", "w");
    assert( fp != NULL );
    // lazy sort O(n^2)
    AdjList sortedList[MAX_VERTEX_NUM];
    bool isSorted[MAX_VERTEX_NUM] = {false};
    int i = 0, j = 0, sorted_i = 0;
    double maxPR = -1;
    int maxj = -1;
    for(; i<g->nV; i+=1){
        maxPR = -1;
        maxj = -1;
        for(j = 0;j<g->nV; j+=1) {
            if( maxPR<=g->adj[j].PR && isSorted[j]==false ) {
                maxPR = g->adj[j].PR;
                maxj = j;
            }
        }
        // debug
        // printf("%d %f",maxj,maxPR);
        sortedList[sorted_i].data = (char*)malloc(sizeof(char)*(strlen(g->adj[maxj].data)+1));
        strcpy(sortedList[sorted_i].data, g->adj[maxj].data);
        sortedList[sorted_i].PR = g->adj[maxj].PR;
        sortedList[sorted_i].w_out = g->adj[maxj].w_out;
        isSorted[maxj] = true;
        sorted_i += 1;
    }

    // output to file
    for(i=0; i<g->nV; i+=1){
        fprintf(fp, "%s, %d, %.7f\n", sortedList[i].data, sortedList[i].w_out, sortedList[i].PR);
    }

    fclose(fp);
}
