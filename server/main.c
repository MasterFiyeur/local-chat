#include "../utils/lectureSecurisee.h"
#include "../utils/request.h"
#include "user_management.h"
#include "request_management.h"

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
    struct user *shared_memory = args; //Connected users
    unsigned int sock, lg = sizeof(struct sockaddr_in); //socket and adr_c size
    struct sockaddr_in adr_s, adr_c; //Server and client addresses

    //Function parameter furing thread creation
    void* thread_function = NULL;

    //Object sent to thread 
    struct request_processing arguments;

    //Request object
    struct request request;

    //Thread for request processing
    pthread_t request_thread;

    /* Socket init */
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    bzero(&adr_s,sizeof(adr_s)); 
    adr_s.sin_family = AF_INET;
    adr_s.sin_port = htons(UDP_PORT);
    adr_s.sin_addr.s_addr = htonl(INADDR_ANY);
    bind (sock, (struct sockaddr *) &adr_s, sizeof(adr_s)); // Attachement socket

    while (1){
        //Waiting for a new message
        if (recvfrom (sock, &request, sizeof(struct request), 0, (struct sockaddr *) &adr_c, &lg)){

            //request_processing object building
            arguments.adr_client = adr_c;
            arguments.request = request;
            arguments.shared_memory = shared_memory;
            arguments.sock = sock;

            switch (request.type){
                case 1: //log in
                    printf("[Request_manager] - Log in thread creation...\n");
                    thread_function = login; // function for log in
                    break;
                case -1://log out
                    printf("[Request_manager] - Log out thread creation...\n");

                    thread_function = logout; // function for log out
                    break;
                case 2://creation of account
                    printf("[Request_manager] - Account-creation thread creation...\n");

                    thread_function = account_creation; // function for create an account
                    break;
                case -2://deletion of account
                    printf("[Request_manager] - Account-deletion thread creation...\n");

                    thread_function = account_deletion; // function for delete an account
                    break;
                default://connected users list
                    printf("[Request_manager] - connected_users thread creation...\n");

                    thread_function = connected_users; // function send list of connected users
                    break;
            }
            /* Thread creation for request treatment */
            if (pthread_create( &request_thread, NULL, thread_function, &arguments))
                printf("\nError during request_thread creation\n");
            else
                pthread_detach(request_thread);
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
    
    //Init of random function (used for token generation)
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
    if (pthread_create( &com, NULL, communication, (void*)shared_memory))
        printf("\nError during thread creation\n");
    printf("Created\n");

    //Create gap between 2 threads
    sleep(1);

    /* Request manager thread creation */
    printf("Creation request thread...");
    if (pthread_create( &req, NULL, request_manager, (void*)shared_memory)) //Thread creation
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
