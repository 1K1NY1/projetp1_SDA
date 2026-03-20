#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Terms.h"
#include "Sort.h"
#include "BinarySearch.h"
#include "AutoComplete.h"

static int compareWeight(const void * tab, size_t i, size_t j);
static int compareTerm(const void * tab, size_t i, size_t j);
static int compareKey(const void * tab, size_t i, void* key);
static void swap(void *array, size_t i, size_t j);


struct AC_t {
    TermArray *ta;
    char** WeightSorted;
    char sorted;
};



AC *acCreate(TermArray *ta)
{
    AC *ac = malloc(sizeof(AC));
    
	if (!ac) {
		fprintf(stderr, "acCreate: allocation error.\n");
		exit(1);
	}
    char** initial = malloc(sizeof(char*)*ta->length);
    if(!initial){
		fprintf(stderr, "acCreate: allocation error for initial.\n");
        free(ac);
		exit(1);
	}
    //recopiage du tableau initial
    for(size_t i = 0; i < ta->length; i++)
    {
        initial[i] = ta->array[i].text;
    }
    
	ac->ta = ta;
    ac->WeightSorted = initial;
    ac->sorted = 0;
    return ac;
}

void acFree(AC *ac)
{
    free(ac->WeightSorted);
    free(ac);
}

size_t acComplete(AC *ac, char *query, size_t k, char **results)
{
    /*
    1) Tri par ordre lexicographique.
    2) determination des m premiers termes dont la requête est un prefixe (recherche binaire)
    3) tri de cette liste de terme par ordre de points
    */
   ///

   //debug 
    /*
    FILE *logFile = fopen("retour.log", "a");
    if (logFile == NULL) {
        perror("Impossible d'ouvrir le fichier log");
        return 1;
    }
    freopen("debug.log", "a", stderr);
    //-----------------------------------------------------
    fprintf(logFile, "Nouvelle entrée\n");
    //-----------------------------------------------------
    */


    
    void* arr = ac->ta->array;
    size_t length = ac->ta->length;
    //Tri par ordre lexicographique
    if(ac->sorted == 0)
    {
        //fprintf(logFile, "Je trie pour la première fois\n");
        sort(arr,length , compareTerm, swap);
        ac->sorted = 1;
    }

    //Si recherche vide on reprends le tableau déjà trié
    if(query == NULL || *query == '\0') //optimise le temps si recherche vide (supposé que les éléments sont déjà trié par ordre de poids)
    {
        size_t i = 0;
        for(; i < k && i < length; i++)
            results[i] = ac->WeightSorted[i];
        return i;
    } 
    
    
    //-----------------------------------------------------
    //fprintf(logFile, "Tri OK\n");
    //-----------------------------------------------------
    //détermination des m premiers terme suffixe
    size_t first = 0;
    size_t last = length-1;

    first = binarySearchLow(arr,length,query,compareKey);
    last = binarySearchHigh(arr,length,query,compareKey);
    if(first > last)
        return 0;
    if(first == last)
        if(compareKey(arr,first,query) != 0) //si pas de clé dans le tableau
            return 0;
    //fprintf(logFile, "La recherche m'a amené à %ld et %ld\n",first,last);
    //-----------------------------------------------------
    //fprintf(logFile, "m premiers terme trouvé\n");
    //-----------------------------------------------------

    //tableau de travail contenant les m termes:
    size_t s_length = (last-first+1);
    Term* suffixs = malloc(sizeof(Term)* s_length);
    if(!suffixs)
    {
        //fprintf(stderr, "Erreur malloc: suffixs\n");
		exit(1);
    }
    for(size_t i = 0; i < s_length; i++)
        suffixs[i] = ((Term*)arr)[first + i];

    //Tri des poids
    sort(suffixs,s_length , compareWeight, swap);
    //-----------------------------------------------------
    //fprintf(logFile, "Tri des poids\n");
    //-----------------------------------------------------

    //remplissage de result
    size_t size  = 0;
    for(; size < k && size < s_length; size++)
    {
        results[size] = suffixs[size].text;
    }
    free(suffixs);
    //-----------------------------------------------------
    //fprintf(logFile, "Fin\n");
    //-----------------------------------------------------
    //fclose(logFile);
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
        
        comp++;
    }
    if (t[i].text[comp] != '\0' && t[j].text[comp] == '\0')
     return -1;
    if (t[i].text[comp] == '\0' && t[j].text[comp] != '\0')
     return 1;
    return 0;
}
static int compareWeight(const void * tab, size_t i, size_t j)
{
    //Comparaison par ordre de poids (décroissant)
    Term* t = (Term*)tab;
    if(t[i].weight > t[j].weight)
            return -1;
    if(t[i].weight < t[j].weight)
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