// main.c
#include <assert.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define SEC_TO_USEC 1000000

int main()
{
    int fd = open("/dev/zero", O_RDONLY);
    assert(fd != -1);

    struct timeval tv_0;
    struct timeval tv_1;
    int n_iter = 1000000;

    memset(&tv_0, 0, sizeof(struct timeval));
    memset(&tv_1, 0, sizeof(struct timeval));

    double average_time = 0.0;

    for (int i = 0; i < n_iter; i++)
    {
        gettimeofday(&tv_0, NULL);
        read(fd, 0, 0);
        gettimeofday(&tv_1, NULL);

        average_time += (double)(tv_1.tv_sec * SEC_TO_USEC + tv_1.tv_usec - 
            tv_0.tv_sec * SEC_TO_USEC - tv_0.tv_usec) / n_iter;
    }

    printf("Average time for 0-byte read: %1.2f us\n", average_time);

    return 0;
}