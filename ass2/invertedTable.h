#ifndef invertedTable_h
#define invertedTable_h
#define MAX_VERTEX_NUM 100
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
// save InvertedIndex.txt
typedef struct InvertedTable {
    List urls;
    int  nV;
    char *data;
} InvertedTable;

void quicksort(InvertedTable a[], int low,int high);
void make_Inverted_Table(List);
void create_Inverted_Map_Table(InvertedTable []);

#endif /* invertedTable_h */
