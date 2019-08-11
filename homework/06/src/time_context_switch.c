// time_context_switch.c
#define _GNU_SOURCE

#include <assert.h>
#include <errno.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SEC_TO_USEC 1000000

/**
 * @brief Wraps the close(2) function.
 */
void w_close(int fd)
{
    if (close(fd) == -1)
    {
        fprintf(stderr, "close(%d): %s\n", errno, strerror(errno));
        exit(errno);
    }
}

/**
 * @brief Wraps the fork(2) function.
 */
pid_t w_fork()
{
    pid_t fork_result = fork();

    if (fork_result == -1)
    {
        fprintf(stderr, "fork(%d): %s\n", errno, strerror(errno));
        exit(errno);
    }

    return fork_result;
}

/**
 * @brief Wraps the pipe(2) function.
 */
void w_pipe(int pipefd[2])
{
    if (pipe(pipefd) == -1)
    {
        fprintf(stderr, "pipefd(%d): %s\n", errno, strerror(errno));
        exit(errno);
    }
}

/**
 * @brief Wraps the read(2) function.
 */
void w_read(int fd, void* buf, size_t nbytes)
{
    if (read(fd, buf, nbytes) == -1)
    {
        fprintf(stderr, "read(%d): %s\n", errno, strerror(errno));
        exit(errno);
    }
}

/**
 * @brief Wraps the write(2) function.
 */
void w_write(int fd, void* buf, size_t nbytes)
{
    if (write(fd, buf, nbytes) == -1)
    {
        fprintf(stderr, "write(%d): %s\n", errno, strerror(errno));
        exit(errno);
    }
}

int main()
{
    // Define pipes for parent and child processes.
    int c_pipefd[2];
    int p_pipefd[2];
    char buf;

    w_pipe(c_pipefd);
    w_pipe(p_pipefd);

    // Define CPU affinity flags.
    cpu_set_t cs;
    CPU_ZERO(&cs);
    CPU_SET(0, &cs);

    struct timeval tv_0;
    struct timeval tv_1;
    int n_iter = 1000000;

    memset(&tv_0, 0, sizeof(struct timeval));
    memset(&tv_1, 0, sizeof(struct timeval));

    double average_time = 0.0;

    // Fork process to create parent and child processes.
    pid_t pid = w_fork();

    if (pid == 0)
    // Child Process.
    {
        // Set CPU affinity.
        sched_setaffinity(0, sizeof(cpu_set_t), &cs);

        // Close the unused pipe ends.
        w_close(c_pipefd[0]);
        w_close(p_pipefd[1]);

        for (int i = 0; i < n_iter; i++)
        {
            buf = '1';
            w_write(c_pipefd[1], &buf, sizeof(char));

            buf = '\0';
            w_read(p_pipefd[0], &buf, sizeof(char));
        }

        w_close(c_pipefd[1]);
        w_close(p_pipefd[0]);

        return 0;
    }
    else
    // Parent Process.
    {
        // Set CPU affinity.
        sched_setaffinity(0, sizeof(cpu_set_t), &cs);

        // Close the unused pipe ends.
        w_close(p_pipefd[0]);
        w_close(c_pipefd[1]);


        for (int i = 0; i < n_iter; i++)
        {
            gettimeofday(&tv_0, NULL);

            buf = '1';
            w_write(p_pipefd[1], &buf, sizeof(char));

            buf = '\0';
            w_read(c_pipefd[0], &buf, sizeof(char));

            gettimeofday(&tv_1, NULL);

            average_time += (double)(tv_1.tv_sec * SEC_TO_USEC + tv_1.tv_usec - 
                tv_0.tv_sec * SEC_TO_USEC - tv_0.tv_usec) / n_iter;
        }

        w_close(p_pipefd[1]);
        w_close(c_pipefd[0]);

        wait(NULL);
    }

    printf("Average time for context switch: %1.2f us\n", average_time);

    return 0;
}