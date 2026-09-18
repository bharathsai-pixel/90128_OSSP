#include <stdio.h>
#include <string.h>

#define MAX_INPUT 100
#define MAX_TOKENS 20

struct Token
{
    char value[50];
    char type[20];
};

int main()
{
    char input[MAX_INPUT];
    struct Token tokens[MAX_TOKENS];
    int count = 0;

    printf("> ");
    fgets(input, MAX_INPUT, stdin);

    input[strcspn(input, "\n")] = '\0';

    char *token = strtok(input, " \t");

    while (token != NULL && count < MAX_TOKENS)
    {
        strcpy(tokens[count].value, token);

        if (count == 0)
            strcpy(tokens[count].type, "COMMAND");
        else
            strcpy(tokens[count].type, "ARGUMENT");

        count++;

        token = strtok(NULL, " \t");
    }

    printf("\nToken Stream:\n");

    for (int i = 0; i < count; i++)
    {
        printf("%d: %s -> %s\n",
               i + 1,
               tokens[i].value,
               tokens[i].type);
    }

    return 0;
}
