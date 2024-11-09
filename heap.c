#include <stdio.h>
#include <stdlib.h>

int main(void){
    int n; // Memory allocated on the Stack for the frame of the main function (local to the main function)
           // Память выделена в стеке для кадра функции main (локальная переменная)
    
    int *p;
    p = (int*)malloc(sizeof(int)); // Memory allocated on the Heap (allocating 4 bytes for an int)
                                   // Память выделена в куче (выделяем 4 байта для int)
    
    *p = 10; // Assigning a value to the memory location pointed by p
             // Присваиваем значение по адресу, на который указывает p
    
    // malloc returns a pointer to the starting address of the allocated memory block
    // malloc возвращает указатель на начальный адрес выделенного блока памяти
    
    // malloc returns a void pointer, so we cast it to an int pointer
    // malloc возвращает указатель типа void, поэтому мы приводим его к указателю на int
    
    printf("%d\n", p); // Printing the address of the allocated memory
                       // Выводим адрес выделенной памяти
    
    free(p); // We should free the memory before assigning a new memory location to the pointer
             // Мы должны освободить память перед присвоением нового адреса указателю
    
    // Otherwise, the previously allocated memory will remain allocated and unused,
    // which can lead to memory leaks or issues with the OS needing that memory later
    // В противном случае ранее выделенная память останется выделенной и неиспользуемой,
    // что может привести к утечкам памяти или проблемам, если ОС потребует эту память позже
    
    p = (int*)malloc(sizeof(int));
    
    printf("%d\n", p);
    
    *p = 20;
    
    printf("%d\n", *p);
    
    free(p); // Remark: If malloc cannot find free memory on the heap, it returns NULL (good to know for error handling)
             // Примечание: если malloc не может найти свободную память в куче, он возвращает NULL (полезно знать для обработки ошибок)
    
    p = (int*)malloc(20 * sizeof(int)); // Allocate memory for an array of size 20
                                        // Выделяем память для массива размером 20
    
    // for(int i=0;i<20;i++){
    //     free(p+1);
    //     } No need to use a loop to free it, just do a 
    // for(int i=0;i<20;i++){
    //     free(p+1);
    //     } Не нужно использовать цикл для освобождения памяти, просто выполните
    
    free(p); // Free the entire block of memory
             // Освобождаем весь блок памяти

    return 0;
}