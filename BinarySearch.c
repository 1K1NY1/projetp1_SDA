#include <stdio.h>

#include "BinarySearch.h"

/*
Explication du code: 
Recherche binaire:(sur tableau trié) on divise le tableau en 2, on compare le milieu et la clé si ils sont pareil on passe au rafinage
sinon on prends la moitié qui contient la clé et on divise en 2 et ainsi de suite (renvoie 0 si pas de clé dans le tableau)
Rafinage: A partir de la clé trouvée, on déplace left en augmentant la taille entre left et right d'un facteur deux jusquà atteindre une valeur où il n'y a pas de clé ou une extremité
pendant l'exécution on "retient" la dernière valeur de left qui correspond à la clé, dès que la boucle s'arrête on obtient alors un sous-tableau qui contient le terme le plus à gauche/droite, 
dans ce nouveau tableau on recommence le raffinage, jusqu'à obtenir un sous tableau de taille 2. 
*/
size_t binarySearchLow(void *array, size_t length, void *key, int (*compare)(const void *, size_t i, void *))
{
    
    size_t left = 0;
    size_t right = length - 1;

    while(left <= right)
    {
        size_t mid = left + (right - left)/2;
        int comp = compare(array,mid,key); 
        if(comp == 0)
        {
            size_t last = mid;
            size_t ref_left = mid-1;
            size_t ref_right = mid;
            size_t max_left = 0; //limite gauche du tableau
            //refining
            while(max_left + 1 < last)
            {
                while(compare(array,ref_left,key) == 0 && ref_left >= max_left) //tant que la clé se répète on déplace left d'un facteur 2 vers la gauche
                {
                    ref_right = ref_left;
                    if(ref_left >= (last - ref_left)/2 + 1)
                        ref_left -= (last - ref_left)/2 + 1;
                    else
                        break;
                    //fprintf(stderr,"-----------------------B1//RR:%ld RL:%ld ML:%ld\n",ref_right,ref_left,max_left);
                }
                //fprintf(stderr,"-----------------------OUT1//RR:%ld RL:%ld ML:%ld\n",ref_right,ref_left,max_left);
                if(ref_left < max_left)
                        ref_left = max_left;
                last = ref_right;
                max_left = ref_left;
                ref_left = last - 1;
            }
            return last;
        }
        if(comp > 0)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    return 0;
}

#include <stdio.h>

#include "BinarySearch.h"

size_t binarySearchHigh(void *array, size_t length, void *key, int (*compare)(const void *, size_t i, void *))
{
    
    size_t left = 0;
    size_t right = length - 1;

    while(left <= right)
    {
        size_t mid = left + (right - left)/2;
        int comp = compare(array,mid,key); 
        if(comp == 0)
        {
            size_t last = mid;
            size_t ref_left = mid;
            size_t ref_right = mid+1;
            size_t max_right = length-1; //limite gauche du tableau
            //refining
            while(max_right - 1 > last)
            {
                while(compare(array,ref_right,key) == 0 && ref_right <= max_right) //tant que la clé se répète on déplace left d'un facteur 2 vers la gauche
                {
                    ref_left = ref_right;
                    
                    ref_right += (last - ref_left)/2 + 1;
                    
                    //fprintf(stderr,"-----------------------B1//RR:%ld RL:%ld ML:%ld\n",ref_right,ref_left,max_left);
                }
                //fprintf(stderr,"-----------------------OUT1//RR:%ld RL:%ld ML:%ld\n",ref_right,ref_left,max_left);
                if(ref_right > max_right)
                        ref_right = max_right;
                last = ref_left;
                max_right = ref_right;
                ref_right = last + 1;
            }
            return last;
    }

    return 0;
}
