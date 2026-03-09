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
            //trouve celui le plus à gauche
            size_t p = 1;
            for(; compare(array,(mid-p),key) == 0 && mid - p > 0; p++)
            return mid - (p+1); //une incrémentation de p de trop
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
