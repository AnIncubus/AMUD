#ifndef _NETWORK_INFO_H_
#define _NETWORK_INFO_H_

#define PORT "8080"
#define MAXCONN 50
#define MAXWAIT 10
#define MAXBYTES 1<<10 // 2^10

enum NetworkCodes
{
    CONN,
    SGNP,
    LOGN,
    FAIL,
    MSGE,
    DIRC,
};

#endif