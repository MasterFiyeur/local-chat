#include "request_management.h"

void *login(void* args){
    /* Request informations */
    struct request_processing *parent_info = args;

    int separator_pos;//Index of the separator
    char username[MAX_USER_USERNAME_LENGTH], password[MAX_USER_PASSWORD_LENGTH];//Username and password got from request
    char *token = malloc(TOKEN_SIZE*sizeof(char));//Token generated

    char data[REQUEST_DATA_MAX_LENGTH];
    strcpy(data,(*parent_info).request.data);//Put request data in data

    printf("\t[Login-thread] - Received data (length : %ld): %s\n", strlen(data), data); //Log

    /* parse data to username and password */
    //Get pos of separator
    for (separator_pos = 0; separator_pos < strlen(data) && data[separator_pos] != USER_PASSWORD_SEPARATOR; separator_pos++);
    
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

    //TODO : Check username/password in file

    /* Adding user to the shared memory */
    switch (add_user((*parent_info).shared_memory,username,&token)){
    case 0://All went right
        (*parent_info).request.type = 0;
        strcpy((*parent_info).request.data,token);
        sendto ((*parent_info).sock, (void *) &(*parent_info).request, sizeof(struct request), 0, (struct sockaddr *) &(*parent_info).adr_client, sizeof((*parent_info).adr_client)); 
        break;
    case 1://User already connected
        (*parent_info).request.type = -1; 
        strcpy((*parent_info).request.data,"User already connected");
        sendto ((*parent_info).sock, (void *) &(*parent_info).request, sizeof(struct request), 0, (struct sockaddr *) &(*parent_info).adr_client, sizeof((*parent_info).adr_client)); 
        break;
    default://Shared memory full of connected user
        (*parent_info).request.type = -1; 
        strcpy((*parent_info).request.data,"Maximum number of simultaneous connections reached");
        sendto ((*parent_info).sock, (void *) &(*parent_info).request, sizeof(struct request), 0, (struct sockaddr *) &(*parent_info).adr_client, sizeof((*parent_info).adr_client)); 
        break;
    }
    pthread_exit(NULL);
}

void *logout(void* args){
    /* Request informations */
    struct request_processing *parent_info = args;

    char token[TOKEN_SIZE];//Token got when log in

    if(strlen((*parent_info).request.data) != (TOKEN_SIZE-1)){ //Token doesn't have the right format
        (*parent_info).request.type = -1; 
        strcpy((*parent_info).request.data,"The token doesn't have the right format");
        sendto ((*parent_info).sock, (void *) &(*parent_info).request, sizeof(struct request), 0, (struct sockaddr *) &(*parent_info).adr_client, sizeof((*parent_info).adr_client)); 
    }

    printf("[Logout-thread] - Received data (length : %ld): %s\n", strlen(token), token); //Log
    
    /* Sending response */
    switch (remove_user((*parent_info).shared_memory,token)){
    case 0://All went right
        (*parent_info).request.type = 0;
        strcpy((*parent_info).request.data,"User disconnected");
        sendto ((*parent_info).sock, (void *) &(*parent_info).request, sizeof(struct request), 0, (struct sockaddr *) &(*parent_info).adr_client, sizeof((*parent_info).adr_client)); 
        break;
    default://User not found
        (*parent_info).request.type = -1; 
        strcpy((*parent_info).request.data,"User not found");
        sendto ((*parent_info).sock, (void *) &(*parent_info).request, sizeof(struct request), 0, (struct sockaddr *) &(*parent_info).adr_client, sizeof((*parent_info).adr_client)); 
        break;
    }
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