// 5.c
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    pid_t fork_result = fork();
    assert(fork_result != -1);

    if (fork_result == 0)
    // Child Process
    {
        printf("Child Process PID: %d\n", getpid());

        printf("Making child nap for five seconds.\n");
        sleep(5);

        printf("Calling wait() from child process returns: %d\n", wait(NULL));
        printf("Child process exiting.\n");
    }
    else
    // Parent Process
    {
        printf("Parent Process PID: %d\n", getpid());

        printf("Calling wait() from parent process returns: %d\n", wait(NULL));
        printf("Parent process exiting.\n");
    }
    
    return 0;
}