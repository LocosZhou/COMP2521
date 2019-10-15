// getPeaks.c 
// Written by Ashesh Mahidadia, August 2017

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "DLList.h"


/* 
    You will submit only this one file.

    Implement the function "getPeaks" below. Read the exam paper for 
    detailed specification and description of your task.  

    - DO NOT modify code in the file DLList.h . 
    - You can add helper functions in this file.  
    - DO NOT add "main" function in this file. 
    
*/
static void AppendNode(DLList L, int val);

DLList getPeaks(DLList L){

	DLList peaksL = newDLList();
	if (DLListLength(L) < 3){
		return peaksL;
	}
	struct DLListNode *curr = L->first->next;
	while (curr->next != NULL) {
		if (curr->value > curr->next->value && curr->value > curr->prev->value){
			AppendNode(peaksL, curr->value);
		}
		curr = curr->next;
	}
	return peaksL;
}

static void AppendNode(DLList L, int val) {
	assert(L != NULL);
	struct DLListNode *new = newDLListNode(val);
	assert(new != NULL);

	if (DLListIsEmpty(L)) {
		L->first = L->curr = L->last = new;
	} else {
		L->last->next = new;
		new->prev = L->last;
		L->last = new;
	}
	L->nitems++;
}



