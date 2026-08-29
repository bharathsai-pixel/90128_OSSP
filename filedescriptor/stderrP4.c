#include <unistd.h>
int main()
{
    write(STDERR_FILENO, "This is an error\n", 17);
    return 0;
}

As STDERR_FILENO is: 2
write(STDERR_FILENO, "This is an error\n", 17) is equivalent to:
write(2, "This is an error\n", 17);
