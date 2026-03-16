#include "Sort.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static size_t partition(void* tab, size_t p, size_t r,
                        int (*compare)(const void *, size_t i, size_t j),
                        void (*swap)(void *tableau, size_t i, size_t j));
static void QuickSort( void* tab, size_t p , size_t r,
                int (*compare)(const void *, size_t i, size_t j),
                void (*swap)(void *tableau, size_t i, size_t j));



static size_t partition(void* tab, size_t p, size_t r,
                        int (*compare)(const void *, size_t i, size_t j),
                        void (*swap)(void *tableau, size_t i, size_t j))
{
    size_t i,j;
    i = p;
    for (j = p; j <= r - 1; j++) {
        if (compare(tab,j,r) <= 0)
        {
            swap(tab, i, j);
            i = i+1;
    
        }
            
    }
    swap(tab, i, r);
    return i;
}

static void QuickSort( void* tab, size_t p , size_t r,
                int (*compare)(const void *, size_t i, size_t j),
                void (*swap)(void *tableau, size_t i, size_t j))
{
   size_t q;
   if (p < r && r != (size_t)-1)
   { 
    q = partition(tab, p, r,compare,swap);
    if(q>0)
        QuickSort(tab,p, q-1,compare,swap); 
    QuickSort(tab,q+1, r,compare,swap);
   }

}

void sort(void *tableau, size_t length,
          int (*compare)(const void *, size_t i, size_t j),
          void (*swap)(void *tableau, size_t i, size_t j)) 
{
    //Quicksort
    if (length < 2) //tableau trop petit
        return;
    QuickSort(tableau,0,length-1,compare,swap);
}
