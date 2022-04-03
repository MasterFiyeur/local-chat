#include "../utils/lectureSecurisee.h"
#include <sys/mman.h>

#define MAX_USERS_CONNECTED 3
#define MAX_USER_USERNAME_LENGTH 10

struct user{
    char username[MAX_USER_USERNAME_LENGTH]; //Username of the user
    char ip_add[16]; //IP address of the user 
};

/**
*\brief Add user to the shared_memory (array of connected users)
*
*\param shared_memory Array of connected users
*\param username Username of the user to add
*\param ip_add IP adress of the user to add
*\return -1 Username already taken
*\return 0 Users array is full (No index available)
*\return 1 User successfully added
*/
int add_user(struct user *shared_memory, char username[MAX_USER_USERNAME_LENGTH], char ip_add[16]){
    int i = 0;

    //User creation
    struct user new_user;
    strcpy(new_user.username,username);
    strcpy(new_user.ip_add,ip_add);

    //Check unique username 
    for (i = 0; i < MAX_USERS_CONNECTED; i++)
    {
        if(strcmp(shared_memory[i].username, username)==0){
            fprintf(stderr, "User %s already used.\n", username);
            return -1;
        }
    }
    for (i = 0; i < MAX_USERS_CONNECTED; i++)
    {
        if(strcmp(shared_memory[i].username, "")==0){
            shared_memory[i] = new_user;
            return 1;
        }
    }

    fprintf(stderr, "Connected users array is currently full.\n");
    return 0;
}

void *communication(void* args){
    struct user *shared_memory = args;
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
        printf("[Communication] - Adding user %s...\n", name);
        add_user(shared_memory, name, "127.0.0.1");
        sleep(2);
        i++;

    }
    pthread_exit(NULL);
}

void *request_manager(void* args){
    struct user *shared_memory = args;
    while (1)
    {
        //Print shared memory which is modified in communication thread
        printf("Request-manager] - Shared memory : [(%s,%s), (%s,%s), (%s,%s)]\n",
            shared_memory[0].username,shared_memory[0].ip_add,
            shared_memory[1].username,shared_memory[1].ip_add,
            shared_memory[2].username,shared_memory[2].ip_add
        );
        sleep(2);
    }
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    pthread_t com, req; //communication process and req process
    struct user *shared_memory; //Shared memory variable
    
    //Shared memory init
    shared_memory = mmap(NULL, MAX_USERS_CONNECTED*sizeof(struct user), (PROT_READ | PROT_WRITE), (MAP_SHARED | MAP_ANONYMOUS), -1, 0);
    //Init of users array to empty string as username and ip_add
    for (size_t i = 0; i < MAX_USERS_CONNECTED; i++){
        strcpy(shared_memory[i].username,"");
        strcpy(shared_memory[i].ip_add,"");
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

    //Unmap shared_memory
    munmap(shared_memory, MAX_USERS_CONNECTED*sizeof(char*));
    printf("Server finished.\n");
    return 0;
}
