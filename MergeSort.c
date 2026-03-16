#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Sort.h"

static void merge_sort(size_t *tab_indices, size_t start, size_t end, void *tableau,
                                 int (*compare)(const void *, size_t, size_t)) ;
static void merge(size_t *tab_indices, size_t start, size_t mid, size_t end, void *tableau,
                  int (*compare)(const void *, size_t, size_t));



static void merge(size_t *tab_indices, size_t start, size_t mid, size_t end, void *tableau,
                  int (*compare)(const void *, size_t, size_t)) {
    size_t n1 = mid - start + 1; //nb element sous-tableau 1 (contient mid donc +1)
    size_t n2 = end - mid; //nb de element sous-tableau 2


    size_t *L = malloc(n1 * sizeof(size_t));
    if (L == NULL)
    {
        fprintf(stderr,"Malloc L1\n");
        return;
    } 
    size_t *R = malloc(n2 * sizeof(size_t));
    if (R == NULL)
    {
        fprintf(stderr,"Malloc R1\n");
        free(L);
        return;
    }

    //on sépare le tableaux des indices en 2 avec L[i] qui corespond à la partie à gauche du tableaux de départ et R[j] qui correspond aux tableaux de gauche.
    //recopiage dans les deux sous tableaux
    for (size_t i = 0; i < n1; i++){
    L[i] = tab_indices[start + i];
    
}
    
    for (size_t j = 0; j < n2; j++){ 
    R[j] = tab_indices[mid + 1 + j];
    
}
  

    size_t i = 0, j = 0, k = start;

    /* i<n1 et j<n2 correspond à L[n1 + 1] = ∞; R[n2 + 1] = ∞ et dans ce code, on va comparer les élemens des tableaux L et R pour les trier !!
     on compare les éléments des deux sous-tableaux (L et R) pour remplir 'tab_indices' avec le plus petit disponible à chaque étape, 
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

void sort(void *tableau, size_t length,
          int (*compare)(const void *, size_t i, size_t j),
          void (*swap)(void *tableau, size_t i, size_t j)) {
    
    if (length < 2) return;

    size_t *tab_indices = malloc(length * sizeof(size_t));
    if(!tab_indices)
    {
        fprintf(stderr,"Erreur malloc tab_indices");
        return;
    }
    //remplissage du tableau
    for (size_t i = 0; i < length; i++)
    {
        tab_indices[i] = i;
    }

    //Tri des indices
    merge_sort(tab_indices,0,length-1,tableau,compare);
    
    /*On parcourt le tableau d'indices triés et on déplace physiquement les données dans 'tableau' via la fonction 'swap'. Tant qu'un index n'est pas 
   à sa place, on échange l'élément actuel avec sa cible finale jusqu'à ce que tout soit aligné, puis on libère la mémoire.*/
    for (size_t i = 0; i < length; i++){
        
        if(tab_indices[i] == i) //déjà à la bonne place
            continue;
        size_t cible = tab_indices[i];
        swap(tableau, i, cible);
        //on place à la bonne place l'élément
        
        //mise à jour des éléments qui change de position
        for(size_t a = i+1; a < length; a++)
        {
            if(tab_indices[a] == i)
            {
                //printf("J'échange %zu avec %zu \n", tab_indices[i],tab_indices[a]);
                size_t temp = tab_indices[i];
                tab_indices[i] = tab_indices[a];
                tab_indices[a] = temp;
            }
        }
        
    }
    
    free(tab_indices);
}

/*Cette fonction divise le tableau en deux moitiés jusqu'à n'avoir que des éléments isolés (p >= r), 
puis elle remonte la récursion en fusionnant les morceaux via 'merge' pour reconstruire le tableau trié. */
static void merge_sort(size_t *tab_indices, size_t start, size_t end, void *tableau,
                                 int (*compare)(const void *, size_t, size_t)) {
    if (start < end) {
        size_t mid = start + (end - start) / 2; 
        merge_sort(tab_indices, start, mid, tableau, compare);
        merge_sort(tab_indices, mid + 1, end, tableau, compare);
        merge(tab_indices, start, mid, end, tableau, compare);
    }
}

