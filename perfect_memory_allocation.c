#include <stdlib.h>
#include <stdio.h>

#define MIN_SIZE_FOR_REALLOC 21
int main(void){

 
       
     int size,value = 0;
     printf("Enter Number Of Elements : \n");
     scanf("%d",&size);
     int* p = (int*)calloc(size,sizeof(int));
     if(p == NULL){
        perror("calloc");
        return 1;
     }
     for (int i = 0; i < size; i++)
     {
        p[i] = ++value;
     }
     for (int i = 0; i < size; i++)
     {
        printf("key value : p[%d]= %d\n",i,*(p+i));
     }
     
     if(size < MIN_SIZE_FOR_REALLOC){
        int newSize, newValue = 0;
        printf("Enter new value over 21 ! : \n");
        scanf("%d",&newSize);
        int* newP = (int*)realloc(p,newSize);
        if(newP == NULL){
            perror("reaclloc");
            return 1;
            free(p);
        }
        for (int i = 0; i < newSize; i++){
            newP[i] = ++newValue;
        }
        for (int i = 0; i < newSize; i++)
     {
        printf("newKey and new value : p[%d]= %d\n",i,*(newP+i));
     }

       free(newP);
     }

     
      
      
       

        
          
    return 0;
}
