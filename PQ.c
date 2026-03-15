#include "PQ.h"
#include <stdio.h>
#include <stdlib.h>

struct PQ_t {
    void **data;     // Tableau de pointeurs génériques
    size_t capacity; // Taille max (limitée)
    size_t size;     // Nombre d'éléments actuellement présents
    int (*compare)(const void *, const void *);
};

PQ *pqCreate(size_t capacity, int (*compare)(const void *, const void *)){
    
    PQ *pq= malloc(sizeof(PQ));
    if (!pq) return NULL;
    pq->data = malloc(capacity *sizeof(void*));
    if (!(pq->data)){free(pq);}
    return NULL;
    
    pq->capacity = capacity;
    pq->size=size;
    pq->compare = compare;
}

void pqFree(PQ* pq){
    if (pq!=NULL)
        free(pq->data);
        free(pq);
}
bool pqInsert(PQ* pq, void *obj){
    if (pq->size == pq->capacity){
    return false;}
    ///ici on va mettre l'objet dans le bas du tas
    size_t i = pq->size;
    pq->data[i] = obj;
    pq->size++;
    // on essaye de comparer les élements entre eux pour respecter l'ordre de Tas
    void *temp;
    while(i>0)
    {
        size_t i_parent = (i-1)/2;
    
        if (compare(pq->data[i],pq->data[i_parent]) <0)
        {
            temp = pq->data[i];
            pq->data[i_parent]=pq->data[i];
            pq->data[i]=temp;
        }else {break;}
        i = i_parent;
    }
    return true;

}

void *pqGetMax(const PQ* pq)
{
    if(!pq) return NULL;
    //on va aller regarder dans l'arbre l'indice de la valeur la plus grande
    return pq->data[0]; 
    
}

void *pqExtractMax(PQ* pq)
{
     if(!pq) return NULL;
        // on va sauvegarder la valeur max du tableau 
    void *max = pq->data[0];
     // on va prendre le dernier element du tas et le mettre en haut du tas
     pq->data[0]=pq->data[pq->size-1];
     // on décremente le tas 
     pq->size = pq->size-1;
    size_t i = 0;// l'indice du  parent
    while(true)
    {
    size_t gauche = 2*i+1;// l'indice de la gauche
    size_t droite =2*i+2;//l'indice de la droite
    size_t max = i;
    //si gauche est plus grand que le max_actuel, on les échanges
    if(gauche < pq->size && pq->compare(pq->data[gauche],pq->data[max])>0)
    {
        max = gauche;
    }
    //si droite est plus grand que le max_actuel, on les échanges
    if(droite < pq->size && pq->compare(pq->data[droite],pq->data[max])>0)
    {
        max = doite;
    }
    // puisque max n'est plus le max_actuel ,on échange et on continue à descendre
    if(max !=i){
        void *temp = pq->data[i];
        pq->data[i]=pq->data[max];
        pq->data[max]=temp;
        i=max;
    }else //sinon l'élement est à sa place, on arrête !
    {
        break;
    }
    }
    return max;
}

void pqReplaceMax(PQ *pq, void *obj)
{
    if(!pq) return NULL;
    pq->data[0] = obj;
    //si l'objet est plus petit que ces précedents on réarrange
    size_t i =0 ;
    while (true)
    {
        size_t gauche = 2 * i + 1;
        size_t droite = 2 * i + 2;
        size_t max = i;

        if (gauche < pq->size && pq->compare(pq->data[gauche], pq->data[max]) > 0) {
            max = gauche;
        }

        if (droite < pq->size && pq->compare(pq->data[droite], pq->data[max]) > 0) {
            max = droite;
        }

        if (max != i) {
            void *temp = pq->data[i];
            pq->data[i] = pq->data[max];
            pq->data[max] = temp;
            i = max;
        } else {
            break; // L'objet a trouvé sa place !
        }
    }    

}


size_t pqSize(const PQ* pq)
{
    if (pq == NULL)
    {
        return 0;
    }return pq->size;
}

size_t pqCapacity(const PQ* pq)
{
    if (pq==NULL) return 0;
    return pq->capacity;
}