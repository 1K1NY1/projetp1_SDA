#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static void Merge(char A[],int p , int q , int r){
    int n1, n2;
    n1 = q-p+1;
    n2 = r-q;
    int i,j;
    int k; 
    char L[n1], R[n2];
    for (i = 1, i<=n1 ,i++)
    {L[i] = A[p+i-1];}
    for ( j = 1 i<=n2 , j++)
    {R[j] = A[q + j];}
    L[n1]= INT_MAX; // sincèrement deepseek m'a dit que ça correspondait à l'infini pour un int donc c'est un sentinelle.
    R[n2]= INT_MAX;
    
    
}