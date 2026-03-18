#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Sort.h"

// --- DEFINITIONS FORCEES ---
// On définit exactement ce que le compilateur doit voir
struct Term_t {
    char *name;
    long weight;
};
typedef struct Term_t Term;

struct TermArray_t {
    Term **terms;
    size_t length;
};
typedef struct TermArray_t TermArray;

// On déclare manuellement les fonctions dont on a besoin depuis Terms.c
extern TermArray *termsLoadFile(char *filename);
extern void termsFree(TermArray *ta);
// ----------------------------

int compare_lexico(const void *tableau, size_t i, size_t j) {
    Term **t = (Term **)tableau;
    return strcmp(t[i]->name, t[j]->name);
}

int compare_weight(const void *tableau, size_t i, size_t j) {
    Term **t = (Term **)tableau;
    if (t[i]->weight > t[j]->weight) return -1;
    if (t[i]->weight < t[j]->weight) return 1;
    return 0;
}

void swap_terms(void *tableau, size_t i, size_t j) {
    Term **t = (Term **)tableau;
    Term *temp = t[i];
    t[i] = t[j];
    t[j] = temp;
}

void run_benchmark(const char *filename, int criteria) {
    TermArray *ta = termsLoadFile((char *)filename);
    if (!ta) {
        printf("Erreur chargement %s\n", filename);
        return;
    }

    int (*cmp)(const void *, size_t, size_t) = (criteria == 1) ? compare_lexico : compare_weight;
    
    printf("Fichier: %s | Taille: %zu\n", filename, ta->length);

    clock_t start = clock();
    sort(ta->terms, ta->length, cmp, swap_terms); 
    clock_t end = clock();

    printf("==> Temps: %.6f s\n\n", (double)(end - start) / CLOCKS_PER_SEC);

    termsFree(ta);
}

int main(int argc, char *argv[]) {
    if (argc < 3) return 1;
    run_benchmark(argv[1], atoi(argv[2]));
    return 0;
}