# Everything About Pointers

A working reference for pointers in C and C++. Every section has code you can compile, not a description of code you could write.

Assumes you know basic C syntax (variables, functions, `printf`). Examples target C11/C++17. Sizes assume a typical 64-bit Linux target (`int` = 4 bytes, pointer = 8 bytes) — none of the *concepts* depend on that, but the printed numbers do.

## Compiling the examples

```bash
# C
gcc -std=c11 -Wall -Wextra -g -fsanitize=address,undefined file.c -o file

# C++
g++ -std=c++17 -Wall -Wextra -g -fsanitize=address,undefined file.cpp -o file
```

Use the sanitizers while learning. Most pointer bugs are silent without them: the program appears to work, then breaks six months later on a different machine.

## Table of Contents

1. [What a pointer actually is](#1-what-a-pointer-actually-is)
2. [Declaring, initializing, dereferencing](#2-declaring-initializing-dereferencing)
3. [Pointer types, arithmetic, and `void *`](#3-pointer-types-arithmetic-and-void-)
4. [Pointers to pointers](#4-pointers-to-pointers)
5. [Pointers as function arguments](#5-pointers-as-function-arguments)
6. [Pointers and arrays](#6-pointers-and-arrays)
7. [Arrays as function arguments](#7-arrays-as-function-arguments)
8. [Character arrays and strings](#8-character-arrays-and-strings)
9. [2-D arrays](#9-2-d-arrays)
10. [Multidimensional and jagged arrays](#10-multidimensional-and-jagged-arrays)
11. [Stack vs heap](#11-stack-vs-heap)
12. [`malloc`, `calloc`, `realloc`, `free`](#12-malloc-calloc-realloc-free)
13. [Returning pointers from functions](#13-returning-pointers-from-functions)
14. [Function pointers](#14-function-pointers)
15. [Callbacks](#15-callbacks)
16. [Memory leaks and how to find them](#16-memory-leaks-and-how-to-find-them)
17. [Undefined behaviour checklist](#17-undefined-behaviour-checklist)

---

## 1. What a pointer actually is

Process memory is one large array of bytes. Every byte has an index — its **address**. A pointer is a variable whose value *is* an address.

```
        memory
        ┌──────────┬──────────┬──────────┬──────────┐
address │ 0x7ffc10 │ 0x7ffc14 │ 0x7ffc18 │ 0x7ffc20 │
        ├──────────┼──────────┼──────────┼──────────┤
value   │    42    │          │          │ 0x7ffc10 │
        └──────────┴──────────┴──────────┴──────────┘
             x                                p
```

`p` holds `0x7ffc10`. Dereferencing `p` means "go to the address stored in `p` and read/write there."

```c
#include <stdio.h>

int main(void) {
    int x = 42;
    int *p = &x;        // & = address-of

    printf("%d\n",  x);          // 42
    printf("%p\n",  (void *)p);  // 0x7ffc10... (varies per run)
    printf("%d\n",  *p);         // 42   -- * = dereference
    printf("%zu\n", sizeof p);   // 8    -- size of the pointer, not of x

    *p = 99;
    printf("%d\n", x);           // 99   -- we wrote through the pointer
}
```

Two things that trip people up early:

- `%p` expects a `void *`. Passing an `int *` without the cast is technically undefined behaviour, even though it usually prints fine.
- `sizeof p` is the size of the *pointer* (8 on x86-64), not the size of what it points to. That's `sizeof *p`.

Pointers matter because they buy you three things you can't get otherwise: letting a function modify its caller's data, referring to memory whose size isn't known until runtime, and passing large objects around without copying them.

---

## 2. Declaring, initializing, dereferencing

### The declaration gotcha

```c
int *p, q;   // p is int*, q is int. The * binds to the declarator, not the type.
int *p, *q;  // both pointers
```

Declaring one pointer per line avoids the whole argument.

### Null and uninitialized pointers

```c
int *good = NULL;   // explicitly points nowhere; testable
int *bad;           // holds garbage; dereferencing is UB
```

`NULL` is guaranteed to compare unequal to any valid object address. Dereferencing it is undefined behaviour — on hosted systems you'll usually get a segfault, which is the *lucky* outcome. In C++, prefer `nullptr`: it's typed, so it can't accidentally pick the `int` overload the way `NULL` can.

Always check pointers that can legitimately be null:

```c
int *p = malloc(sizeof *p);
if (p == NULL) { /* handle allocation failure */ }
```

### `const` and pointers

Read declarations **right to left**:

```c
const int *p;         // p: pointer to const int      -- can't do *p = 5, can do p++
int *const p = &x;    // p: const pointer to int      -- can do *p = 5, can't do p++
const int *const p;   // const pointer to const int   -- neither
```

`const int *` and `int const *` are the same thing. The second form makes right-to-left reading consistent, which is why some codebases mandate it.

Marking parameters `const` is not decoration — it documents that the function won't write through the pointer, and lets the compiler catch it when you do.

---

## 3. Pointer types, arithmetic, and `void *`

### Why pointers are typed

`int *` and `char *` both store a plain address. The type tells the compiler two things: how many bytes to read when you dereference, and how far to jump when you do arithmetic.

```c
int   a[5] = {10, 20, 30, 40, 50};
int  *p    = a;

printf("%p\n", (void *)p);      // base
printf("%p\n", (void *)(p+1));  // base + 4  (sizeof(int))

char *c = (char *)a;
printf("%p\n", (void *)(c+1));  // base + 1
```

**`p + n` advances by `n * sizeof(*p)` bytes.** All pointer arithmetic follows from this one rule.

### Difference and comparison

```c
int *start = &a[0], *end = &a[5];
ptrdiff_t n = end - start;      // 5, in elements -- not bytes
```

Subtraction yields `ptrdiff_t` (from `<stddef.h>`) and counts *elements*. Comparison (`<`, `>`, `==`) is defined between pointers into the same array.

> **Rule:** pointer arithmetic is only defined inside an array, plus one element past the end. You may *compute* `&a[5]` for a 5-element array and compare against it — that's how every C loop works — but dereferencing it is UB. `a - 1` is UB even to compute.

### `void *`

A `void *` is a typeless address. It's how C does generic code: `malloc` returns one, `qsort` takes them.

```c
void *v = &a;
// *v;        // error: can't dereference
// v + 1;     // not valid ISO C (GCC extension treats sizeof(void) as 1)
int *back = v;  // converting back to the right type is fine and implicit in C
```

Any object pointer converts to `void *` and back without loss. Converting to the *wrong* type and dereferencing violates strict aliasing and can be miscompiled at `-O2` — if you need to reinterpret bytes, use `memcpy` into a correctly-typed object, which optimizers reliably turn into a plain load.

In C, don't cast `malloc`'s return value — it's implicit, and the cast can hide a missing `<stdlib.h>`. In C++ the cast *is* required, which is one signal that you should be using `new` or a container instead.

---

## 4. Pointers to pointers

A pointer is a variable, so it has an address, so you can point at it.

```c
int    x  = 5;
int   *p  = &x;
int  **pp = &p;

**pp = 7;         // x == 7
printf("%d\n", *pp == p);   // 1
```

```
 pp ──→ p ──→ x
 (int**)  (int*)  (int)
```

This isn't a party trick — you need it whenever a function must change *which object a caller's pointer points to*, not just the pointed-to value:

```c
void alloc_buffer(int **out, size_t n) {
    *out = malloc(n * sizeof **out);
}

int *buf = NULL;
alloc_buffer(&buf, 100);   // buf now points at the new block
```

Without the double pointer, `alloc_buffer` would receive a copy of `buf` and the caller would never see the assignment. `main`'s `char *argv[]` — an array of pointers, decaying to `char **` — is the other example you meet constantly.

---

## 5. Pointers as function arguments

C is strictly **pass by value**. A function always receives copies. Passing a pointer means passing a copy of an address — and a copy of an address still points at the original object. That's how you get call-by-reference semantics.

```c
void swap_broken(int a, int b)   { int t = a;  a  = b;  b  = t;  }  // no effect
void swap(int *a, int *b)        { int t = *a; *a = *b; *b = t;  }

int x = 1, y = 2;
swap(&x, &y);   // x == 2, y == 1
```

The other reason to pass pointers is cost. A `struct` with 40 fields is copied byte-for-byte when passed by value; a pointer to it is 8 bytes. Pass `const T *` when the function only reads.

```c
double area(const struct Rect *r) { return r->w * r->h; }
```

`r->w` is shorthand for `(*r).w`. Use it; the parenthesized form is noise.

C++ adds references, which are pointers with sugar and no null state:

```cpp
void swap(int &a, int &b) { int t = a; a = b; b = t; }
swap(x, y);   // no & at the call site
```

Rule of thumb in C++: reference when the argument is mandatory, pointer when "absent" is a meaningful value.

---

## 6. Pointers and arrays

Arrays and pointers are related but **not the same thing**. The confusion comes from one rule:

> In most expressions, an array *decays* to a pointer to its first element.

```c
int a[5] = {10, 20, 30, 40, 50};

int *p = a;          // same as &a[0]
printf("%d\n", *p);       // 10
printf("%d\n", *(a + 2)); // 30
printf("%d\n", a[2]);     // 30 -- a[i] is *defined* as *(a + i)
printf("%d\n", 2[a]);     // 30 -- legal, since *(a+2) == *(2+a). Never write this.
```

Where they differ:

```c
sizeof a;        // 20 -- the whole array
sizeof p;        // 8  -- just the pointer
&a;              // type int(*)[5]  -- pointer to the whole array
&a[0];           // type int*
a = p;           // error: an array is not assignable
```

`&a + 1` jumps 20 bytes; `a + 1` jumps 4. Same numeric address, different types, different arithmetic.

The three exceptions to decay: `sizeof`, unary `&`, and a string literal initializing a `char` array.

Idiomatic traversal:

```c
for (int *it = a; it != a + 5; ++it)
    printf("%d ", *it);
```

---

## 7. Arrays as function arguments

An array parameter is **always** rewritten as a pointer:

```c
void f(int a[10]);   // these three
void f(int a[]);     // declare
void f(int *a);      // the same function
```

The `10` is documentation the compiler ignores. Consequently:

```c
void print(int a[]) {
    printf("%zu\n", sizeof a);   // 8 -- the pointer size, NOT 40
}
```

Length information is lost at the call boundary, so you must pass it:

```c
void print(const int *a, size_t n) {
    for (size_t i = 0; i < n; ++i) printf("%d ", a[i]);
}

int a[5] = {1,2,3,4,5};
print(a, sizeof a / sizeof a[0]);   // compute the count at the definition site
```

That `sizeof a / sizeof a[0]` idiom only works where `a` is still a real array. Once it's decayed, the information is gone.

C++ can preserve the length via templates or `std::span`:

```cpp
template <size_t N> void print(const int (&a)[N]);  // N deduced
void print(std::span<const int> a);                 // C++20
```

---

## 8. Character arrays and strings

A C string is a `char` array terminated by `'\0'`. There is no length field; every function walks to the terminator.

```c
char  s[] = "hello";   // 6 bytes on the stack: 'h','e','l','l','o','\0'. Writable.
char *t   = "hello";   // t points at a string literal. Writing through it is UB.
```

This distinction causes real crashes:

```c
s[0] = 'H';   // fine
t[0] = 'H';   // UB -- literals usually live in a read-only page; segfault
```

Always write `const char *t = "hello";` so the compiler stops you. (In C++ this isn't optional — string literals are `const char[]`, and `char *t = "hello"` has been ill-formed since C++11.)

Common operations, and the traps:

```c
strlen(s);            // walks to '\0'; O(n), so don't call it in a loop condition
strcpy(dst, src);     // no bounds check -- classic buffer overflow
snprintf(dst, sizeof dst, "%s", src);   // bounded and always NUL-terminates
```

`strncpy` is not a safe `strcpy`. It pads with zeros when the source is short and does **not** terminate when the source is too long. Use `snprintf`.

Traversal via pointer:

```c
size_t my_strlen(const char *s) {
    const char *p = s;
    while (*p) ++p;
    return (size_t)(p - s);
}
```

In C++, use `std::string` for owning text and `std::string_view` for non-owning reads. Reach for raw `char *` only at C API boundaries.

---

## 9. 2-D arrays

```c
int a[3][4];
```

Read this as "array of 3 elements, each of which is an array of 4 `int`s." It is **one contiguous block** of 12 `int`s, laid out row by row (row-major):

```
row 0: a[0][0] a[0][1] a[0][2] a[0][3]
row 1: a[1][0] a[1][1] a[1][2] a[1][3]
row 2: a[2][0] a[2][1] a[2][2] a[2][3]
```

Decay applies one level: `a` becomes a pointer to its first element, and its first element is `int[4]`. So `a` has type `int (*)[4]`.

```c
sizeof a;       // 48 -- whole thing
sizeof a[0];    // 16 -- one row
sizeof a[0][0]; // 4

a[i][j] == *(*(a + i) + j);
```

Step by step: `a + i` skips `i` whole rows (16 bytes each). `*(a + i)` is row `i`, an `int[4]`, which decays to `int *`. Adding `j` steps within the row.

Passing to a function — the column count must be in the type, because that's what sets the stride:

```c
void print(int a[][4], int rows);     // OK
void print(int (*a)[4], int rows);    // identical
// void print(int **a, int rows);     // WRONG -- different type, different layout
```

With C99 variable-length array parameters you can make both dimensions dynamic:

```c
void print(int rows, int cols, int a[rows][cols]) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            printf("%d ", a[i][j]);
}
```

Because the memory is contiguous, iterating in row-major order (`j` innermost) is dramatically faster than the reverse on large matrices — you're walking the cache lines forward instead of thrashing them.

---

## 10. Multidimensional and jagged arrays

`int **` is not a 2-D array. It's a pointer to a pointer, which implies an **array of row pointers** — two indirections and non-contiguous rows.

```c
// Contiguous, one allocation, rows of equal length
int (*grid)[4] = malloc(3 * sizeof *grid);
grid[1][2] = 7;
free(grid);

// Jagged: array of pointers, N+1 allocations, rows can differ in length
int **rows = malloc(3 * sizeof *rows);
for (int i = 0; i < 3; ++i)
    rows[i] = malloc((i + 1) * sizeof **rows);   // row i has i+1 elements
rows[2][2] = 7;
for (int i = 0; i < 3; ++i) free(rows[i]);       // free inner first
free(rows);
```

Prefer contiguous for numeric work: one allocation, one `free`, and it doesn't scatter your rows across the heap. Jagged is for genuinely ragged data — `argv`, arrays of strings, adjacency lists.

The flattened single-array version is often the cleanest of all:

```c
int *m = malloc((size_t)rows * cols * sizeof *m);
#define AT(r, c) m[(size_t)(r) * cols + (c)]
```

For 3-D and beyond the same rule extends: `int a[2][3][4]` decays to `int (*)[3][4]`.

---

## 11. Stack vs heap

| | Stack | Heap |
|---|---|---|
| Lifetime | until the function returns | until you `free`/`delete` |
| Managed by | compiler | you |
| Size | small, fixed (~1–8 MB typical) | large, limited by RAM |
| Speed | pointer bump; very fast | bookkeeping; slower |
| Failure mode | stack overflow | `NULL` return, leaks, fragmentation |

```c
void f(void) {
    int a[100];                        // stack: gone when f returns
    int *b = malloc(100 * sizeof *b);  // heap: survives until freed
    free(b);
}
```

Use the heap when the size isn't known at compile time, when the object must outlive the function that created it, or when it's too big for the stack (a `double[1000][1000]` is 8 MB — instant overflow).

The two failure modes are mirror images. Freeing too late is a **leak**. Using after free — or returning a pointer to a stack local — is a **dangling pointer**, which is far worse: it may appear to work for years.

---

## 12. `malloc`, `calloc`, `realloc`, `free`

```c
#include <stdlib.h>

void  *malloc(size_t size);                 // uninitialized bytes
void  *calloc(size_t n, size_t size);       // n*size bytes, zeroed, overflow-checked
void  *realloc(void *p, size_t new_size);   // resize, may move the block
void   free(void *p);                       // release
```

### The allocation idiom

```c
int *p = malloc(n * sizeof *p);
if (!p) { /* handle failure */ }
```

`sizeof *p` rather than `sizeof(int)` — if the type of `p` changes later, this line stays correct. This is worth making a habit.

`calloc(n, sizeof *p)` additionally checks `n * sizeof *p` for overflow, which raw multiplication in `malloc` does not. For attacker-influenced sizes, that check matters.

### `realloc` correctly

```c
int *tmp = realloc(p, new_n * sizeof *p);
if (!tmp) { free(p); return NULL; }   // p is still valid; don't lose it
p = tmp;
```

Writing `p = realloc(p, ...)` leaks the original block if the call fails. `realloc` may move the data, so **every other pointer into the old block is dangling afterwards** — including indices you cached as pointers.

Edge cases: `realloc(NULL, n)` is `malloc(n)`. `free(NULL)` is a no-op, so you never need to guard it.

### Rules

- Every `malloc`/`calloc`/`realloc` needs exactly one `free`.
- Double free is UB. So is freeing a pointer you didn't get from the allocator, or a pointer into the middle of a block.
- Setting `p = NULL` after `free(p)` turns some use-after-free bugs into an immediate null-deref. It doesn't help with the *other* copies of that pointer.

### C++

Use `new`/`delete` over `malloc`/`free` (they run constructors), and prefer to use neither:

```cpp
auto p = std::make_unique<int[]>(n);   // freed automatically
std::vector<int> v(n);                 // usually the right answer
```

`std::vector` is a growable heap array with correct `realloc` semantics baked in. Manual allocation in modern C++ is a code smell outside of low-level containers and allocators.

---

## 13. Returning pointers from functions

The one rule: **never return a pointer to a local variable.**

```c
int *broken(void) {
    int x = 42;
    return &x;      // x dies at return; the caller gets a dangling pointer
}
```

`-Wall` catches the obvious form of this. It does not catch it once the address travels through a struct or another function.

Three valid patterns:

```c
// 1. Return heap memory -- document who frees it
int *make_array(size_t n) {
    return malloc(n * sizeof(int));   // caller must free
}

// 2. Caller supplies the buffer -- no ownership question at all
void fill(int *out, size_t n) {
    for (size_t i = 0; i < n; ++i) out[i] = (int)i;
}

// 3. Return a pointer into something that already outlives the call
int *find(int *a, size_t n, int key) {
    for (size_t i = 0; i < n; ++i)
        if (a[i] == key) return &a[i];
    return NULL;
}
```

Pattern 2 is the most robust and is what most C standard library functions do. Pattern 1 requires the ownership contract to be in the header comment; if it isn't written down, it will be gotten wrong.

`static` locals also survive the return, but they're shared across all calls and not thread-safe — this is precisely why `strtok` and `localtime` are the way they are, and why their `_r` variants exist.

In C++, return by value. Move semantics and RVO make it free, and the ownership question disappears.

---

## 14. Function pointers

Functions live in memory too, so they have addresses.

```c
int add(int a, int b) { return a + b; }

int (*fp)(int, int) = add;   // or &add -- identical
printf("%d\n", fp(2, 3));    // 5
printf("%d\n", (*fp)(2, 3)); // 5 -- also legal; the sugar above is preferred
```

Read the declaration inside-out: `fp` is a pointer, to a function, taking `(int, int)`, returning `int`.

The parentheses are load-bearing:

```c
int (*fp)(int);   // pointer to function returning int
int  *f(int);     // function returning int*
```

`typedef` makes this survivable:

```c
typedef int (*BinaryOp)(int, int);

BinaryOp ops[] = { add, sub, mul };   // dispatch table
printf("%d\n", ops[2](4, 5));         // 20
```

A table of function pointers is how you build a state machine, a bytecode interpreter's dispatch loop, or a plugin interface — the technique that a `switch` grows into when the cases become data.

C++ additions: `std::function<int(int,int)>` accepts anything callable (function, lambda, functor) at the cost of possible allocation and indirect calls; a template parameter is zero-overhead but must be known at compile time. Non-static member functions need pointer-to-member syntax (`R (C::*)(args)`) because they carry an implicit `this`.

---

## 15. Callbacks

A callback is a function you hand to another function so it can call you back. Function pointers are the mechanism; callbacks are the pattern.

The canonical example is `qsort`, which sorts anything because it delegates comparison:

```c
#include <stdlib.h>

int cmp_int(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x > y) - (x < y);   // NOT x - y: that overflows
}

int a[] = {5, 2, 9, 1};
qsort(a, 4, sizeof a[0], cmp_int);
```

`qsort` knows nothing about `int`. It gets a base pointer, a count, an element size, and a comparator — enough to swap bytes and ask "which comes first?"

Writing your own callback-taking function:

```c
void for_each(int *a, size_t n, void (*fn)(int *, void *), void *ctx) {
    for (size_t i = 0; i < n; ++i) fn(&a[i], ctx);
}
```

That trailing `void *ctx` is the part people forget. A bare function pointer has no state, so without a context parameter your callback can only touch globals. Every well-designed C callback API passes a user pointer through untouched — see `pthread_create`, `bsearch`'s absence of one (a known wart), and every GUI toolkit ever written.

C++ solves the state problem with lambdas, which capture:

```cpp
int threshold = 10;
std::sort(v.begin(), v.end(), [threshold](int a, int b) {
    return std::abs(a - threshold) < std::abs(b - threshold);
});
```

A capture-less lambda converts implicitly to a plain function pointer, which is how you pass one to a C API.

---

## 16. Memory leaks and how to find them

A leak is heap memory that's still allocated but no longer reachable — you've lost the last pointer to it.

```c
void leak(void) {
    int *p = malloc(100);
    p = malloc(200);   // the first block is now unreachable and unfreeable
    free(p);           // frees only the second
}
```

Common causes: early `return` past the `free`, overwriting the only pointer, forgetting inner frees on jagged structures, and losing the original on a failed `realloc`.

### Finding them

```bash
# Sanitizers -- build-time, fast, use these by default
gcc -fsanitize=address,leak -g prog.c -o prog && ./prog

# Valgrind -- no rebuild needed, catches more, much slower
valgrind --leak-check=full --show-leak-kinds=all ./prog
```

Both also catch use-after-free and buffer overruns, which cause more damage than leaks do. A leak wastes memory; a use-after-free corrupts unrelated data.

### Preventing them

In C, discipline: allocate and free at the same level of abstraction, use a single cleanup path (`goto cleanup;` on error is idiomatic and correct here, not a stylistic sin), and document ownership in the function's header comment.

```c
int f(void) {
    int rc = -1;
    char *a = malloc(100);
    if (!a) goto done;
    char *b = malloc(200);
    if (!b) goto free_a;
    /* ... */
    rc = 0;
    free(b);
free_a:
    free(a);
done:
    return rc;
}
```

In C++, use RAII and the problem mostly disappears: `std::vector`, `std::string`, `std::unique_ptr`, `std::shared_ptr`. Destructors run on every exit path including exceptions, which no amount of manual `free` placement can guarantee. The remaining C++ leak is the reference cycle between two `shared_ptr`s — break it with `weak_ptr`.

---

## 17. Undefined behaviour checklist

Every one of these compiles cleanly and may appear to work:

- Dereferencing an uninitialized, `NULL`, or freed pointer
- Reading or writing past the end of an array
- Computing a pointer before the start of an array (even without dereferencing)
- Dereferencing one-past-the-end
- Writing through a `char *` that points at a string literal
- `free`ing the same pointer twice, or a non-heap pointer, or a mid-block pointer
- Returning the address of a local
- Reading an object through an incompatible pointer type (strict aliasing)
- Comparing or subtracting pointers into different objects

"Works on my machine" and "correct" are different claims. The sanitizers close most of the gap between them; use them from day one.

---

## Further reading

- **Kernighan & Ritchie**, *The C Programming Language*, ch. 5 — still the clearest treatment
- **Peter van der Linden**, *Expert C Programming: Deep C Secrets* — the array/pointer chapter is worth the book
- **cppreference.com** — accurate, standard-conforming, the reference to trust
- `man 3 malloc`, `man 3 qsort` — the local docs are better than most tutorials

Corrections and additions welcome via issue or PR.
