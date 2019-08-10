// 2.c
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define PATHNAME "../bin/file.txt"

int main()
{
    int fd = open(PATHNAME, O_CREAT | O_WRONLY);
    if (fd == -1)
    {
        fprintf(stderr, "[ERROR] open(%d): %s\n", errno, strerror(errno));
        exit(errno);
    }

    pid_t fork_result = fork();
    if (fork_result == -1)
    {
        fprintf(stderr, "[ERROR] fork(%d): %s\n", errno, strerror(errno));
        exit(errno);
    }
    else if (fork_result == 0)
    // Child Process
    {
        const char* buffer = "Hello, from the child process!";
        size_t buffer_size = strlen(buffer) + 1;

        ssize_t write_result = write(fd, buffer, buffer_size);
        if (write_result == -1)
        {
            fprintf(stderr, "[ERROR] write(%d): %s\n", errno, strerror(errno));
            exit(errno);
        }
    }
    else 
    // Parent Process
    {
        const char* buffer = "Hello, from the parent process!";
        size_t buffer_size = strlen(buffer) + 1;

        ssize_t write_result = write(fd, buffer, buffer_size);
        if (write_result == -1)
        {
            fprintf(stderr, "[ERROR] write(%d): %s\n", errno, strerror(errno));
            exit(errno);
        }

        pid_t wait_result = wait(NULL);
        if (wait_result == -1)
        {
            fprintf(stderr, "[ERROR] wait(%d): %s\n", errno, strerror(errno));
            exit(errno);
        }

        int close_result = close(fd);
        if (close_result == -1)
        {
            fprintf(stderr, "[ERROR] close(%d): %s\n", errno, strerror(errno));
            exit(errno);
        }
    }

    return 0;
}
