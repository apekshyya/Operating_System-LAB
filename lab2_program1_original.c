#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("This demonstrates the fork\n");
    fork();
    printf("Hello world\n");
    return 0;
}
