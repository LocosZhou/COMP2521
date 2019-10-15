// testList.c - testing DLList data type
// Written by John Shepherd, March 2013

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "DLList.h"

int main (void)
{
	printf("===TESTING===\n\n");
	printf("===TEST 01 : Start from an empty list===\n");
	DLList myList = getDLList (stdin);
	putDLList (stdout, myList);
	assert (validDLList (myList));

	// TODO: more tests needed here

	freeDLList (myList);
	return EXIT_SUCCESS;
}
/*
void printState(DLList L){

}
*/
