#include <stdio.h>
#include <stdlib.h>

int global_var = 10;
static int static_var = 20;

void code_function()
{
}

int main()
{
    int stack_var = 30;

    int *heap_var = malloc(sizeof(int));
    *heap_var = 40;

    printf("Code   : %p\n", (void *)code_function);
    printf("Global : %p\n", (void *)&global_var);
    printf("Static : %p\n", (void *)&static_var);
    printf("Heap   : %p\n", (void *)heap_var);
    printf("Stack  : %p\n", (void *)&stack_var);

    getchar();

    free(heap_var);

    return 0;
}
