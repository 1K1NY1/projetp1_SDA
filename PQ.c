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
    size_t ind = pq->size;
    pq->size++;
    while (ind>0)
    {
        size_t ind_parent = (ind-1)/2;
        if(compare(pq->data[ind],pq->data[ind_parent]))
        {
            
        }
    }
    
}

void *pqExtractMax(PQ* pq)
{

}

void pqReplaceMax(PQ *pq, void *obj)
{

}


size_t pqSize(const PQ* pq)
{

}

size_t pqCapacity(const PQ* pq)
{

}