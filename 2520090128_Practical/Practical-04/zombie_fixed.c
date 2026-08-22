#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
    {
        printf("Fork Failed\n");
        return 1;
    }

    if (pid == 0)
    {
        printf("Child Process\n");
        printf("PID : %d\n", getpid());
        printf("Child exiting...\n");
        exit(0);
    }
    else
    {
        printf("Parent Process\n");
        printf("PID : %d\n", getpid());

        wait(NULL);

        printf("Child completed successfully.\n");
        printf("No zombie process remains.\n");
        printf("Parent exiting.\n");
    }

    return 0;
}

