#include "../utils/lectureSecurisee.h"
#include <sys/mman.h>

#define MAX_USERS_CONNECTED 3
#define MAX_USER_USERNAME_LENGTH 10

struct user
{
    char username[16];
    char ip_add[16];
};



void *communication(void* args){
    char** shared_memory = args;
    int i = 1;
    char init[10];
    char num[3];
    char* name = malloc((MAX_USER_USERNAME_LENGTH+1)*sizeof(char));
    strcpy(init,"Theo");
    while (i)
    {
        //Update with Theo1, Theo2...
        strcpy(name,init);
        sprintf(num,"%d",i);
        strcat(name,num);
        //Modify shared_memory
        memcpy(shared_memory[(i-1)%3], name, sizeof(char)*(MAX_USER_USERNAME_LENGTH+1));

        printf("[Communication] - Writing %s to index %d in shared memory\n",name,(i-1)%3);
        sleep(2);
        i++;

    }
    pthread_exit(NULL);
}

void *request_manager(void* args){
    char** shared_memory = args;
    while (1)
    {
        //Print shared memory which is modified in communication thread
        printf("Request-manager] - Shared memory : [%s, %s, %s]\n",shared_memory[0],shared_memory[1],shared_memory[2]);
        sleep(2);
    }
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    pthread_t com, req; //communication process and req process
    char** shared_memory; //Shared memory variable
    
    //Shared memory init
    shared_memory = mmap(NULL, MAX_USERS_CONNECTED*sizeof(char*), (PROT_READ | PROT_WRITE), (MAP_SHARED | MAP_ANONYMOUS), -1, 0);
    for (size_t i = 0; i < MAX_USERS_CONNECTED; i++)
    {
        shared_memory[i] = malloc((MAX_USER_USERNAME_LENGTH+1)*sizeof(char));
    }
    
    printf("Hello I'm the server !\n");

    //Communication process creation
    printf("Creation communication thread...");
    if(pthread_create( &com, NULL, communication, (void*)shared_memory))
        printf("\nError during thread creation\n");
    printf("Created\n");

    //Create gap between 2 threads
    sleep(1);

    //Request manager process creation
    printf("Creation request thread...");
    if(pthread_create( &req, NULL, request_manager, (void*)shared_memory)) //Thread creation
        printf("\nError during thread creation\n");
    printf("Created\n");

    //Join communication and request manager threads
    pthread_join( com, NULL);
    pthread_join( req, NULL);

    //Free every string from shared_memory
    for (size_t i = 0; i < MAX_USERS_CONNECTED; i++)
    {
        free(shared_memory[i]);
    }
    //Unmap shared_memory
    munmap(shared_memory, MAX_USERS_CONNECTED*sizeof(char*));
    printf("Server finished.\n");
    return 0;
}
