#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COMMAND_SIZE 100

int main()
{
    char **history;
    int count = 0;
    int capacity = 2;

    history = malloc(capacity * sizeof(char *));

    if (history == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    while (1)
    {
        char buffer[COMMAND_SIZE];

        printf("> ");
        fgets(buffer, COMMAND_SIZE, stdin);

        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "exit") == 0)
            break;

        if (count == capacity)
        {
            capacity *= 2;

            history = realloc(history,
                              capacity * sizeof(char *));

            if (history == NULL)
            {
                printf("Reallocation failed\n");
                return 1;
            }
        }

        history[count] = malloc(
            (strlen(buffer) + 1) * sizeof(char)
        );

        if (history[count] == NULL)
        {
            printf("Memory allocation failed\n");
            return 1;
        }

        strcpy(history[count], buffer);

        count++;
    }

    printf("\nCommand History:\n");

    for (int i = 0; i < count; i++)
    {
        printf("%d: %s\n", i + 1, history[i]);
    }

    for (int i = 0; i < count; i++)
        free(history[i]);

    free(history);

    return 0;
}
