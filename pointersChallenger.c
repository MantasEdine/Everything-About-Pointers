#include <stdio.h>
#include <math.h>


void swap(int a[],int b[]){
    
      int i,j,holder = 0;
      for (i = 0; i < 20; i++)
      { 
        holder = a[i];
        for ( j = 0; j < 20; j++)
        { 
            if(i == j){
              
               a[i] = b[j];
               b[j] = holder;

            }else {
                continue;
            }

        }
        
        
      }
      
       
}
int main(void){
 
  int a[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
  int b[20] = {20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};
  swap(a,b);
  for(int i = 0; i < 20; i++){
    printf("%d\n",a[i]);
  }

}