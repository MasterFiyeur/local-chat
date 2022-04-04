#include "request_management.h"

void *login(void* args){
    /* Request informations */
    struct request_processing *parent_info = args;

    char data[REQUEST_DATA_MAX_LENGTH];
    strcpy(data,(*parent_info).request.data);//Put request data in data

    printf("[Login-thread] - Received data (length : %ld): %s\n", strlen(data), data); //Log

    //TODO : Make the connection (check user exist and add to connected user and creation of token)
    strcpy((*parent_info).request.data,"token:MYSUPERTOKEN");

    /* Sending response */
    sendto ((*parent_info).sock, (void *) &(*parent_info).request, sizeof(struct request), 0, (struct sockaddr *) &(*parent_info).adr_client, sizeof((*parent_info).adr_client)); 
    
    pthread_exit(NULL);
}

void *logout(void* args){
    /* Request informations */
    struct request_processing *parent_info = args;

    char data[REQUEST_DATA_MAX_LENGTH];
    strcpy(data,(*parent_info).request.data);//Put request data in data

    printf("[Logout-thread] - Received data (length : %ld): %s\n", strlen(data), data); //Log
    
    //TODO : Make the deconnection (Removing user from the shared memory)
    strcpy((*parent_info).request.data,"ok");

    /* Sending response */
    sendto ((*parent_info).sock, (void *) &(*parent_info).request, sizeof(struct request), 0, (struct sockaddr *) &(*parent_info).adr_client, sizeof((*parent_info).adr_client)); 
    
    pthread_exit(NULL);
}

void *account_creation(void* args){
    /* Request informations */
    struct request_processing *parent_info = args;

    char data[REQUEST_DATA_MAX_LENGTH];
    strcpy(data,(*parent_info).request.data);//Put request data in data

    printf("[Account_creation-thread] - Received data (length : %ld): %s\n", strlen(data), data); //Log
    
    //TODO : Make the creation of the account (using Alan's code)
    strcpy((*parent_info).request.data,"ok");

    /* Sending response */
    sendto ((*parent_info).sock, (void *) &(*parent_info).request, sizeof(struct request), 0, (struct sockaddr *) &(*parent_info).adr_client, sizeof((*parent_info).adr_client)); 
    
    pthread_exit(NULL);
}

void *account_deletion(void* args){
    /* Request informations */
    struct request_processing *parent_info = args;

    char data[REQUEST_DATA_MAX_LENGTH];
    strcpy(data,(*parent_info).request.data);//Put request data in data

    printf("[Account_deletion-thread] - Received data (length : %ld): %s\n", strlen(data), data); //Log
    
    //TODO : Make the deletion of the account (using Alan's code)
    strcpy((*parent_info).request.data,"ok");

    /* Sending response */
    sendto ((*parent_info).sock, (void *) &(*parent_info).request, sizeof(struct request), 0, (struct sockaddr *) &(*parent_info).adr_client, sizeof((*parent_info).adr_client)); 
    
    pthread_exit(NULL);
}

void *connected_users(void* args){
    /* Request informations */
    struct request_processing *parent_info = args;

    char data[REQUEST_DATA_MAX_LENGTH];
    strcpy(data,(*parent_info).request.data);//Put request data in data

    printf("[Connected_users-thread] - Received data (length : %ld): %s\n", strlen(data), data); //Log
    
    //TODO : Make the deletion of the account (using Alan's code)
    strcpy((*parent_info).request.data,"ok");

    /* Sending response */
    sendto ((*parent_info).sock, (void *) &(*parent_info).request, sizeof(struct request), 0, (struct sockaddr *) &(*parent_info).adr_client, sizeof((*parent_info).adr_client)); 
    
    pthread_exit(NULL);
}