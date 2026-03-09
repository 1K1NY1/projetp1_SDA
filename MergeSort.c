#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void Merge(char A[],int p , int q , int r){
    int n1, n2;
    n1 = q-p+1;
    n2 = r-q;
    int k; 
    char L[n1], R[n2];
    for (int i = 1, i<=n1 ,i++)
    {
        L[i] = A[p+i-1];
    }
    for ( int j = 1 i<=n2 , j++)
    {
        R[j] = A[q + j];
    }
    L[n1]= INT_MAX; // sincèrement deepseek m'a dit que ça correspondait à l'infini pour un int donc c'est un sentinelle.
    R[n2]= INT_MAX;

    int i =0;
    int j =0; 
    for (int k = p ,k<=r,k++){
        if(L[i]<=R[j]){
            A[k]= L[i];
            i=i+1;}
            else {
                A[k]= R[j];
                j = j+1;
            }

    }
}