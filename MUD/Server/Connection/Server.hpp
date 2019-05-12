#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>

#include "NetworkInfo.h"

void* get_in_addr(struct sockaddr* sa)
{
    if(sa->sa_family == AF_INET)
    {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

class Server
{
public:
    Server()
    {
        fprintf(stdout, "Starting listener thread...\n");
        
        fprintf(stdout, "Created thread!\n");
    }

    void* ping(void* args)
    {

    }

    static void* listener(void* args)
    {
        int sockfd, newfd;
        struct addrinfo hints, *server, *p;
        struct sockaddr_storage conn_addr;
        socklen_t sin_size;
        struct sigaction sa;
        int yes = 1;
        char s[INET6_ADDRSTRLEN];
        int rv;

        memset(&hints, 0, sizeof(hints));
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;

        if((rv = getaddrinfo(NULL, PORT, &hints, &server)))
        {
            fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
            return NULL;
        }

        for(p = server; p != NULL; p = p->ai_next)
        {
            if((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
            {
                perror("unable to create socket\n");
                return NULL;
            }

            if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
            {
                perror("uable to mount the socket\n");
                return NULL;
            }

            if(bind(sockfd, p->ai_addr, p->ai_addrlen) == -1)
            {
                close(sockfd);
                perror("unable to bind the socket\n");
                return NULL;
            }

            break;
        }

        freeaddrinfo(server);

        if(p == NULL)
        {
            fprintf(stderr, "server: failed to bind the socket\n");
            return NULL;
        }

        if(listen(sockfd, MAXWAIT) == -1)
        {
            perror("listening failed\n");
            return NULL;
        }

        printf("online and waiting for connections...\n");

        while(1)
        {
            sin_size = sizeof(conn_addr);
            newfd = accept(sockfd, (struct sockaddr*)&conn_addr, &sin_size);
            if(newfd == -1)
            {
                perror("unable to accept connection");
            }

            inet_ntop(conn_addr.ss_family,
                get_in_addr((struct sockaddr*)&conn_addr),
                s, sizeof(s));

            printf("received connection from: %s\n", s);

            if(!fork())
            {
                close(sockfd);
                if(send(newfd, "Hello, world!", 13, 0) == -1)
                    perror("send");
                close(newfd);
                exit(0);
            }
            close(newfd);
        }

        return NULL;
    }

private:
    pthread_t thrd_listen(listener, NULL), thrd_ping, thrd_logic;
    
    //int connected_sockets[MAXCONN];
};

#endif