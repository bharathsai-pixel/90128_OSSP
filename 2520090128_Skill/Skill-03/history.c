#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define MAX_HISTORY 10
#define MAX_COMMAND 100

void disableRawMode(struct termios *old)
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, old);
}

void enableRawMode(struct termios *old)
{
    struct termios raw;

    tcgetattr(STDIN_FILENO, old);
    raw = *old;

    raw.c_lflag &= ~(ECHO | ICANON);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main()
{
    char history[MAX_HISTORY][MAX_COMMAND];
    char command[MAX_COMMAND];
    int history_count = 0;
    int history_pos = 0;
    int len = 0;
    char c;

    struct termios old;

    enableRawMode(&old);

    while (1)
    {
        printf("> ");
        fflush(stdout);

        len = 0;
        history_pos = history_count;

        while (1)
        {
            read(STDIN_FILENO, &c, 1);

            if (c == '\n' || c == '\r')
            {
                command[len] = '\0';
                printf("\n");

                break;
            }

            if (c == 127)
            {
                if (len > 0)
                {
                    len--;
                    printf("\b \b");
                    fflush(stdout);
                }
                continue;
            }

            if (c == 27)
            {
                char seq[2];

                read(STDIN_FILENO, &seq[0], 1);
                read(STDIN_FILENO, &seq[1], 1);

                if (seq[0] == '[' && seq[1] == 'A')
                {
                    if (history_pos > 0)
                    {
                        history_pos--;

                        printf("\33[2K\r> ");
                        strcpy(command, history[history_pos]);
                        len = strlen(command);

                        printf("%s", command);
                        fflush(stdout);
                    }
                }
                else if (seq[0] == '[' && seq[1] == 'B')
                {
                    if (history_pos < history_count)
                    {
                        history_pos++;

                        printf("\33[2K\r> ");

                        if (history_pos < history_count)
                        {
                            strcpy(command, history[history_pos]);
                            len = strlen(command);
                            printf("%s", command);
                        }
                        else
                        {
                            len = 0;
                            command[0] = '\0';
                        }

                        fflush(stdout);
                    }
                }

                continue;
            }

            if (len < MAX_COMMAND - 1)
            {
                command[len++] = c;
                putchar(c);
                fflush(stdout);
            }
        }

        if (strcmp(command, "exit") == 0)
            break;

        if (len > 0)
        {
            if (history_count < MAX_HISTORY)
            {
                strcpy(history[history_count], command);
                history_count++;
            }
            else
            {
                for (int i = 1; i < MAX_HISTORY; i++)
                    strcpy(history[i - 1], history[i]);

                strcpy(history[MAX_HISTORY - 1], command);
            }
        }
    }

    disableRawMode(&old);

    return 0;
}
