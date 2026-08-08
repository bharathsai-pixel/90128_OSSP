#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int source, destination;
    char buffer[1024];
    ssize_t bytesRead;

    source = open("source.txt", O_RDONLY);

    if(source < 0)
    {
        perror("Error opening source file");
        return 1;
    }

    destination = open("destination.txt",
                       O_WRONLY | O_CREAT | O_TRUNC,
                       0644);

    if(destination < 0)
    {
        perror("Error opening destination file");
        close(source);
        return 1;
    }

    while((bytesRead = read(source, buffer, sizeof(buffer))) > 0)
    {
        write(destination, buffer, bytesRead);
    }

    printf("File copied successfully.\n");

    close(source);
    close(destination);

    return 0;
} 
