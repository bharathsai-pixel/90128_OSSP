#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
int main()
{
    char command[100];
    char *args[20];
    printf("Enter Linux command: ");
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = '\0';
    int i = 0;
    args[i] = strtok(command, " ");
    while(args[i] != NULL)
    {
        i++;
        args[i] = strtok(NULL, " ");
    }
    pid_t pid = fork();
    if(pid == 0)
    {
        printf("\nChild Process\n");
        printf("Child PID : %d\n", getpid());
        printf("Parent PID: %d\n\n", getppid());
        execvp(args[0], args);
        perror("Execution Failed");
        exit(1);
    }
    else if(pid > 0)
    {
        printf("\nParent Process\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID : %d\n", pid);
        wait(NULL);
        printf("\nChild execution completed.\n");
    }
    else
    {
        printf("Fork failed.\n");
    }
    return 0;
}
