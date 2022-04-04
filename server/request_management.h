#pragma once

#include "../utils/request.h"
#include <netinet/in.h> 

struct request_processing{
    struct request request;
    unsigned int sock;
    struct sockaddr_in adr_client;
    struct user *shared_memory;
};