#include "Sort.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


static int partition(char A[], unsigned p, unsigned r){
    char x;
    int i,j;
    x = A[r];
    i = p-1;
    for (j = p; j <= r - 1; j++) {
        if (A[j]<= x)
            i = i+1;
            swap(A[], i, j);
    }
    swap(A[], i+1, r);

}return i+1;

void QuickSort( char A[], int p , int r){
   int q;
   if (p< r){
    q = partition(A, p, r);
    QuickSort(A,p, q-1); 
    QuickSort(A,q+1, r );
   }

}