#include "searchPagerank.h"
#include "readData.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

int main(int argc, const char * argv[]) {
    // If invertedIndex.txt not exists, do it
    List L = getCollection();
    make_Inverted_Table(L);

    int count_keywords = argc - 1;
    List keywords = NULL;
    int i = 0;
    char *keyword = malloc(sizeof(char)*1000);
    for(; i < count_keywords; i++){
        keyword = strcpy(keyword, argv[i+1]);
        keywords = insertLL(keywords, keyword);
    }
    free(keyword);
    keyword = NULL;
    // showLL(keywords);
    assert(keywords!=NULL);
    // read invertIndex
    InvertedTable table[1000];
    create_Inverted_Map_Table(table);

    // read pageranklist
    List PRL = inputPageRankW();

    // search all url by keywords
    List res = search_result(table,  keywords, PRL);

    // sort by pr
    List sorted_res = sort_pr(res);

    // output to shell
    output_search_result(sorted_res);

}

List search_result(InvertedTable table[], List keywords, List PRL){
    List L = NULL;
    List tmp_k = keywords;
    for(; tmp_k; tmp_k = tmp_k->next){
        for(int i = 0; i<1000; ){
            if(strcmp(tmp_k->v, table[i].data) > 0){
                i+=1;
            }else if(strcmp(tmp_k->v, table[i].data) ==0){
                for(List url=table[i].urls; url; url = url->next){
                    List cur_url_node = getNode(PRL, url->v);
                    if(cur_url_node){
                         L = insertLL_pr(L, url->v, cur_url_node->PR);
                    }
                }
                break;
            }else{
                printf("CAN'T FIND %s", tmp_k->v);
                break;
            }
        }
    }
    return L;
}

void output_search_result(List L){
    List tmp =L;
    int count = 30;
    while(tmp){
        printf("%s\n", tmp->v);
        tmp = tmp ->next;
        count -=1;
        if(count == 0)
            break;
    }
}

List inputPageRankW(void){
    FILE *fp;
    fp = fopen("pagerankList.txt", "r");
    assert( fp!=NULL );
    List L = NULL;
    char *url = malloc(sizeof(char)*100) ;
    int outLinks;
    double PR;
    while (!feof(fp)) {
        //    debug
        fscanf(fp,"%s %d, %lf",url,&outLinks,&PR );
        char *ture_url = malloc(sizeof(char)*100);
        for(int j=0; url[j]!=','&&j<100; j+=1){
            ture_url[j] = url[j];
        }
        //        printf("PR file string:[%s, %d, %.7f]\n", ture_url, outLinks, PR);
        L = insertLL_pr(L, ture_url, PR);
        free(ture_url);
        ture_url = NULL;
    }
    free(url);
    url = NULL;
    fclose(fp);
    return L;
}
