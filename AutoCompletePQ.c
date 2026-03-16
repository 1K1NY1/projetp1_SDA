#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Terms.h"
#include "Sort.h"
#include "BinarySearch.h"
#include "AutoComplete.h"
#include "PQ.h"

static int compareTerm(const void * tab, size_t i, size_t j);
static int compareKey(const void * tab, size_t i, void* key);
static int comparePriority(const void * p1,const void * p2);

static void swap(void *array, size_t i, size_t j);

struct AC_t {
    TermArray *ta;
    bool sorted; //definis si le tableau est deja trié par ordre lexicographique
};

AC *acCreate(TermArray *ta)
{
    AC *ac = malloc(sizeof(AC));

	if (!ac) {
		fprintf(stderr, "acCreate: allocation error.\n");
		exit(1);
	}

	ac->ta = ta;
    ac->sorted = false;

    return ac;
}

void acFree(AC *ac)
{
    free(ac);
}

size_t acComplete(AC *ac, char *query, size_t k, char **results)
{
    /*
    1) Tri par ordre lexicographique.
    2) determination des m premiers termes dont la requête est un prefixe (recherche binaire)
    3) file à priorité
    */
    /*
    FILE *logFile = fopen("retour.log", "a");
    if (logFile == NULL) {
        perror("Impossible d'ouvrir le fichier log");
        return 1;
    }
    freopen("debug.log", "a", stderr);*/
    //-----------------------------------------------------
    //fprintf(logFile, "Nouvelle entrée\n");
    //-----------------------------------------------------



    
    void* arr = ac->ta->array;
    size_t length = ac->ta->length;
   //Tri par ordre lexicographique
    if(!ac->sorted)
        sort(arr,length , compareTerm, swap);
    ac->sorted = 1;
    
    //détermination des m premiers terme suffixe
    size_t first = 0;
    size_t last = length-1;
    if(query == NULL || *query != '\0') //optimise le temps si recherche vide
    {
        first = binarySearchLow(arr,length,query,compareKey);
        last = binarySearchHigh(arr,length,query,compareKey);
    }   
    if(first > last)
        return 0;
    if(first == last)
        if(compareKey(arr,first,query) != 0) //si pas de clé dans le tableau
            return 0;
    //fprintf(logFile, "First: %ld, Last: %ld\n",first,last);
    //tableau de travail contenant les m termes:
    size_t s_length = (last-first+1);
    //fprintf(logFile, "s_length: %ld\n",s_length);
    if(s_length <= 0) //evite des potentiels problemes
        return 0;
    Term* suffixs = malloc(sizeof(Term)* s_length);
    if(!suffixs)
    {
        fprintf(stderr, "Erreur malloc: suffixs\n");
		exit(1);
    }
    for(size_t i = 0; i < s_length; i++)
        suffixs[i] = ((Term*)arr)[first + i];

    //Tri des poids
    //Implementation de PQ
    PQ* pq = pqCreate(k,comparePriority);
    if(!pq)
    {
        fprintf(stderr, "Erreur de creation PQ\n");
		exit(1);
    }

    //initialisation
    pqInsert(pq,&suffixs[0]);
    //fprintf(logFile, "Remplissage de la pq\n");
    for(size_t i = 1; i < s_length; i++)
    {
        
        if(pqInsert(pq,&suffixs[i]) == false) //insère si on n'y arrive pas soit on remplace le max, so
        {
            //fprintf(logFile, "Plus de place \n");
            if(suffixs[i].weight > ((Term*)pqGetMax(pq))->weight) //remplace par un meilleur terme
            {
                //fprintf(logFile, "Je remplace un poids de %ld par %ld \n",((Term*)pqGetMax(pq))->weight,suffixs[i].weight);
                pqReplaceMax(pq,&suffixs[i]);
            }
        }

        
    }
    //A ce stade on doit avoir une liste de maximum k 

    //Remplissage du tableau final (dans le sens inverse)
    size_t size = pqSize(pq);
    size_t a = 0;
    for(; a < size && a < k;a++)
    {
        if(size >= k)
            results[k-1-a] = ((Term*)pqExtractMax(pq))->text;
        else
            results[size-1-a] = ((Term*)pqExtractMax(pq))->text; //au cas où on a m < k
    }
    free(suffixs);
    pqFree(pq);
    //fclose(logFile);
    return a;
}
static int comparePriority(const void * Term1,const void * Term2)
{
    Term* t1 = (Term*)Term1;
    Term* t2 = (Term*)Term2;
    //(1/t1) < (1/t2) => t1 > t2
    if(t1->weight < t2->weight)
        return 1;
    if(t1->weight > t2->weight)
        return -1;
    return 0;
}
static int compareTerm(const void * tab, size_t i, size_t j)
{
    //Comparaison par ordre lexicographique (de deux termes du tableau)
    Term* t = (Term*)tab;
    size_t comp = 0;
    while(t[i].text[comp] != '\0' && t[j].text[comp] != '\0')
    {
        if(t[i].text[comp] < t[j].text[comp])
            return -1;
        if(t[i].text[comp] > t[j].text[comp])
            return 1;
        
        comp++;
    }
    if (t[i].text[comp] != '\0' && t[j].text[comp] == '\0')
     return -1;
    if (t[i].text[comp] == '\0' && t[j].text[comp] != '\0')
     return 1;
    return 0;
}
static int compareKey(const void * tab, size_t i, void* key)
{
    //Comparaison par ordre lexicographique (un terme et la clé)
    Term* t = (Term*)tab;
    char* string_key = (char*)key;
    size_t comp = 0;
    while(t[i].text[comp] != '\0' && string_key[comp] != '\0')
    {
        if(t[i].text[comp] < string_key[comp])
            return -1;
        if(t[i].text[comp] > string_key[comp])
            return 1;
        
        comp++;
    }
    if (string_key[comp] == '\0') //match
        return 0;
    return -1; //texte terminé mais pas la clé
}
static void swap(void *array, size_t i, size_t j)
{
    //on suppose qu'on donne pas de pointeur vide
    Term* t = (Term*)array;
    Term temp = t[i];
    t[i] = t[j];
    t[j] = temp;
    return;
}