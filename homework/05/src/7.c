// 7.c
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
        close(STDOUT_FILENO);
        printf("Can you see me?!\n");
        return 0;
    }
    else
    // Parent Process
    {
        wait(NULL);
    }
    
    return 0;
}