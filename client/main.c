#include <stdio.h>
#include "../utils/lectureSecurisee.h"
#include "../utils/request.h"
#include "../utils/signals.h"
#include "commands.h"


static void handler(int sig, siginfo_t *info, void *ctx) {
    printf("Received signal %s (%d) from PID: %d\n", get_signal_name(sig), sig, info->si_pid);
    // close()
}

static void handle_signals(int signals[], int count) {
    struct sigaction action;
    memset(&action, '\0', sizeof(action));
    action.sa_sigaction = &handler;

    for (int i=0; i<count; i++) {
        sigaction(signals[i], &action, NULL);
    }
}

/**
*\brief Thread which receive each message from the server and will transfer it to board processus
*
*\param socket TCP socket to listen for new messages
*\return void* Nothing
*/
void *receive_msg(void *socket)
{
    int sock = *((int *)socket);
    char message[REQUEST_DATA_MAX_LENGTH+MAX_USER_USERNAME_LENGTH+2];//Request data length + Max username length + ": "
    int len;
    // client thread always ready to receive message
    while((len = recv(sock,message,REQUEST_DATA_MAX_LENGTH+MAX_USER_USERNAME_LENGTH+2,0)) > 0) {
        message[len] = '\0';
        /* If connection ended */
        if(strcmp(message,LOGOUT_COMMAND) == 0){
            printf("[Message receiver] - Good Bye.\n");
            //TODO : end connexion to pipe
            break;
        }

        /* Send it to nommed pipe */
        printf("Message from the server : %s\n",message);
    }
    pthread_exit(NULL);
}

/**
*\brief Creation of TCP socket and interception of each connection to affect a thread to connexion
*
*\param args NULL
*\return void* Nothing
 */
void *TCP_connexion(void* args){
    char message[REQUEST_DATA_MAX_LENGTH]; //Message wrote by user
    int sock = socket( AF_INET, SOCK_STREAM,0); //Client socket
    struct sockaddr_in adr_s; //Server address
    int exit_status = 0;//Exit while condition
    pthread_t receiver; //Thread that will receive messages
    char token[TOKEN_SIZE]; //Connexion token
    strcpy(token,"");

    /* Server address init */
    bzero(&adr_s,sizeof(adr_s));
    adr_s.sin_port = htons(TCP_PORT);
    adr_s.sin_family= AF_INET;
    adr_s.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* Make the connexion */
    if ((connect( sock ,(struct sockaddr *)&adr_s,sizeof(adr_s))) == -1 ){
        printf("Connection to socket failed.\n");
        exit(0);
    }

    //Creating a thread for receive messages from server
    pthread_create(&receiver, NULL, receive_msg, &sock);
    printHelp();//Print help menu

    /* Sending messages */
    while (exit_status == 0){
        saisieString(message, REQUEST_DATA_MAX_LENGTH);
        if(commande_detection(message, &exit_status,&(*token),sock) == 0){//There is no command
            write(sock, message, strlen(message));
        }
    }

    /* Properly end the client */
    close(sock);
    printf("[TCP-connexion] - Connection ended !\n");
    pthread_exit(NULL);
}

int main(int argc, char const *argv[]) {
    pthread_t tcp_connect; //TCP connection

    // add signal handler for potentially-killing signals
    int signals[6] = {SIGSTOP, SIGABRT, SIGINT, SIGQUIT, SIGTERM, SIGTSTP};
    //handle_signals(signals, sizeof(signals)/sizeof(signals[0]));
    printf("Hello I'm the client with pid %d !\n", getpid());

    /* Creation of TCP connexion manager */
    printf("Creation TCP thread...");
    if (pthread_create( &tcp_connect, NULL, TCP_connexion, NULL))
        printf("\nError during thread creation\n");
    printf("Created\n");


    /* Join TCP connexion manager manager thread */
    pthread_join( tcp_connect, NULL);

    return 0;
}
