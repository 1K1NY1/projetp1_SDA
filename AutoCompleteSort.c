#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Terms.h"
#include "Sort.h"
#include "BinarySearch.h"
#include "AutoComplete.h"

static void compare(const void * tab, size_t i, void * key);
static void swap(void *array, size_t i, size_t j);

struct AC_t {
    TermArray *ta;
    TermArray *SearchArray; //contient les m éléments de la recherche
};

AC *acCreate(TermArray *ta)
{
    AC *ac = malloc(sizeof(AC));

	if (!ac) {
		fprintf(stderr, "acCreate: allocation error.\n");
		exit(1);
	}

	ac->ta = ta;

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
    3) tri de cette liste de terme par ordre de points
    */
    void* arr = ac->ta->array;
    size_t length = ac->ta->length;
   //Tri par ordre lexicographique
    sort(arr,length , compareTerm, swap);

    //détermination des m premiers terme suffixe
    size_t first = binarySearchLow(arr,length,query,compareKey);
    size_t last = binarySearchHigh(arr,length,query,compareKey);

    //tableau de travail contenant les m termes:
    size_t s_length = (last-first+1);
    Term* suffixs = malloc(sizeof(Term)* s_length);
    if(!suffixs)
    {
        fprintf(stderr, "Erreur malloc: suffixs\n");
		exit(1);
    }
    for(size_t i = 0; i < s_length; i++)
        suffixs[i] = ((Term*)arr)[first + i];

    //Tri des poids
    sort(suffixs,s_length , compareWeight, swap);

    //remplissage de result
    size_t size  = 0;
    for(; size < k && size < s_length; size++)
    {
        results[size] = suffixs[size].text;
    }
    free(suffixs);
    return size;
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
        //sinon égaux : potentiel problème si pas la même taille (ici il ne se passera rien, on considère qu'il seront égaux)
        comp++;
    }
    return 0;
}
static int compareWeight(const void * tab, size_t i, size_t j)
{
    //Comparaison par ordre de poids
    Term* t = (Term*)tab;
    size_t comp = 0;
    if(t[i].weight < t[j].weight)
            return -1;
    if(t[i].weight > t[j].weight)
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
        //sinon égaux : potentiel problème si pas la même taille (ici il ne se passera rien, on considère qu'il seront égaux)
        comp++;
    }
    return 0;
}
static void swap(void *array, size_t i, size_t j)
{
    //on suppose qu'on donne pas de pointeur vide
    Term* t = (Term*)array;
    Term temp = t[i];
    t[i] = t[j];
    t[j] = temp;
    return 0;
}