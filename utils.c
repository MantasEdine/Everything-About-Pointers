#include "utils.h"
#include <stdio.h>
int increment(int a){
    a = a + 1;
    return a;
}
int increment_another(int* a1){
    *a1 = *a1 + 1;
    return *a1;
}

int sum_elements(int A[],int size){
    int i , sum = 0;
    for (i = 0; i < size; i++)
    {
        sum += A[i];
    }
    return sum;
    
}
void printArr(char A[]){
     
     // int i = 0;
     while ( *A !=  '\0')
     {
          printf("%c",*A);
          A++;
     }
     printf("\n");
          
}
