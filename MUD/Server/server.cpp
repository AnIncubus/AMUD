// =================
// MUD Server Side Application
//
// This is the server entrance point for MUD. It spawns a single thread (listener).
// The main thread acts as a way to check on the server's status.
//
// (c) AnIncubus
// =================

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

#include "Connection/Server.hpp"

int main(int argc, char** argv)
{
    fprintf(stdout, "Starting server...\n");
    Server server;

    fprintf(stdout, "Finished!\n");


    return 0;
}
