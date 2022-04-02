#include "../utils/lectureSecurisee.h"

void *communication(void* args){
    while (1)
    {
        sleep(2);
        printf("[Communication] - I'm the communication thread\n");
    }
    pthread_exit(NULL);
}

void *request_manager(void* args){
    while (1)
    {
        sleep(3);
        printf("[Request-manager] - I'm the request manager thread\n");
    }
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    pthread_t com, req; //communication process and req process
    printf("Hello I'm the server !\n");

    //Communication process creation
    printf("Creation communication thread...");
    if(pthread_create( &com, NULL, communication, NULL))
        printf("\nError during thread creation\n");
    printf("Created\n");

    //Request manager process creation
    printf("Creation request thread...");
    if(pthread_create( &req, NULL, request_manager, NULL)) //Thread creation
        printf("\nError during thread creation\n");
    printf("Created\n");


    pthread_join( com, NULL);
    pthread_join( req, NULL);
    printf("Server finished.\n");
    return 0;
}
