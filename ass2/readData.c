#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "readData.h"

List getCollection(void) {
    FILE* fp = fopen("collection.txt","r");
    assert( fp!=NULL );

    char * buffer = malloc(sizeof(char)*100);
    List cur_ptr = NULL;
    while ( fscanf(fp,"%s", buffer)!=EOF ) {
        //    debug
//        printf("file string:[%s]\n", buffer);
        cur_ptr = insertLL(cur_ptr, buffer);
    }
    //    debug
//    showLL(cur_ptr);
//    printf("%d",getLenLL(cur_ptr));
    fclose(fp);
    return cur_ptr;
}

Graph getGraph(List L){
    Graph g = newGraph(L);
    List tmp = L;
    while(tmp!=NULL) {
        char * file_name;
        // before defined url.length <= 100
        file_name = malloc(105 * sizeof(char));
        strcpy(file_name, tmp->v);
        strcat(file_name, ".txt");
        // debug
//        printf("%s\n", file_name);
        FILE *fp = fopen(file_name, "r");
        assert( fp != NULL );

        char line[1000] = "\0";
        while (fgets(line, 1000, fp) != NULL) {
            if (strcmp(line, "#start Section-1\n") == 0) {
                char *url = malloc(sizeof(char)*100);
                while(fscanf(fp, "%s", url)){
                    if(strcmp(url, "#end") == 0)
                        break;
                    if(strcmp(tmp->v, url) != 0){
                        // easy ignore
                        insertEdge(g, tmp->v, url);
                    }
                }
                if(strcmp(url, "#end") == 0)
                    break;
                free(url);
                url = NULL;
            }
        }
        fclose(fp);
        free(file_name);
        file_name = NULL;
        tmp = tmp->next;
    }

    return g;
}
