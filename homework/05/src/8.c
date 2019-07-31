// 8.c
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./8.out \"<string>\"\n");
        exit(1);
    }

    int pipefd[2];
    memset(pipefd, 0, sizeof(pipefd));

    assert(pipe(pipefd) != -1);

    pid_t child_pid = fork();
    assert(child_pid != -1);

    if (child_pid == 0)
    // Child Process.
    // The child process writes the value of argv[1] into the write-end of the
    // pipe.
    {
        // Close the read-end of the pipe.
        assert(close(pipefd[0]) != -1);

        assert(write(pipefd[1], argv[1], strlen(argv[1])) != -1);

        // Close the write-end of the pipe.
        assert(close(pipefd[1]) != -1);
    }
    else
    // Parent Process.
    // The parent process reads the value at the read-end of the pipe and prints
    // that to `stdout`.
    {
        // Close the write-end of the pipe.
        assert(close(pipefd[1]) != -1);

        char buf;
        while (read(pipefd[0], &buf, sizeof(buf)) != 0)
        {
            printf("%c", buf);
        }
        printf("\n");

        // Close the read-end of the pipe.
        assert(close(pipefd[0]) != -1);

        wait(NULL);
    }
}