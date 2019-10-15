#include "invertedTable.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void create_Inverted_Map_Table(InvertedTable table[]){
    FILE *fp;
    fp = fopen("invertedIndex.txt", "r");
    assert( fp!=NULL );

    // reads lines of file
    char line[1000] = "\0";
    int i = 0;
    while (fgets(line, 1000, fp) != NULL) {
        char * pch;
        // split by white space
        pch = strtok (line," ");
        table[i].data = malloc(sizeof(char)*100);
        strcpy(table[i].data, pch);
        table[i].nV = 0;
        table[i].urls = NULL;
        pch = strtok (NULL, " ");
        while (pch != NULL)
        {
            if(strcmp(pch, " ")!=0&&strcmp(pch, "\t")!=0&&*pch!= '\n'){
                //debug
            //    printf ("add url: %s\n",pch);
                for(int i = 0; pch[i]; i++){
                    if(pch[i]=='\n'){
                        pch[i] = '\0';
                        break;
                    }
                }
                table[i].urls = insertLL(table[i].urls, pch);
            }
            pch = strtok (NULL, " ");
        }
        i+=1;
    }
    return;
}

//sorting
void quicksort(InvertedTable a[], int low,int high)
{
    int i = low;
    int j = high;
    InvertedTable tmp;
    tmp.data = malloc(sizeof(char)*500);
    strcpy(tmp.data, a[i].data);
    tmp.urls = a[i].urls;
    if( low > high)
    {
        return ;
    }
    while(i < j)
    {
        while(strcmp(a[j].data, tmp.data)>=0 && (i < j))
        {
            j--;
        }
        if(i==j) break;
        strcpy(a[i].data,a[j].data);
        a[i].urls = a[j].urls;
        while(strcmp(a[i].data, tmp.data)<=0 && (i < j))
        {
            i++;
        }
        if(i==j) break;
        strcpy(a[j].data, a[i].data);
        a[j].urls = a[i].urls;
    }
    strcpy(a[i].data, tmp.data);
    a[i].urls = tmp.urls;
    quicksort(a,low,i-1);
    quicksort(a,j+1,high);
}

void make_Inverted_Table(List L){
    List tmp = L;
    InvertedTable table[1000];
    for(int i =0; i<1000; i+=1){
        table[i].data = "\0";
//        table[i].data = "\0";
        table[i].urls = NULL;
    }
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
            if (strcmp(line, "#start Section-2\n") == 0) {

                while (fgets(line, 1000, fp) != NULL)
                {
                    if(strcmp(line, "#end Section-2\n") == 0) break;
                    char * pch;
                    pch = strtok(line, " ");
                    while (pch != NULL)
                    {
                        if(strcmp(pch, " ")!=0&&strcmp(pch, "\t")!=0&&*pch!= '\n'){
                            for(int i = 0; pch[i]; i++){
                                if(pch[i]=='\n' || pch[i]=='.'){
                                    pch[i] = '\0';
                                    break;
                                }
                                pch[i] = tolower(pch[i]);
                            }
//                            printf ("add words: %s\n", pch);
                            for(int i = 0; i<1000; i+=1) {
                                if(strcmp(table[i].data, pch)==0 || strcmp(table[i].data, "\0")==0){
                                    table[i].urls = insertLL(table[i].urls, tmp->v);
                                    if(strcmp(table[i].data, "\0")==0){

//                                        printf ("add words: %s\n", pch);
                                        table[i].data = malloc(sizeof(char)*500);
                                        strcpy(table[i].data, pch);
                                    }
                                    break;
                                }
                            }
                        }
                        pch = strtok (NULL, " ");
                    }
                }
            }
        }
        fclose(fp);
        free(file_name);
        file_name = NULL;
        tmp = tmp->next;
    }
    int length = 0;
    for(int i = 0; i<1000; i++,length+=1){
        if(strcmp(table[i].data, "\0")==0) break;
    }

    quicksort(table, 0, length-1);

    FILE *fp;
    fp = stdin;
    fp = fopen("invertedIndex.txt", "w");
    for(int i = 0; i<length; i++){
        fprintf(fp, "%s", table[i].data);
        List tmp = table[i].urls;
        while(tmp){
            fprintf(fp, " %s", tmp->v);
            tmp = tmp->next;
        }
        fprintf(fp, "\n");

        free(table[i].data);
        table[i].data = NULL;
        freeLL(table[i].urls);
    }
    fclose(fp);

}
