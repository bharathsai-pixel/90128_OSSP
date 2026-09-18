#include <stdio.h>
#include <string.h>

#define MAX_INPUT 200
#define MAX_ARGS 20

int main()
{
    char input[MAX_INPUT];
    char *args[MAX_ARGS];
    int count = 0;

    printf("> ");
    fgets(input, MAX_INPUT, stdin);

    input[strcspn(input, "\n")] = '\0';

    char *token = strtok(input, " \t");

    while (token != NULL && count < MAX_ARGS)
    {
        args[count] = token;
        count++;

        token = strtok(NULL, " \t");
    }

    if (count == 0)
    {
        printf("Error: Empty command\n");
        return 1;
    }

    printf("\nParsed Command:\n");

    for (int i = 0; i < count; i++)
    {
        printf("Argument %d: %s\n", i + 1, args[i]);
    }

    return 0;
}
