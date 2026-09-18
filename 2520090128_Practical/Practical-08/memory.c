#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *a, *b;

    // malloc
    a = malloc(3 * sizeof(int));

    if (a == NULL)
    {
        printf("malloc failed\n");
        return 1;
    }

    a[0] = 10;
    a[1] = 20;
    a[2] = 30;

    printf("malloc: %d %d %d\n", a[0], a[1], a[2]);

    // calloc
    b = calloc(3, sizeof(int));

    if (b == NULL)
    {
        printf("calloc failed\n");
        free(a);
        return 1;
    }

    printf("calloc: %d %d %d\n", b[0], b[1], b[2]);

    // realloc
    a = realloc(a, 5 * sizeof(int));

    if (a == NULL)
    {
        printf("realloc failed\n");
        free(b);
        return 1;
    }

    a[3] = 40;
    a[4] = 50;

    printf("realloc: %d %d %d %d %d\n",
           a[0], a[1], a[2], a[3], a[4]);

    // free
    free(a);
    free(b);

    printf("Memory freed successfully.\n");

    return 0;
}
