// 1.c
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    int x = 100;
    pid_t fork_result = fork();

    if (fork_result == -1)
    {
        fprintf(stderr, "[ERROR] fork(%d): %s\n", errno, strerror(errno));
        exit(errno);
    }
    else if (fork_result == 0)
    // Child Process
    {
        printf("The value of x in the child process is: %d\n", x);

        x += 50;
        printf("After x is incremented by 50, the value of x in the child process is: %d\n", x);

        return 0;
    }
    else
    // Parent Process
    {
        x -= 50;
        printf("After x is decremented by 50, the value of x in the parent process is: %d\n", x);

        return 0;
    }
}
