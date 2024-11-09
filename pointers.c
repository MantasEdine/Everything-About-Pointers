#include <stdio.h>
#include <string.h>



#include "utils.h"


int main(void) {
    // Introduction to pointers
    // Note: Pointers are variables that store the address of other variables (its type depending)
    // Pointer to an integer variable should be of type integer, etc... to optimize memory management by the computer

    // Введение в указатели
    // Примечание: Указатели - это переменные, которые хранят адреса других переменных (в зависимости от их типа)
    // Указатель на целочисленную переменную должен быть типа integer и т.д., чтобы оптимизировать управление памятью компьютера

    int x = 10;
    int* p = &x;

    // Print the address of the pointer itself
    // Вывести адрес самого указателя
    printf("Address of pointer p: %p\n", (void*)&p);

    // Print the address of x
    // Вывести адрес x
    printf("Address of x: %p\n", (void*)&x);

    // Print the value of x
    // Вывести значение x
    printf("Value of x: %d\n", x);

    // Dereference the pointer to x to get the value of x
    // Разыменовать указатель на x, чтобы получить значение x
    printf("Value of x through pointer p: %d\n", *p);

    // Using dereferencing, we can change the value of x using the pointer to it:
    // Используя разыменование, мы можем изменить значение x, используя указатель на него:
    *p = 20;
    printf("New value of x: %d\n", *p); // 20
    printf("New value of x: %d\n", x); // 20

    int b = 30;
    p = &b;
    printf("New value of *p: %d\n", *p); // 30
    printf("Value of x: %d\n", x); // 20
    printf("Value of b: %d\n", *p); // 30

    // We can conclude from this operation that by changing the value of p, it won't change the value of x
    // and we also know that by making p point to a new variable, this has no effect on the initial variable it was pointing to
    // Из этой операции мы можем заключить, что изменение значения p не изменит значение x
    // и мы также знаем, что сделав p указывающим на новую переменную, это не повлияет на начальную переменную, на которую он указывал

    int c = 50;
    *p = c;
    printf("Value of b: %d\n", b); // 50
    printf("Value of *p: %d\n", *p); // 50
    printf("Address of b: %p\n", (void*)&b); // Address of b
    printf("Address of p: %p\n", (void*)p); // Address of b

    // As we can see, assigning a new value c to the pointer only changed the value of b
    // and didn't change anything else
    // Как мы видим, присвоение нового значения c указателю изменило только значение b
    // и ничего больше не изменило

    printf("Address of pointer p: %p\n", (void*)p);
    printf("Size of integer in Bytes : %zu\n", sizeof(int)); // sizeof is a built-in function in C language
    printf("Address of pointer p: %p\n", (void*)(p + 1));
    // As we can see the pointer address is now +4 which is 4Bytes which is size of Integer
    // so we can conclude that after adding 1 to the pointer it moved by 4 bytes to the next address
    // Как мы видим, адрес указателя теперь +4, что составляет 4 байта, что является размером Integer
    // поэтому мы можем заключить, что после добавления 1 к указателю он переместился на 4 байта к следующему адресу

    // Explaining how Variables are stored in memory Using Integer type as an example:
    // Let's say we have int a = 1025 it means ===> "0"0000000 00000000 00000100 00000001
    //                                                 byte3    byte2    byte1    byte0
    // Examples of addresses values           ====>     203      202      201      200
    // The "0" is a regular 0 but that specific bit is called a sign bit which determines if the number is "POSITIVE +" OR "NEGATIVE -"
    // The next 7 bits + 3 bytes are the actual number
    // Now let's see how pointers work under the hood:
    // Let's say now we have int* p = &a;
    // print(p) // 200 (printing address of first byte) logic behind this is that the machine will look 3 bytes after the byte pointed by pointer p to get the value
    // print(*p) // 1025 (printing value of a which is pointed by p which means p is holding address of a)

    // Объяснение того, как переменные хранятся в памяти, используя тип Integer в качестве примера:
    // Допустим, у нас есть int a = 1025, это означает ===> "0"0000000 00000000 00000100 00000001
    //                                                         byte3    byte2    byte1    byte0
    // Примеры значений адресов                        ====>    203      202      201      200
    // "0" - это обычный 0, но этот конкретный бит называется знаковым битом, который определяет, является ли число "ПОЛОЖИТЕЛЬНЫМ +" ИЛИ "ОТРИЦАТЕЛЬНЫМ -"
    // Следующие 7 бит + 3 байта - это фактическое число
    // Теперь давайте посмотрим, как указатели работают под капотом:
    // Допустим, теперь у нас есть int* p = &a;
    // print(p) // 200 (вывод адреса первого байта) логика заключается в том, что машина будет смотреть 3 байта после байта, на который указывает указатель p, чтобы получить значение
    // print(*p) // 1025 (вывод значения a, на которое указывает p, что означает, что p содержит адрес a)
    
 
 // Pointer Casting
    ///////////////////////////

    int var = 1025;
    int* pOinter = &var;
    printf("%d\n", *pOinter); // 1025
    printf("%p\n", (void*)pOinter); // Address of var
    printf("%p\n", (void*)&var); // Address of var
    printf("%ld\n", sizeof(int)); // 4 Bytes

    ////////////////////////////
    // Let's use the same pointer but this time to point to a char which requires 1 byte of memory
    // In this case, since we will cast the first pointer, the pointer address won't change (starting byte), you can notice by comparing address values

    // Используем тот же указатель, но на этот раз указываем на char, который требует 1 байт памяти
    // В этом случае, так как мы приведем первый указатель, адрес указателя не изменится (начальный байт), это можно заметить, сравнивая значения адресов

    char* pChar;

    pChar = (char*) pOinter;

    printf("%p\n", (void*)pChar); // Address of var
    printf("%ld\n", sizeof(char)); // 1 Byte
    printf("%ld\n", sizeof(pChar)); // 8 Bytes (64 bits)
    printf("%d\n", *(pChar + 1)); // 4
    // The value 4 suggests that the byte at the memory location pChar + 1 contains the value 4
    // Значение 4 указывает на то, что байт по адресу pChar + 1 содержит значение 4

    ////////////////////////////
    // Example of what happening in memory under the hood
    // Пример того, что происходит в памяти под капотом

    // Memory: [0x1000] -> 0x01
    //         [0x1001] -> 0x04
    //         [0x1002] -> 0x00
    //         ...

    ////////////////////////////
    // Generic pointer type does correspond to any type (Void Pointer)
    // Универсальный тип указателя не соответствует никакому типу (Указатель типа void)

    void* pVoid;
    pVoid = &var;
    // printf("%d\n",*pVoid); we can't dereference a void pointer because it doesn't correspond to any real type, trying this will cause an error
    // printf("%d\n",*(pVoid + 1)); we can't do this using a void pointer, this will cause an error
    printf("%p\n", pVoid); // Address of var

    ////////////////////////////
    // Pointer to Pointer
    // Указатель на указатель

    // Note amount of memory reserved to store a pointer (variable storing the address of a specific variable of a specific type)
    // is equivalent to the amount of memory reserved for the var itself, so if it's an integer which means requires 4 bytes
    // Заметьте, что количество памяти, зарезервированной для хранения указателя (переменной, хранящей адрес определенной переменной определенного типа)
    // эквивалентно количеству памяти, зарезервированной для самой переменной, поэтому если это целое число, которое означает требует 4 байта
// Pointer to Pointer
    // Указатель на указатель

   int test01 = 10;
    int* pTest01 = &test01;
    int** ppTest01 = &pTest01;
    int*** pppTest01 = &ppTest01;
    printf("%d\n", test01); // 10

    ////////////////////////////
    // Dereferencing
    // Разыменование

    printf("%d\n", *pTest01); // 10
    printf("%d\n", **ppTest01); // 10
    printf("%d\n", ***pppTest01); // 10

    // Accessing First Pointer Value (address of variable pointed to)
    // Доступ к значению первого указателя (адрес переменной, на которую указывает)

    printf("%p\n", (void*)&test01); // Address of test01
    printf("%p\n", (void*)pTest01); // Address of test01
    printf("%p\n", (void*)**pppTest01); // Address of test01
    printf("%p\n", (void*)*ppTest01); // Address of test01

    // Accessing second pointer value (address of variable pointer he points to)
    // Доступ к значению второго указателя (адрес переменной, на которую указывает)

    printf("%p\n", (void*)*pppTest01); // Address of pTest01
    printf("%p\n", (void*)ppTest01); // Address of pTest01
    printf("%p\n", (void*)&pTest01); // Address of pTest01

    // Accessing third pointer value (address of second pointer variable he points to)
    // Доступ к значению третьего указателя (адрес переменной второго указателя, на которую он указывает)

    printf("%p\n", (void*)pppTest01); // Address of ppTest01

    ////////////////////////////
    // Loading Process
    // Процесс загрузки

    // Compilation and Linking:
    // Компиляция и связывание:

    // The source code is first compiled into an object file (machine code).
    // Исходный код сначала компилируется в объектный файл (машинный код).

    // The object files are then linked together to form an executable file.
    // Объектные файлы затем связываются вместе, образуя исполняемый файл.

    // Executable File:
    // Исполняемый файл:

    // The executable file contains the machine code, data, and metadata needed to run the program.
    // Исполняемый файл содержит машинный код, данные и метаданные, необходимые для запуска программы.

    // Loading into Memory:
    // Загрузка в память:

    // When you run the executable, the operating system's loader reads the executable file and loads it into memory.
    // Когда вы запускаете исполняемый файл, загрузчик операционной системы читает исполняемый файл и загружает его в память.

    // The loader allocates memory for the program's code, data, stack, and heap segments.
    // Загрузчик выделяет память для сегментов кода, данных, стека и кучи программы.

    // The loader also sets up the program's environment, including the initial values of registers and the stack.
    // Загрузчик также настраивает среду программы, включая начальные значения регистров и стека.

    // Execution:
    // Выполнение:

    // Once the program is loaded into memory, the CPU starts executing the instructions from the entry point (usually the main function).
    // После того как программа загружена в память, процессор начинает выполнять инструкции с точки входа (обычно функция main).

    ////////////////////////////
    // Memory Layout
    // Макет памяти

    // The memory allocated for a program typically includes the following segments:
    // Память, выделенная для программы, обычно включает следующие сегменты:

    // Text Segment:
    // Сегмент кода:

    // Contains the executable code (machine instructions).
    // Содержит исполняемый код (машинные инструкции).

    // Read-only and shared among processes.
    // Доступен только для чтения и разделяется между процессами.

    // Data Segment:
    // Сегмент данных:

    // Contains initialized global and static variables.
    // Содержит инициализированные глобальные и статические переменные.

    // Divided into initialized and uninitialized sections (.data and .bss).
    // Разделен на инициализированные и неинициализированные секции (.data и .bss).

    // Heap Segment:
    // Куча:

    // Dynamically allocated memory (e.g., using malloc, calloc, realloc).
    // Динамически выделяемая память (например, с использованием malloc, calloc, realloc).

    // Grows upwards in memory.
    // Растет вверх в памяти.

    // Stack Segment:
    // Стек:

    // Contains local variables, function parameters, return addresses, and control information.
    // Содержит локальные переменные, параметры функций, адреса возврата и управляющую информацию.

    // Grows downwards in memory.
    // Растет вниз в памяти.
    //*********** */
    // Examples 
    int z = 1;
    // Pass By Value
    increment(z);
    printf("The Value of Z after passing it to (increment) : %d\n", z); // 1
    // Pass By Reference
    increment_another(&z);
    printf("The Value of Z after passing it to (increment_another) : %d\n", z); // 2

    // Pointers And Arrays 

    // Remark if make a pointer to an Array it will Automatically point to the first element of the Array !
    int Arr[5];
    Arr[0] = 69;
    Arr[1] = 96;
    Arr[2] = 1;
    Arr[3] = 2;
    Arr[4] = 3;
    // Arr[5] = 123; // This is out of bounds and should be removed

    int* pArr = Arr;
    printf("Arr[0] = %d\n", *pArr); // 69
    pArr = pArr + 1; 
    printf("Arr[1] = %d\n", *pArr); // 96
    pArr = pArr - 1; 

    // First Element of an array is called Base Address and using Array itself gives us Base Address
    // IMPORTANT REMARK !!!!
    for (size_t i = 0; i < 5; i++) {
        printf("A[%d] = %d\n", i, Arr[i]);
        printf("A[%d] = %d\n", i, *(pArr + i));
    }

    for (size_t i = 0; i < 5; i++) {
        printf("A[%d] = %d\n", i, Arr[i]);
        printf("A[%d] = %d\n", i, *(Arr + i)); // Can Simply use the Array directly cause it's just a pointer variable pointing to the BASE ELEMENT
    }

    // Difference is that we can do pArr++ BUT we can't do Arr++

    // Passing Arrays as Arguments Example 
    int A[] = {1, 2, 3, 4, 5};
    int sizeA = sizeof(A) / sizeof(A[0]);
    int res = sum_elements(A, sizeA);
    printf("Sum Of A(Array) elements  = %d\n", res);

    // Char Arrays And Pointers (Strings) :

    // String Literal 
    char name[] = "John";
    int len = strlen(name);
    printf("%s , length = %d\n", name, len);

    // Other way of writing it 
    // Remark in the way I'll show you, You Should know putting a Null-terminator Char at the end is done manually (Explicitly)

    char Name[] = {'j', 'o', 'h', 'n', '\0'};
    printf("%s\n", Name);

    // Some more examples to train :
    char str[] = "Hello";

    printArr(str);

    //******************************/

    char Arr01[] = "Hello, World"; // The String will be stored in its special place in memory (memory allocated to it)
    // char *Arr02 = "Hello World"; // The String will be stored as a compile time constant which means can't be modified
    // Arr02[0] = "A";     // Error (Segmentation fault (core dumped))
    // The string "Hello, World!" is stored in a read-only section of memory, and str points to the first character of this string.
    // Remark if we want to force the behavior of only Reading when passing an array as an argument of a function (Pointer)
    // we can make it constant example : char Function(const char* Argument) this will force behavior of only reading

    // Pointers And Multidimensional Arrays

 
     
     // We're technically Creating 2 1-D Arrays of 3 elements each !! ! ! ! 
     int  B[2][3] = {{1,2,3},{4,5,6}};
     printf("%d\n",B); // -681728480
     printf("%d\n",&B[0]); // -681728480
     printf("%d\n",&B[0][0]); // -681728480
     printf("%d\n",(B+1)); // -681728468
     printf("%d\n",*(B+1)); // 2
     printf("%d\n",*(*B+1)); // 
     printf("%d\n",(B[0]+1)); // 681728468
     printf("%d\n",*B); // 
     printf("%d\n",&B[0]); 
     printf("%d\n",B[0][1]); 
     printf("%d\n",B[1][0]); 
     printf("%d\n",B[1]); 
     printf("%d\n",*(B+1)+2); 
     printf("%d\n",*B+1); 
     printf("%d\n",&B[0][1]); 
     printf("%d\n",&B[1][0]); 
     

    // we can write it what return B in form :
    int (*pMulti)[3] = B; 
    // B will return a pointer to 1-Dimentional Array of 3 elements
    // int *p = B is wrong will return an Error
     printf("%d\n",B); // Pointer to an 1-D Array of 3 Elements
     printf("%d\n",*B); // Pointer to an integer of value B[0][0]

    //  int arr[14][5][2][7]
    //  printf("%d\n",&arr[9][4][0][1]);
    //  printf("%d\n",&arr[5][1]);
    //  printf("%d\n",&arr[9][4][0][1] - &arr[5][1]);




 
  
 // Understanding How Memory Works (in the Context of Application Memory)
// When we speak about memory, we're primarily referring to RAM (Random Access Memory).

// Memory is divided into blocks called "pages."
// Each page is a fixed-size block of memory managed by the operating system.
// Pages are mapped to physical memory blocks called "frames."

// To explain this better, let's discuss how the operating system partitions memory for a specific application.
// Memory is divided into four main parts: HEAP, STACK, Static/Global, and Code/Text.

// Code/Text: This section stores the instructions that will be executed by the process.

// Static/Global: This section stores static and global variables, which remain in memory throughout the entire program's lifetime, whether they are used or not.

// STACK: One of the most important parts of application memory, used to store local variables, function return addresses, function parameters, and arguments.
// The lifetime of a local variable ends when the function finishes execution, and the memory allocated for it by the OS is freed.
// The stack is divided into "stack frames" for each function call. A stack frame is a chunk of memory allocated by the OS for the function to execute and is freed once the function execution ends.

// HEAP: This section is used for dynamic memory allocation, where memory is allocated using functions such as `calloc`, `malloc`, and `realloc`.

// Понимание работы памяти (в контексте памяти приложений)
// Когда мы говорим о памяти, мы преимущественно имеем в виду ОЗУ (оперативную память).

// Память делится на блоки, называемые "страницами."
// Каждая страница — это фиксированный размер блока памяти, управляемый операционной системой.
// Страницы отображаются на физические блоки памяти, называемые "кадрами."

// Чтобы объяснить это лучше, давайте обсудим, как операционная система разделяет память для конкретного приложения.
// Память делится на четыре основные части: HEAP, STACK, Static/Global и Code/Text.

// Code/Text: В этой секции хранятся инструкции, которые будут выполнены процессом.

// Static/Global: В этой секции хранятся статические и глобальные переменные, которые остаются в памяти на протяжении всего времени работы программы, независимо от того, используются они или нет.

// STACK: Одна из самых важных частей памяти приложения, используется для хранения локальных переменных, адресов возврата функций, параметров и аргументов функций.
// Время жизни локальной переменной заканчивается, когда функция завершает выполнение, и память, выделенная для неё ОС, освобождается.
// Стек делится на "кадры стека" для каждого вызова функции. Кадр стека — это часть памяти, выделенная ОС для выполнения функции и освобождаемая после завершения выполнения функции.

// HEAP: В этой секции выделяется динамическая память, где память выделяется с использованием функций, таких как `calloc`, `malloc` и `realloc`.





// Virtual memory is an abstraction provided by the operating system to give each process the illusion that it has its own private, contiguous address space.
//  When a process is running, the operating system maps its virtual memory addresses to physical RAM addresses.
// The virtual memory space of a process is divided into the sections mentioned above.
// The operating system uses techniques like paging to manage the mapping between virtual and physical memory.
// If the physical RAM is full, the operating system can move some pages of virtual memory to disk (swap space) to free up RAM.

// Important Note: The memory allocated for the stack does not grow at runtime. If we exceed it, we will encounter a stack overflow.
// For example, this can happen during a bad recursion. One of the limitations of the stack is that its memory allocation is fixed.
// If we exceed this limit at runtime, due to bad recursion or a function return that cannot fit within the allocated stack space,
// the program will crash. This condition is known as a stack overflow.

// Heap memory, on the other hand, is dynamic and can grow at runtime. We can allocate more memory as needed, which is why it is called dynamic.
// However, if we do not manage heap memory properly, we can encounter memory leaks, which can eventually crash the program and potentially
// stop the computer. Unlike the stack, we do not need to know the exact size of a large variable at runtime.
// The heap can grow as needed, and it grows upward, while the stack grows downward.

// Важное замечание: Память, выделенная для стека, не увеличивается во время выполнения. Если мы превысим этот лимит, произойдет переполнение стека.
// Например, это может случиться при плохой рекурсии. Одно из ограничений стека заключается в том, что его выделение памяти фиксировано.
// Если мы превысим этот лимит во время выполнения, из-за плохой рекурсии или возврата функции, который не помещается в выделенное пространство стека,
// программа завершится аварийно. Это состояние называется переполнением стека.

// Память кучи, с другой стороны, динамическая и может увеличиваться во время выполнения. Мы можем выделять больше памяти по мере необходимости,
// поэтому она называется динамической. Однако, если мы не будем правильно управлять памятью кучи, мы можем столкнуться с утечками памяти,
// которые могут привести к сбою программы и потенциально остановить компьютер. В отличие от стека, нам не нужно знать точный размер большой переменной во время выполнения.
// Куча может расти по мере необходимости и растет вверх, в то время как стек растет вниз.

          
    return 0;
}