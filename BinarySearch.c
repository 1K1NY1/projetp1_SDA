#include <stdio.h>

#include "BinarySearch.h"

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
            //trouve celui le plus à gauche
            size_t p = 1;
            for(; compare(array,(mid+p),key) == 0 && mid + p < length - 1; p++)
            return mid + (p-1); //une incrémentation de p de trop
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
