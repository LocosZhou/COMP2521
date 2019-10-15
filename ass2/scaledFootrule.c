#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "scaledFootrule.h"

int main(int argc, char *argv[]) {
   // scan file
   int num_files = argc - 1;
   assert(num_files);
   int N = 0;
   for(int i = 0; i < num_files; i+=1) {
       FILE *fp;
       fp = fopen(argv[i+1], "r");
       assert(fp != NULL);
       char *url = malloc(sizeof(char)*100);
       List L = NULL;
       int count_cur_setT = 0;
       while (!feof(fp)) {
           fscanf(fp,"%s",url);
           L = insertLL(L, url);
           standP =insertLL(standP, url);
           count_cur_setT+=1;
       }
       setT[i] = reverseLL(L);
       free(url);
       url = NULL;
   }

   N = getLenLL(standP);
   // N!
   // use Backtrackink
   standP = reverseLL(standP);
   int setP[10] = {0};
   for(int i=0; i<N; i++){
       setP[i] = i+1;
   }
   double curw = 35526;
   double W = permute(setP, 0, N-1, num_files,0 ,curw);
   printf("%.6f\n", W);
   for(int i= 0; i<N; i++){
       printf("%s\n", getLLbyPos(standP, resP[i]-1)->v);
   }
}

void swap(int a[], int l, int i){
    int temp = a[l];
    a[l] = a[i];
    a[i] = temp;
}

double calW(int pVal, int pos, int num_files){
    int N = getLenLL(standP);
    List L = getLLbyPos(standP, pos);
    assert(L);
    double sum = 0;
    double p_N = (double) pVal/ (double) N;
    for(int i=0; i<num_files; i++){
        int n = getLenLL(setT[i]);
        int Tval = (getVerPos(setT[i], L->v)+1);
        double T_n = (double) Tval / (double)n;
        if(T_n == 0){
            continue ;
        }
        sum += fabs(T_n-p_N);
    }
    return sum;
}

double permute(int *a, int l, int r, int num_files, double preW, double W) {

    // Base case
    if (l == r){
//        debug
//        for(int i=0; a[i]!=0; i+=1){
//            printf("%d",a[i]);
//        }
        preW += calW(a[l], l, num_files);
//        printf(": %f\n",preW);

        return preW;

    }
    else
    {
        // Permutations made
        for (int i = l; i <= r; i++)
        {
            // Swapping done
            swap(a, l, i);
            double add = calW(a[l], l, num_files);
            preW += add;
            if(preW <= W){
                // cut
                // Recursion called
                double tmp_w = permute(a, l+1, r, num_files, preW, W);
                if(tmp_w<W){
                    W = tmp_w;
                    for(int k = 0; k<10; k++){
                        resP[k] = a[k];
                    }
                }
//                W = tmp_w<W?tmp_w: W;
            }
            //backtrack
            swap(a, i, l);
            preW -= add;

        }
    }
    return W;
}
