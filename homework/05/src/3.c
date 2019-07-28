// 3.c
#include <assert.h>
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
    struct addrinfo hints;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    struct addrinfo* res;
    assert(getaddrinfo("127.0.0.1", "8080", &hints, &res) == 0);

    int parent_sockfd = socket(res->ai_family, res->ai_socktype,
        res->ai_protocol);
    assert(parent_sockfd != -1);

    assert(bind(parent_sockfd, res->ai_addr, res->ai_addrlen) == 0);

    assert(listen(parent_sockfd, SOMAXCONN) == 0);

    pid_t fork_result = fork();
    if (fork_result == -1)
    {
        fprintf(stderr, "[ERROR] fork(%d): %s\n", errno, strerror(errno));
        exit(errno);
    }
    else if (fork_result == 0)
    // Child Process
    {
        printf("Hello\n");

        int child_sockfd = socket(res->ai_family, res->ai_socktype,
            res->ai_protocol);
        assert(child_sockfd != -1);

        assert(connect(child_sockfd, res->ai_addr, res->ai_addrlen) == 0);

        assert(send(child_sockfd, "FIN", sizeof("FIN"), 0) != -1);

        assert(close(child_sockfd) != -1);
    }
    else
    // Parent Process
    {
        assert(accept(parent_sockfd, NULL, NULL) != -1);

        assert(close(parent_sockfd) == 0);

        printf("Goodbye\n");
    }
}