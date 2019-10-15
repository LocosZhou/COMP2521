//reference with lecture material week04a/exercises
#include "list.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Node *makeNode(char* n) {
    Node *new = malloc(sizeof(Node));
    assert(new != NULL);
    new->v = (char*)malloc(sizeof(char)*(strlen(n)+1));
    strcpy(new->v, n);
    new->next = NULL;
    new->PR = 0;
    return new;
}

Node *makeNode_pr(char* n, double w) {
    Node *new = malloc(sizeof(Node));
    assert(new != NULL);
    new->v = (char*)malloc(sizeof(char)*(strlen(n)+1));
    strcpy(new->v, n);
    new->next = NULL;
    new->PR = w;
    return new;
}

List insertLL(List L, char* n) {
    if (inLL(L, n))
        return L;

    // add new node at the beginning
    Node *new = makeNode(n);
    new->next = L;
    return new;
}

List insertLL_pr(List L, char* n, double w){
    if (inLL(L, n))
        return L;

    // add new node at the beginning
    Node *new = makeNode_pr(n, w);
    new->next = L;
    return new;
}


bool inLL(List L, char* n) {
    if (L == NULL)
        return false;
    if ( strcmp(L->v, n) == 0 )
        return true;
    return inLL(L->next, n);
}

void showLL(List L) {
    if (L == NULL)
        putchar('\n');
    else {
        printf("%s ", L->v);
        showLL(L->next);
    }
}

void freeLL(List L) {
    if (L != NULL) {
        freeLL(L->next);
        free(L);
        L = NULL;
    }
}

List getNode(List L, char *n) {
    if (L == NULL)
        return NULL;
    if ( strcmp(L->v, n) == 0 )
        return L;
    return getNode(L->next, n);
}

int getLenLL(List L) {
    int count =0;
    List tmp = L;
    for( ; tmp!=NULL; tmp=tmp->next,count+=1);
    return count;
}


List sort_pr(List L){
    if(L == NULL || L->next == NULL)return L;
    List head = insertLL(L, "head");
    List maxNode = L;
    List tmp = L->next;
    List prev = L;
    List maxPrev =NULL;
    int curlen = getLenLL(L);
    int count = 0;
    int arranged = 0;
    bool isChange = true;
    while(isChange){
        isChange = false;
        count = 0;
        tmp = head->next;
        prev = head;
        maxNode = head->next;
        maxPrev = head;
        while(tmp){
            if(tmp->PR<maxNode->PR){
                maxPrev = prev;
                maxNode = tmp;
                isChange = true;
            }
            count += 1;

            if (count == curlen - arranged){
                break;
            }
            prev = tmp;
            tmp = tmp->next;
        }
        if(maxNode->next != tmp){
            List _tmp = NULL;
            _tmp = maxNode->next;
            maxNode->next = tmp->next;
            prev->next = maxNode;
            maxPrev->next = tmp;
            tmp->next = _tmp;
        }else{
            maxPrev->next=tmp;
            maxNode->next = tmp->next;
            tmp->next = maxNode;
        }
        arranged+=1;
//        printf("--------------------\n");
//        showLL(head);
    }
    return head->next;
}

List reverseLL(List L){
    List new = NULL;
    List head = L;
    while(L){
        new = insertLL(new, L->v);
        L = L->next;
    }
    freeLL(head);
    return new;
}

int getVerPos(List L, char *n){
    int count = 0;
    while(L){
        if(strcmp(n, L->v) == 0){
            return count;
        }
        count += 1;
        L = L -> next;
    }
    if(L==NULL){
        return -1;
    }
    return count;
}

List getLLbyPos(List L, int pos){
    int count = 0;
    while(L){
        if(pos == count){
            return L;
        }
        L = L->next;
        count +=1;
    }
    if(L){
        return NULL;
    }
    return L;
}
