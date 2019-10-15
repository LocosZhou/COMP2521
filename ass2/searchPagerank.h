#ifndef searchPagerank_h
#define searchPagerank_h
#include "invertedTable.h"
#include <stdio.h>

List search_result(InvertedTable table[], List keywords, List PRL);
void output_search_result(List L);
List inputPageRankW(void);
#endif /* searchPagerank_h */
