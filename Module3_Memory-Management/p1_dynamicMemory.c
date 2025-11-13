/*
	Dynamic Memory Allocation in C
    ------------------------------
    In C, dynamic memory is allocated from the heap at runtime using functions
    from the <stdlib.h> library.

    Functions:
        1. malloc(size): Allocates raw memory (uninitialized)
        2. calloc(n, size): Allocates and initializes to zero
        3. realloc(ptr, new_size): Changes the size of allocated memory
        4. free(ptr): Frees allocated memory

    Notes:
        - malloc returns a void pointer (void*), which must be cast to the proper type.
        - Always check if malloc returns NULL (allocation failure).
        - After freeing memory, assign the pointer to NULL to avoid dangling pointers.
        - Freeing a NULL pointer is safe — it does nothing.

*/

#include <stdio.h>
#include <stdlib.h>

int main() {

    // Allocate memory for one integer using malloc
	int* p = malloc(sizeof(int));   // malloc only allocates memory does not initialize it

    // Always check if allocation was successful
    if (p == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Initialize the allocated memory
    *p = 5;

    printf("Value stored at allocated memory: %d\n", *p);
    printf("Address of allocated memory: %p\n", (void*)p);

    // Free the allocated memory
    free(p);

    // After freeing, make pointer NULL to avoid dangling pointer
    p = NULL;

    // Safe: calling free on NULL does nothing
    free(p);

    return 0;
}
