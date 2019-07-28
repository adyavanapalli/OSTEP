// 4.c
#include <assert.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t fork_result = fork();
    assert(fork_result != -1);

    if (fork_result == 0)
    // Child Process
    {
        execl("/bin/ls", "ls", "-l", (char*)NULL);
    }
    else
    // Parent Process
    {
        return 0;
    }
}
