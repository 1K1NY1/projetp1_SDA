#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sort.h"

static void merge(int *tab_indices, size_t p, size_t q, size_t r, void *tableau,
                  int (*compare)(const void *, size_t, size_t)) {
    size_t n1 = q - p + 1;
    size_t n2 = r - q;

    int *L = malloc(n1 * sizeof(int));
    if (L == NULL) return NULL;
    int *R = malloc(n2 * sizeof(int));
     if (L == NULL) return NULL;

    //on sépare le tableaux des indices en 2 avec L[i] qui corespond à la partie à gauche du tableaux de départ et R[j] qui correspond aux tableaux de gauche.
    for (size_t i = 0; i < n1; i++){
    L[i] = tab_indices[p + i];}

    for (size_t j = 0; j < n2; j++){ 
    R[j] = tab_indices[q + 1 + j];}

    size_t i = 0, j = 0, k = p;

    /* i<n1 et j<n2 correspond à L[n1 + 1] = ∞; R[n2 + 1] = ∞ et dans ce code, on va comparer les élemens des tableaux L et R pour les trier !!
    /* on compare les éléments des deux sous-tableaux (L et R) pour remplir 'tab_indices' avec le plus petit disponible à chaque étape, 
   puis on copie les éléments restants de la pile non vide pour finaliser. */
    while (i < n1 && j < n2) {
        if (compare(tableau, L[i], R[j]) <= 0) {
            tab_indices[k++] = L[i++];
        } else {
            tab_indices[k++] = R[j++];
        }
    }
    while (i < n1) 
    tab_indices[k++] = L[i++];
    while (j < n2)
     tab_indices[k++] = R[j++];

    free(L); 
    free(R);
}
/*  Si le tableau contient moins de 2 éléments, aucun tri n'est nécessaire.
Sinon, on alloue et on remplit un tableau d'indices qui servira de base pour trier les éléments sans déplacer les données réelles immédiatement. */
void sort(void *tableau, size_t length,
          int (*compare)(const void *, size_t i, size_t j),
          void (*swap)(void *tableau, size_t i, size_t j)) {
    
    if (length < 2) return;

    int *tab_indices = malloc(length * sizeof(int));
    for (size_t i = 0; i < length; i++)
    {tab_indices[i] = i};
    /*On parcourt le tableau d'indices triés et on déplace physiquement les données dans 'tableau' via la fonction 'swap'. Tant qu'un index n'est pas 
   à sa place, on échange l'élément actuel avec sa cible finale jusqu'à ce que tout soit aligné, puis on libère la mémoire.*/
    for (size_t i = 0; i < length; i++){
        /*on met des paranthèses sur le int avant le i pour dire que le i devient un entier*/
        while (tab_indices[i] != (int)i) {
            int cible = tab_indices[i];

            swap(tableau, i, (size_t)cible);

            int temp = tab_indices[i];
            tab_indices[i] = tab_indices[cible];
            tab_indices[cible] = temp;
        }
    }
    free(tab_indices);
}

/*Cette fonction divise le tableau en deux moitiés jusqu'à n'avoir que des éléments isolés (p >= r), 
puis elle remonte la récursion en fusionnant les morceaux via 'merge' pour reconstruire le tableau trié. */
static void merge_sort(int *tab_indices, size_t p, size_t r, void *tableau,
                                 int (*compare)(const void *, size_t, size_t)) {
    if (p < r) {
        size_t q = p + (r - p) / 2; 
        merge_sort(tab_indices, p, q, tableau, compare);
        merge_sort(tab_indices, q + 1, r, tableau, compare);
        merge(tab_indices, p, q, r, tableau, compare);
    }
}

