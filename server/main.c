#include "../utils/lectureSecurisee.h"
#include "../utils/request.h"
#include "user_management.h"

/**
*\brief This function used by a thread will manage TCP connection for write and read messages between clients
    It should verify that the user is logged
*
*\param args [struct user *] shared memory of connected users with the request manager thread
*\return void* Nothing
 */
void *communication(void* args){
    struct user *shared_memory = args;
    while (1)
    {
        //Print shared memory which is modified in communication thread
        /*printf("[Communication] - Shared memory : [(%s,%d,%s), (%s,%d,%s), (%s,%d,%s)]\n",
            shared_memory[0].username, shared_memory[0].sock, shared_memory[0].token,
            shared_memory[1].username, shared_memory[1].sock, shared_memory[1].token,
            shared_memory[2].username, shared_memory[2].sock, shared_memory[2].token
        );*/
        sleep(2);
    }
    pthread_exit(NULL);
}

/**
*\brief This function used by a thread will manage UDP connection for login/logout, creation/suppression of user, liste of connected users 
*
*\param args [struct user *] shared memory of connected users with the communication thread
*\return void* Nothing
 */
void *request_manager(void* args){
    struct user *shared_memory = args;
    unsigned int sock, lg;
    struct sockaddr_in adr_s, adr_c;
    struct request request;

    /* Login used */
    char* username, password;
    char** splitted_str;

    /* Socket init */
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    bzero(&adr_s,sizeof(adr_s)); 
    adr_s.sin_family = AF_INET;
    adr_s.sin_port = htons(UDP_PORT);
    adr_s.sin_addr.s_addr = htonl(INADDR_ANY);
    bind (sock, (struct sockaddr *) &adr_s, sizeof(adr_s)); // Attachement socket

    while (1)
    {
        lg = sizeof(adr_c);
        if(recvfrom (sock, &request, sizeof(struct request), 0, (struct sockaddr *) &adr_c, &lg)){
            printf("J'ai reçu un message de type : %d avec les données suivantes : %s\n",request.type, request.data);

            switch (request.type)
            {
            case 1: //log in
                /*splitted_str = str_split(request.data,'/');
                if(*(splitted_str) && *(splitted_str + 1)){
                    password = *(splitted_str + 1);
                    username = *(splitted_str);
                    printf("Username received (%ld): %s\nPassword received (%ld): %s\n", strlen(username), username, strlen(password), password);
                }*/
                printf("Case login\n");
                break;
            
            default:
                //Send user's list
                break;
            }
        }
    }
    /* Close socket */
    close(sock);
    /* Exit thread */
    pthread_exit(NULL);
}

int main(int argc, char const *argv[])
{
    pthread_t com, req; //communication process and request manager process
    struct user *shared_memory; //Shared memory variable (connected users)
    
    //Init of random function (ex : token generation)
    srand(time(NULL));

    /* Shared memory of connected users initialization */
    shared_memory = mmap(NULL, MAX_USERS_CONNECTED*sizeof(struct user), (PROT_READ | PROT_WRITE), (MAP_SHARED | MAP_ANONYMOUS), -1, 0); //Shared memory init
    //Init of users array to empty string as username and ip_add
    for (size_t i = 0; i < MAX_USERS_CONNECTED; i++){
        strcpy(shared_memory[i].username,"");
        strcpy(shared_memory[i].token,"");
        shared_memory[i].sock = 0;
    }

    
    printf("Hello I'm the server !\n");

    /* Communication thread creation */
    printf("Creation communication thread...");
    if(pthread_create( &com, NULL, communication, (void*)shared_memory))
        printf("\nError during thread creation\n");
    printf("Created\n");

    //Create gap between 2 threads
    sleep(1);

    /* Request manager thread creation */
    printf("Creation request thread...");
    if(pthread_create( &req, NULL, request_manager, (void*)shared_memory)) //Thread creation
        printf("\nError during thread creation\n");
    printf("Created\n");

    /* Join communication and request manager threads */
    pthread_join( com, NULL);
    pthread_join( req, NULL);

    /* Unmap shared_memory */
    munmap(shared_memory, MAX_USERS_CONNECTED*sizeof(char*));

    printf("Server finished.\n");
    return 0;
}
