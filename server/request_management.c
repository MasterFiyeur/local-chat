#include "request_management.h"

void *login(void* args){
    /* Request informations */
    struct request_processing *parent_info = args;

    int separator_pos;//Index of the separator
    char username[MAX_USER_USERNAME_LENGTH], password[MAX_USER_PASSWORD_LENGTH];//Username and password got from request

    char data[REQUEST_DATA_MAX_LENGTH];
    strcpy(data,(*parent_info).request.data);//Put request data in data

    printf("[Login-thread] - Received data (length : %ld): %s\n", strlen(data), data); //Log

    /* parse data to username and password */
    //Get pos of separator
    for (separator_pos = 0; separator_pos < strlen(data) && data[separator_pos] != USER_SEPARATOR; separator_pos++);
    
    //Check string param length
    if (separator_pos >= MAX_USER_USERNAME_LENGTH || strlen(data)-separator_pos > MAX_USER_PASSWORD_LENGTH){
        (*parent_info).request.type = -1; //There is an error
        strcpy((*parent_info).request.data,"Username or password are too long");
        sendto ((*parent_info).sock, (void *) &(*parent_info).request, sizeof(struct request), 0, (struct sockaddr *) &(*parent_info).adr_client, sizeof((*parent_info).adr_client));
        pthread_exit(NULL);
    }else if (separator_pos == 0 || separator_pos == strlen(data)-1){
        (*parent_info).request.type = -1; //There is an error
        strcpy((*parent_info).request.data,"Username or password are empty");
        sendto ((*parent_info).sock, (void *) &(*parent_info).request, sizeof(struct request), 0, (struct sockaddr *) &(*parent_info).adr_client, sizeof((*parent_info).adr_client));
        pthread_exit(NULL);
    }
    
    /* Copy username and password from data */
    strncpy(username,data,separator_pos);
    strncpy(password,&data[separator_pos]+1,strlen(data)-separator_pos);    

    //TODO : Make the connection (check user exist and add to connected user and creation of token)
    sprintf((*parent_info).request.data, "I show this username :'%s' and this password:'%s'",username,password);
    //strcpy((*parent_info).request.data,"token:MYSUPERTOKEN");

    /* Sending response */
    (*parent_info).request.type = 0; //All went right
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