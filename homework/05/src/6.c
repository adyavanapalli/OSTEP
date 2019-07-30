// 6.c
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

        printf("Child process exiting.\n");
    }
    else
    // Parent Process
    {
        printf("Parent Process PID: %d\n", getpid());

        printf("Calling waitpid(%d, ...) from parent process returns: %d\n",
            fork_result, waitpid(fork_result, NULL, 0));
        printf("Parent process exiting.\n");
    }
    
    return 0;
}