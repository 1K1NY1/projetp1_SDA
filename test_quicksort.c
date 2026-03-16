#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Sort.h"
void QuickSort(void *A, size_t p, size_t r,
               int (*compare)(const void *, size_t i, size_t j),
               void (*swap)(void *array, size_t i, size_t j));
               
// 1. Fonction de comparaison : respecte (const void *array, size_t i, size_t j)
int comparer_chaines(const void *array, size_t i, size_t j) {
    // On convertit l'argument array en tableau de pointeurs de caractères
    char **mots = (char **)array;
    // On compare les éléments aux indices i et j
    return strcmp(mots[i], mots[j]);
}

// 2. Fonction de swap : respecte (void *array, size_t i, size_t j)
void swap_pointeurs(void *array, size_t i, size_t j) {
    void **tab = (void **)array;
    void *temp = tab[i];
    tab[i] = tab[j];
    tab[j] = temp;
}

int main() {
    // Tableau de test
    char *mots[] = {"Zèbre", "Banane", "Pomme", "Abricot", "Datte", "Cerise"};
    size_t n = sizeof(mots) / sizeof(mots[0]);

    printf("Avant le tri :\n");
    for (size_t i = 0; i < n; i++) {
        printf("%s ", mots[i]);
    }
    printf("\n");

    // Appel de ton QuickSort (p=0, r=n-1)
    QuickSort((void **)mots, 0, n - 1, comparer_chaines, swap_pointeurs);

    printf("\nApres le tri :\n");
    for (size_t i = 0; i < n; i++) {
        printf("%s ", mots[i]);
    }
    printf("\n");

    return 0;
}