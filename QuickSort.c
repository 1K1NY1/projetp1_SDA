#include "Sort.h"
#include <stdlib.h>

static size_t partition(void* A[], size_t p, size_t r,
           int (*compare)(const void *, size_t i, size_t j),
           void (*swap)(void *array, size_t i, size_t j)) {
    
    size_t i, j;
    i = p;

    for (j = p; j < r; j++) {
        
        if (compare(A, j, r) <= 0) {
            swap(A, i, j);
            i = i + 1;
        }
    }
    swap(A, i, r);
    return i;
}

void QuickSort(void *A[], size_t p, size_t r,
               int (*compare)(const void *, size_t i, size_t j),
               void (*swap)(void *array, size_t i, size_t j)) {
    
    size_t q;
    if (p < r) {
       
        q = partition(A, p, r, compare, swap);

        if (q > 0) {
            QuickSort(A, p, q - 1, compare, swap);
        }
        QuickSort(A, q + 1, r, compare, swap);
    }
}