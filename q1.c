
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Terms.h"
#include "Sort.h"

static int compareWeight(const void * tab, size_t i, size_t j);
static int compareTerm(const void * tab, size_t i, size_t j);
static void swap(void *array, size_t i, size_t j);

void performanceTest(TermArray *ta, size_t k, FILE* fp, char*);

int main(int argc, char *argv[])
{
    if (argc < 4) {
        fprintf(stderr, "Usage: %s file k destination_csv\n", argv[0]);
        exit(1);
    }

    srand(time(NULL)); // Initialisation aléatoire réelle

    char *filename = argv[1];
    size_t k = atol(argv[2]);
    char *csv_name = argv[3];

    // Chargement des données
    TermArray *termarray1 = termsLoadFile(filename);
    if (!termarray1) return 1;
    TermArray *termarray2 = termsLoadFile(filename);
    if (!termarray2) return 1;

    printf("Fichier : %s (%ld termes)\n", filename, termarray1->length);

    // Ouverture du fichier de sortie CSV
    FILE* fp = fopen(csv_name, "w");
    if (fp == NULL) {
        perror("Erreur ouverture CSV");
        return 1;
    }

    // Lancer le test de performance
    performanceTest(termarray1, k, fp,"Poids");
    performanceTest(termarray2, k, fp,"Lexico");

    // Nettoyage
    fclose(fp);
    termsFree(termarray1);
    termsFree(termarray2);

    return 0;
}

// Fonction pour mesurer les performances
void performanceTest(TermArray *ta, size_t k, FILE* fp, char* category) {
    

    fprintf(fp, "temps\n"); // En-tête CSV

    // 3. Mesurer précisément le temps de acComplete
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    if(*category == 'L')
        sort(ta->array,ta->length,compareTerm,swap);
    else
        sort(ta->array,ta->length,compareWeight,swap);

    clock_gettime(CLOCK_MONOTONIC, &end);

    double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;


    // Calcul de la moyenne en millisecondes pour plus de lisibilité
    double average_time = (time_taken) * 1000.0;
    printf("Par %s: | Temps moyen : %.6f ms\n",category, average_time);
    
    // Écriture dans le CSV
    fprintf(fp, "%s;%.6f\n",category, average_time);
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
static void swap(void *array, size_t i, size_t j)
{
    //on suppose qu'on donne pas de pointeur vide
    Term* t = (Term*)array;
    Term temp = t[i];
    t[i] = t[j];
    t[j] = temp;
    return;
}