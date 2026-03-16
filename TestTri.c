#include <stdio.h>
#include <stdbool.h>
#include "Sort.h"

static int compare_int(const void *array, size_t i, size_t j);
static void swap_int(void *array, size_t i, size_t j);
// Comparaison pour des entiers
static int compare_int(const void *array, size_t i, size_t j) {
    int *tab = (int *)array;
    if (tab[i] < tab[j]) return -1;
    if (tab[i] > tab[j]) return 1;
    return 0;
}

// Échange pour des entiers
static void swap_int(void *array, size_t i, size_t j) {
    int *tab = (int *)array;
    int temp = tab[i];
    tab[i] = tab[j];
    tab[j] = temp;
}


void print_array(int *arr, size_t size)
{
    printf("[");
    for (size_t i = 0; i < size; i++) printf("%d%s", arr[i], (i < size - 1) ? ", " : "");
    printf("]\n");
}

bool is_sorted(int *arr, size_t size) {
    for (size_t i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i+1]) return false;
    }
    return true;
}

static void test_algorithm(const char *name) {
    printf("--- Test de : %s ---\n", name);

    // Cas 1 : Normal
    int normal[] = {64, 34, 25, 12, 22, 11, 90};
    print_array(normal,7);
    size_t n1 = 7;
    sort(normal, n1, compare_int, swap_int);
    print_array(normal,n1);
    printf("Normal  : %s\n", is_sorted(normal, n1) ? "SUCCÈS" : "ÉCHEC");

    // Cas 2 : Déjà trié
    int sorted[] = {1, 2, 3, 4, 5};
    print_array(sorted,5);
    size_t n2 = 5;
    sort(sorted, n2, compare_int, swap_int);
    print_array(sorted,n2);
    printf("Déjà trié: %s\n", is_sorted(sorted, n2) ? "SUCCÈS" : "ÉCHEC");

    // Cas 3 : Inversé
    int reversed[] = {5, 4, 3, 2, 1};
    size_t n3 = 5;
    print_array(reversed,n3);
    sort(reversed, n3, compare_int, swap_int);
    print_array(reversed,n3);
    printf("Inversé : %s\n", is_sorted(reversed, n3) ? "SUCCÈS" : "ÉCHEC");

    // Cas 4 : Taille 1 (Cas limite)
    int singleT[] = {42};
    sort(singleT, 1, compare_int, swap_int);
    print_array(singleT,1);
    printf("Taille 1: %s\n", is_sorted(singleT, 1) ? "SUCCÈS" : "ECHEC");

    // Cas 5 : Vide (Cas critique)
    sort(NULL, 0, compare_int, swap_int);
    printf("Taille 0: SUCCÈS (Pas de crash)\n");

    // Cas 6 : Doublons
    int dupes[] = {3, 1, 2, 1, 3, 2};

    size_t n6 = 6;
    print_array(dupes,n6);
    sort(dupes, n6, compare_int, swap_int);
    print_array(dupes,n6);
    printf("Doublons: %s\n", is_sorted(dupes, n6) ? " SUCCÈS" : "ÉCHEC");

    printf("\n");
}

int main() {
    // Remplacez 'quickSort' et 'mergeSort' par les noms exacts de vos fonctions
    test_algorithm("SortAlgo");

    
    return 0;
}
