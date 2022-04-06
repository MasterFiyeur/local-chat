#include "commands.h"

int is_command(char* message, char* command){
    if((strncmp(message,command,strlen(command)) == 0) 
        && (message[strlen(command)] == ' ' || message[strlen(command)] == '\0')){
        return 1;
    }
    return 0;
}

void login(char message[REQUEST_DATA_MAX_LENGTH],char* token, struct sockaddr_in adr_s, struct sockaddr_in adr_c, int udp_socket, int tcp_socket){
    struct request request;
    unsigned int lg = sizeof(adr_s);
    /* Building request */
    request.type = 1;
    strcpy(request.data,&message[strlen(LOGIN_COMMAND)+1]);

    /* Log in request (UDP) */
    sendto (udp_socket, (void *) &request, sizeof(struct request), 0, (struct sockaddr *) &adr_s, sizeof(adr_s)); 

    if (recvfrom (udp_socket, &request, sizeof(struct request), 0, (struct sockaddr *) &adr_s, &lg)>0){
        if(request.type == 0){
            strcpy(token,request.data);
            write(tcp_socket, request.data, strlen(request.data));
        }else{
            printf("%s\n",request.data);
        }
    }
}

int commande_detection(char message[REQUEST_DATA_MAX_LENGTH], int* exit_status, char* token, int tcp_sock){
    /* ---UDP connection--- */
    struct sockaddr_in adr_s, adr_c; //server and client addresses
    unsigned int sock; //Socket

    if(strlen(message) > 0 && message[0] == '/'){
        /* Addresses init */
        //Client init
        bzero(&adr_c,sizeof(adr_c));
        adr_c.sin_family = AF_INET; 
        adr_c.sin_port = htons(UDP_PORT);
        adr_c.sin_addr.s_addr = htonl(INADDR_ANY);
        //Server init
        bzero(&adr_s,sizeof(adr_s));
        adr_s.sin_family = AF_INET;
        adr_s.sin_port = htons(UDP_PORT);
        adr_s.sin_addr.s_addr = htonl(INADDR_ANY);

        /* Socket creation and binding */
        sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        bind(sock, (struct sockaddr *) &adr_c, sizeof(adr_c));

        if (is_command(message,LOGIN_COMMAND)){
            if(message[strlen(LOGIN_COMMAND)] == '\0'){
                printf("Example use : /login MyUser MyPass\n");
            }else{
                //Necessite TCP_socket to send message
                login(message,&(*token), adr_s,adr_c, sock, tcp_sock);
            }
        }else if (is_command(message,LOGOUT_COMMAND)){
            printf("Command logout !\n");
        }else if (is_command(message,CREATE_ACCOUNT_COMMAND)){
            printf("Command create account\n");
        }else if (is_command(message,DELETE_ACCOUNT_COMMAND)){
            printf("Command delete account\n");
        }else if (is_command(message,LIST_COMMAND)){
            printf("Command list\n");
        }else if (is_command(message,EXIT_COMMAND)){
            *exit_status = 1;
        }else{
            printf("Command not recognized.\n");
        }
        return 1;
    }
    return 0;
}