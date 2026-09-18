#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int *data = malloc(5 * sizeof(int));

    for (int i = 0; i < 5; i++)
        data[i] = i + 1;

    printf("Before fork:\n");
    printf("Parent data address: %p\n", (void *)data);

    pid_t pid = fork();

    if (pid < 0)
    {
        printf("fork failed\n");
        free(data);
        return 1;
    }

    if (pid == 0)
    {
        printf("\nChild process:\n");
        printf("Child data address: %p\n", (void *)data);

        data[0] = 100;

        printf("Child modified data[0] = %d\n", data[0]);

        printf("Child data address after modification: %p\n",
               (void *)data);

        free(data);
    }
    else
    {
        wait(NULL);

        printf("\nParent process:\n");
        printf("Parent data[0] = %d\n", data[0]);

        free(data);
    }

    return 0;
}
