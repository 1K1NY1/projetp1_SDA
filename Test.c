#include <stdlib.h>
#include <stdio.h>
#include "BinarySearch.h"

int compare(const void * tab, size_t i, void * key);
int main()
{
    fprintf(stderr,"Initialisation des tableaux\n");
    int key = 1;
    int t1[10] = {0,0,0,0,1,1,1,1,1,1};
    int t2[10] = {0,0,0,0,0,0,0,0,0,0};
    int t3[10] = {1,1,1,1,1,1,1,1,1,1};
    int t4[10] = {0,1,1,1,1,1,1,1,1,1};
    int t5[10] = {0,0,0,0,0,1,1,1,1,1};
    int t6[10] = {0,0,0,0,0,0,1,1,1,1};
    int tspecial[11] = {0,1,1,1,1,1,1,1,1,1,1};
    int tspecial2[11] = {1,1,1,1,1,1,1,1,1,1,1};
    int tspecial3[10] = {2,2,2,2,2,2,2,2,2,2};
    int s1[1] = {1};
    int s2[1] = {0};
    int s3[2] = {0,1};
    int s4[2] = {1,1};
    int s5[1] = {2};
    int s6[2] = {2,2};
    fprintf(stderr,"Verif start:\n");
    fprintf(stderr,"t1: %ld \n", binarySearchLow(t1,10,&key,compare));
    fprintf(stderr,"t2: %ld \n", binarySearchLow(t2,10,&key,compare));
    fprintf(stderr,"t3: %ld \n", binarySearchLow(t3,10,&key,compare));
    fprintf(stderr,"t4: %ld \n", binarySearchLow(t4,10,&key,compare));
    fprintf(stderr,"t5: %ld \n", binarySearchLow(t5,10,&key,compare));
    fprintf(stderr,"t6: %ld \n", binarySearchLow(t6,10,&key,compare));
    fprintf(stderr,"tspecial: %ld \n", binarySearchLow(tspecial,11,&key,compare));
    fprintf(stderr,"tspecial2: %ld \n", binarySearchLow(tspecial2,11,&key,compare));
    fprintf(stderr,"tspecial3: %ld \n", binarySearchLow(tspecial3,10,&key,compare));

    //Petit tableaux
    fprintf(stderr,"s1: %ld \n", binarySearchLow(s1,1,&key,compare));
    fprintf(stderr,"s2: %ld \n", binarySearchLow(s2,1,&key,compare));
    fprintf(stderr,"s3: %ld \n", binarySearchLow(s3,2,&key,compare));
    fprintf(stderr,"s4: %ld \n", binarySearchLow(s4,2,&key,compare));
    fprintf(stderr,"s5: %ld \n", binarySearchLow(s5,1,&key,compare));
    fprintf(stderr,"s6: %ld \n", binarySearchLow(s6,2,&key,compare));
    fprintf(stderr,"Test itératif:\n");
    for(int i = 0; i < 10; i++)
    {
        t2[9-i] = 1;
        fprintf(stderr,"iter%d: %ld \n",i, binarySearchLow(t2,10,&key,compare));
    }
    fprintf(stderr,"iter%d: %ld \n",9, binarySearchLow(t2,10,&key,compare));
    fprintf(stderr,"iter TAB3: %ld \n", binarySearchLow(t3,10,&key,compare));
    fprintf(stderr,"iter TAB3: %ld \n", binarySearchLow(t3,10,&key,compare));
    fprintf(stderr,"iter TAB3: %ld \n", binarySearchLow(t3,10,&key,compare));
    for(int i = 0; i < 10;i++)
        fprintf(stderr,"%d,",t3[i]);
    fprintf(stderr,"\n Test de BinHigh:\n");
    fprintf(stderr,"Full tab: %ld \n", binarySearchHigh(t2,10,&key,compare));
    for(int i = 0; i < 10; i++)
    {
        t2[9-i] = 2;
        fprintf(stderr,"iter%d: %ld \n",i, binarySearchHigh(t2,10,&key,compare));
       
        fprintf(stderr,"\n Tableau en cours: ");
         for(int x = 0; x < 10;x++)
        fprintf(stderr,"%d,",t2[x]);
        fprintf(stderr,"\n");
    }
    fprintf(stderr,"\n");
    fprintf(stderr,"Test finish:\n");
    return 0;
}
int compare(const void * tab, size_t i, void * key)
{
    int* myTab = (int*)tab;
    int myKey = *(int*)key;
    if(myKey == myTab[i])
        return 0;
    if(myTab[i] < myKey)
        return -1;
    return 1;
}
