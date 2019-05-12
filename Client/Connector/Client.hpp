#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#include <iostream>

#include "NetworkInfo.h"

class Connection
{
public:
    Connection(int port)
    {
        this->port = port;
        
        std::cout << "Populating connection info..." << std::endl;
        server.sin_family = AF_INET;
        server.sin_port = htons(this->port);
        server.sin_addr.s_addr = inet_addr("127.0.0.1");
        std::cout << "Done!" << std::endl;

        std::cout << "Attempting to create socket..." << std::endl;
        if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        {
            std::cout << "Failure trying to create a socket."
                        << "Exiting application" << std::endl;
            exit(1);
        }
        std::cout << "Created socket successfully!" << std::endl;
    }

    bool attempt_connection()
    {
        if(connect(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0)
            return false;
        else
            return true;
    }

    bool send_message()
    {
        send(sockfd, "Hello!", strlen("Hello!"), 0);
        return false;
    }
    
    std::string getOS()
    {
        #ifdef _WIN32
        os = "WIN32";
        #elif _WIN64
        os = "WIN64";
        #elif __unix || __unix__
        os = "Unix";
        #elif __APPLE__ || __MACH__
        os = "Mac";
        #elif __linux__
        os = "Linux";
        #elif __FreeBSD__
        os = "FreeBSD;"
        #else
        os = "Unknown";
        #endif

        return os;
    }
    
private:
    int port, sockfd;
    
    std::string os;

    struct sockaddr_in server;

};

#endif