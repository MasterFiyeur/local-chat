#include <stdio.h>
#include "../utils/lectureSecurisee.h"
#include "../utils/request.h"
#include "../utils/signals.h"


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

void *TCP_connexion(void* args){
    char message[REQUEST_DATA_MAX_LENGTH]; //Message wrote by user
    int sock = socket( AF_INET, SOCK_STREAM,0); //Client socket
    struct sockaddr_in adr_s; //Server address

    printf("I'm the TCP connexion\n");

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

    int end = 1;
    printf("/exit -> Quit the connexion \n");
    while (end == 1){
        saisieString(message, REQUEST_DATA_MAX_LENGTH);
        printf("Voici le message envoyé (%ld): %s\n",strlen(message),message);
        if (strcmp(message,"/exit")==0){
            end = 0;
        }else{
            write(sock, message, strlen(message));
        }
    }

    /* Properly end the client */
    close(sock);
    
    pthread_exit(NULL);
}



int main(int argc, char const *argv[]) {
    pthread_t tcp_connect; //TCP connection

    // add signal handler for potentially-killing signals
    int signals[6] = {SIGSTOP, SIGABRT, SIGINT, SIGQUIT, SIGTERM, SIGTSTP};
    //handle_signals(signals, sizeof(signals)/sizeof(signals[0]));
    printf("Hello I'm the client with pid %d !\n", getpid());

    /* ---UDP connection--- */
    // struct request request;
    // struct sockaddr_in adr_s, adr_c;
    // unsigned int sock, lg;
    // /* Request creation */
    // request.type = 1;
    // strcpy(request.data,"MyUser\tpassword");

    // sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // Creation socket
    // /* Client adress init */
    // bzero(&adr_c,sizeof(adr_c));
    // adr_c.sin_family = AF_INET; 
    // adr_c.sin_port = htons(UDP_PORT);
    // adr_c.sin_addr.s_addr = htonl(INADDR_ANY);
    // /* Server adress init */
    // bzero(&adr_s,sizeof(adr_s));
    // adr_s.sin_family = AF_INET;
    // adr_s.sin_port = htons(UDP_PORT);
    // adr_s.sin_addr.s_addr = htonl(INADDR_ANY);
    // /* Attachement socket */
    // bind(sock, (struct sockaddr *) &adr_c, sizeof(adr_c));
    // /* Sending informations */

    // /* Log in request */
    // sendto (sock, (void *) &request, sizeof(struct request), 0, (struct sockaddr *) &adr_s, sizeof(adr_s)); 
    // lg = sizeof(adr_s);
    // if (recvfrom (sock, &request, sizeof(struct request), 0, (struct sockaddr *) &adr_s, &lg)>0){
    //     printf("%s\n",request.data);
    // }
    // char token[16];
    // strcpy(token,request.data);

    // sleep(3);

    // /* User list */
    // request.type = 0;
    // sendto (sock, (void *) &request, sizeof(struct request), 0, (struct sockaddr *) &adr_s, sizeof(adr_s)); 
    // lg = sizeof(adr_s);
    // if (recvfrom (sock, &request, sizeof(struct request), 0, (struct sockaddr *) &adr_s, &lg)>0){
    //     printf("%s\n",request.data);
    // }

    // sleep(6);

    // /* Log out request */
    // request.type = -1;
    // strcpy(request.data,token);
    // sendto (sock, (void *) &request, sizeof(struct request), 0, (struct sockaddr *) &adr_s, sizeof(adr_s)); 
    // lg = sizeof(adr_s);

    // struct request response;
    // ssize_t status = recvfrom(sock, &response, sizeof(struct request), 0, (struct sockaddr *) &adr_s, &lg);
    // if (status == -1){
    //     printf("Unable to receive message\n");
    //     return EXIT_FAILURE;
    // }
    // //Close socket
    // close(sock);

    /* Creation of TCP connexion manager */
    printf("Creation TCP thread...");
    if (pthread_create( &tcp_connect, NULL, TCP_connexion, NULL))
        printf("\nError during thread creation\n");
    printf("Created\n");


    /* Join TCP connexion manager manager thread */
    pthread_join( tcp_connect, NULL);

    return 0;
}
