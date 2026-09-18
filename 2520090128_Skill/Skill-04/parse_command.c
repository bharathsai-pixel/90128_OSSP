#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 100
#define MAX_ARGS 20

struct Node
{
    char value[50];
    struct Node *left;
    struct Node *right;
};

struct Node *createNode(char value[])
{
    struct Node *node = malloc(sizeof(struct Node));

    strcpy(node->value, value);

    node->left = NULL;
    node->right = NULL;

    return node;
}

void printTree(struct Node *root, int level)
{
    if (root == NULL)
        return;

    for (int i = 0; i < level; i++)
        printf("  ");

    printf("%s\n", root->value);

    printTree(root->left, level + 1);
    printTree(root->right, level + 1);
}

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

    struct Node *root = createNode("COMMAND");

    struct Node *current = root;

    for (int i = 0; i < count; i++)
    {
        current->left = createNode(args[i]);

        if (i < count - 1)
        {
            current->right = createNode("ARGUMENT");
            current = current->right;
        }
    }

    printf("\nParse Tree:\n");

    printTree(root, 0);

    return 0;
}
