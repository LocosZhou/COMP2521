// crawl.c ... build a graph of part of the web
// Written by John Shepherd, September 2015
// Uses the cURL library and functions by Vincent Sanders
// <vince@kyllikki.org>

#include <ctype.h>
#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "graph.h"
#include "html.h"
#include "set.h"
#include "stack.h"
#include "url_file.h"

#define BUFSIZE 1024

static void setFirstURL (char *, char *);

int main (int argc, char **argv)
{
	URL_FILE *handle;
	char buffer[BUFSIZE];
	char baseURL[BUFSIZE];
	char firstURL[BUFSIZE];
	char next[BUFSIZE];
	int maxURLs;

	if (argc > 2) {
		strcpy (baseURL, argv[1]);
		setFirstURL (baseURL, firstURL);
		maxURLs = atoi (argv[2]);
		if (maxURLs < 40)
			maxURLs = 40;
	} else {
		fprintf (stderr, "Usage: %s BaseURL MaxURLs\n", argv[0]);
		exit (1);
	}

	// You need to modify the code below to implement:
	//
	// add firstURL to the ToDo list
	Queue ToDo = newQueue();
	enterQueue (ToDo, firstURL);
	// initialise Graph to hold up to maxURLs
	Graph newG = newGraph (maxURLs);
	// initialise set of Seen URLs
	Set seen = newStack ();
	insertInto(seen, firstURL);

	// while (ToDo list not empty and Graph not filled) {
	//    grab Next URL from ToDo list
	//    if (not allowed) continue
	//    foreach line in the opened URL {
	//       foreach URL on that line {
	//          if (Graph not filled or both URLs in Graph)
	//             add an edge from Next to this URL
	//          if (this URL not Seen already) {
	//             add it to the Seen set
	//             add it to the ToDo list
	//          }
	//       }
	//    }
	//    close the opened URL
	//    sleep(1)
	// }
	while (!emptyQueue (ToDo) && nVertices (newG) < maxURLs){
		char *curr_url = leaveQueue(ToDo);
		if (!(handle = url_fopen (firstURL, "r"))) {
			fprintf (stderr, "Couldn't open %s\n", next);
			exit (1);
		}
		while (!url_feof (handle)) {
			url_fgets (buffer, sizeof (buffer), handle);
			// fputs(buffer,stdout);
			int pos = 0;
			char next_url[BUFSIZE];
			memset (next_url, 0, BUFSIZE);
			
			while ((pos = GetNextURL (buffer, firstURL, next_url, pos)) > 0) {
				if(nVertices (newG) < maxURLs || isConnected (newG, curr_url, next_url)){
					addEdge(new_graph, cur_url, next_url);
					memset (next_url, 0, BUFSIZE);
				}
				if(!isElem(seen, next_url)){
					insertInto(seen, next_url);
					enterQueue(ToDo, next_url);
				}

			}
			url_fclose (handle);
			sleep (1);

	}
	printf("======================================================\n");
	printf("Display the graph: \n\n")
	showGraph (newG, 0);
	//showGraph (newG, 1);
	return 0;
}

// setFirstURL(Base,First)
// - sets a "normalised" version of Base as First
// - modifies Base to a "normalised" version of itself
static void setFirstURL (char *base, char *first)
{
	char *c;
	if ((c = strstr (base, "/index.html")) != NULL) {
		strcpy (first, base);
		*c = '\0';
	} else if (base[strlen (base) - 1] == '/') {
		strcpy (first, base);
		strcat (first, "index.html");
		base[strlen (base) - 1] = '\0';
	} else {
		strcpy (first, base);
		strcat (first, "/index.html");
	}
}
