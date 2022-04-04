#pragma once

#include "../utils/request.h"
#include "../utils/lectureSecurisee.h"

struct request_processing{
    struct request request;
    unsigned int sock;
    struct sockaddr_in adr_client;
    struct user *shared_memory;
};

/**
*\brief Log in an user and put it in the shared memory for make it connected
*
*\param args [struct request_processing] all infomations that a thread needs to respond to a request
*\return void* Nothing
*/
void *login(void* args);

/**
*\brief Log out an user and remove it from the shared memory for make it disconnected
*
*\param args [struct request_processing] all infomations that a thread needs to respond to a request
*\return void* Nothing
*/
void *logout(void* args);

/**
*\brief Create an user and put it in the CSV file (used for account store)
*
*\param args [struct request_processing] all infomations that a thread needs to respond to a request
*\return void* Nothing
*/
void *account_creation(void* args);

/**
*\brief Delete an user and remove it from the CSV file (used for account store)
*
*\param args [struct request_processing] all infomations that a thread needs to respond to a request
*\return void* Nothing
*/
void *account_deletion(void* args);

/**
*\brief Collect each user connected to the server and send them to the client
*
*\param args [struct request_processing] all infomations that a thread needs to respond to a request
*\return void* Nothing
*/
void *connected_users(void* args);
