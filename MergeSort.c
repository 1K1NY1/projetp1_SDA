#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sort.h"

static void merge(int *indices, size_t p, size_t q, size_t r, void *array,
                  int (*compare)(const void *, size_t, size_t)) {
    size_t n1 = q - p + 1;
    size_t n2 = r - q;

    int *L = malloc(n1 * sizeof(int));
    if (L == NULL) return NULL;
    int *R = malloc(n2 * sizeof(int));
     if (L == NULL) return NULL;

    for (size_t i = 0; i < n1; i++) L[i] = indices[p + i];
    for (size_t j = 0; j < n2; j++) R[j] = indices[q + 1 + j];

    size_t i = 0, j = 0, k = p;
    while (i < n1 && j < n2) {
        if (compare(array, L[i], R[j]) <= 0) {
            indices[k++] = L[i++];
        } else {
            indices[k++] = R[j++];
        }
    }
    while (i < n1) 
    indices[k++] = L[i++];
    while (j < n2)
     indices[k++] = R[j++];

    free(L); free(R);
}
void sort(void *array, size_t length,
          int (*compare)(const void *, size_t i, size_t j),
          void (*swap)(void *array, size_t i, size_t j)) {
    
    if (length < 2) return;

    int *indices = malloc(length * sizeof(int));
    for (size_t i = 0; i < length; i++) indices[i] = i;



static void merge_sort_recursive(int *indices, size_t p, size_t r, void *array,
                                 int (*compare)(const void *, size_t, size_t)) {
    if (p < r) {
        size_t q = p + (r - p) / 2; 
        merge_sort_recursive(indices, p, q, array, compare);
        merge_sort_recursive(indices, q + 1, r, array, compare);
        merge(indices, p, q, r, array, compare);
    }
}

    for (size_t i = 0; i < length; i++) {
        while (indices[i] != (int)i) {
            int cible = indices[i];

            swap(array, i, (size_t)cible);
            
            int temp = indices[i];
            indices[i] = indices[cible];
            indices[cible] = temp;
        }
    }
    free(indices);
}

