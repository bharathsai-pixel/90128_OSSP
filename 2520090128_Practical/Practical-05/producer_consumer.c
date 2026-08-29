#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define N 100000

int main()
{
    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return 1;
    }

    if (pid == 0)
    {
        close(pipefd[1]);

        int sum = 0;
        int value;
        int count = 0;

        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);

        while (read(pipefd[0], &value, sizeof(value)) > 0)
        {
            sum += value;
            count++;
        }

        clock_gettime(CLOCK_MONOTONIC, &end);

        double time_taken =
            (end.tv_sec - start.tv_sec) +
            (end.tv_nsec - start.tv_nsec) / 1e9;

        close(pipefd[0]);

        printf("Consumer: Received %d integers\n", count);
        printf("Consumer: Sum of received data = %d\n", sum);
        printf("Communication Time: %.6f seconds\n", time_taken);

        if (time_taken > 0)
        {
            printf("Communication Throughput: %.2f MB/s\n",
                   (N * sizeof(int)) / (time_taken * 1024 * 1024));
        }

        wait(NULL);
        return 0;
    }
    else
    {
        close(pipefd[0]);

        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);

        for (int i = 1; i <= N; i++)
        {
            write(pipefd[1], &i, sizeof(i));
        }

        close(pipefd[1]);

        clock_gettime(CLOCK_MONOTONIC, &end);

        double time_taken =
            (end.tv_sec - start.tv_sec) +
            (end.tv_nsec - start.tv_nsec) / 1e9;

        printf("Producer: Generated %d integers\n", N);
        printf("Producer: Sent %zu bytes through pipe\n",
               N * sizeof(int));
        printf("Producer Time: %.6f seconds\n", time_taken);

        wait(NULL);
    }

    return 0;
}
