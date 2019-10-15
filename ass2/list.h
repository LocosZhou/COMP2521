//reference with lecture material week04a/exercises
#ifndef list_h
#define list_h

#include <stdio.h>
#include <stdbool.h>

typedef struct Node *List;

typedef struct Node {
    char*     v;
    double PR; // PR value
    struct Node *next;
} Node;


List insertLL(List, char*);// add new Node with node info
List insertLL_pr(List, char*, double); // add new Node with node info & pr value
bool inLL(List, char*); // string: X is in list
void freeLL(List); // free list
void showLL(List); // printf list info
int getLenLL(List); // get length of list
List getNode(List L, char *n); // get Node of list
List sort_pr(List L); // bubble sort
List reverseLL(List L); // reverse list
int getVerPos(List L, char *n); // get pos of string: X
List getLLbyPos(List L, int pos); // get Node by pos
#endif /* list_h */
