#include <stdio.h>
#include <unistd.h>

int main() {
    int pid;
    printf("I am the parent process with ID %d\n", getpid());
    printf("Here I am before the use of forking\n");

    pid = fork();
    printf("Here I am just after forking\n");

    if (pid == 0)
        printf("I am a child process with ID %d\n", getpid());
    else
        printf("I am the parent process with PID %d\n", getpid());

    return 0;
}
