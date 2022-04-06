#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>

#include <sys/msg.h>
#include <unistd.h>

#include "../utils/lectureSecurisee.h"
#include "../utils/request.h"
#include "../utils/signals.h"
#include "../utils/client-structures.h"

#if __APPLE__
    #define OPEN_BOARD "open ./output/board --env MSGID=%i"
#else
    #define OPEN_BOARD "export MSGID=%i; gnome-terminal -- \"./output/board\""
#endif


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

static int create_msg_pipe() {
    key_t cle = ftok("./output/board", 0);
    if (cle == -1) {
        perror("Unable to create file key");
        exit(EXIT_FAILURE);
    }
    int msgid = msgget(cle, IPC_CREAT|IPC_EXCL|0640);
    if (msgid == -1) {
        perror("Unable to create message pipe:");
        msgctl(msgid, IPC_RMID, NULL);
        exit(EXIT_FAILURE);
    }
    return msgid;
}

static void kill_board(int msgid) {
    stopSignal req = { 3, 0 };
    size_t s = sizeof(req) - sizeof(long);
    msgsnd(msgid, &req, s, 0);
}

int main(int argc, char const *argv[]) {
    // add signal handler for potentially-killing signals
    int signals[6] = {SIGSTOP, SIGABRT, SIGINT, SIGQUIT, SIGTERM, SIGTSTP};
    handle_signals(signals, sizeof(signals)/sizeof(signals[0]));

    // message pipe test
    int msgid = create_msg_pipe();    

    // launch board console in a new terminal
    char command[200];
    sprintf(command, OPEN_BOARD, msgid);
    if (system(command) != 0) {
        fprintf(stderr, "Unable to open the board console: abort\n");
        return EXIT_FAILURE;
    }

    // user joined the chat
    stopSignal req1 = {3, 1};
    msgsnd(msgid, &req1, sizeof(req1) - sizeof(long), 0);
    sleep(2);

    // zrunner says hello world
    messageSignal req2 = {1, "zrunner", "hello world!"};
    msgsnd(msgid, &req2, sizeof(req2) - sizeof(long), 0);
    sleep(1);
    
    // théo joined the chat
    moveSignal req3 = {2, "Théo", true};
    msgsnd(msgid, &req3, sizeof(req3) - sizeof(long), 0);
    sleep(1);

    // théo says salut
    messageSignal req4 = {1, "Théo", "Salut !"};
    msgsnd(msgid, &req4, sizeof(req4) - sizeof(long), 0);
    sleep(1);

    // user left the chat
    stopSignal req5 = {3, 2};
    msgsnd(msgid, &req5, sizeof(req5) - sizeof(long), 0);
    sleep(1);

    // close board
    kill_board(msgid);
    sleep(3);

    msgctl(msgid, IPC_RMID, NULL);

    /* ---UDP connection--- */
    struct request request;
    struct sockaddr_in adr_s, adr_c;
    unsigned int sock, lg;
    /* Request creation */
    request.type = 1;
    strcpy(request.data,"MyUser\tpassword");

    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // Creation socket
    /* Client adress init */
    bzero(&adr_c,sizeof(adr_c));
    adr_c.sin_family = AF_INET; 
    adr_c.sin_port = htons(UDP_PORT);
    adr_c.sin_addr.s_addr = htonl(INADDR_ANY);
    /* Server adress init */
    bzero(&adr_s,sizeof(adr_s));
    adr_s.sin_family = AF_INET;
    adr_s.sin_port = htons(UDP_PORT);
    adr_s.sin_addr.s_addr = htonl(INADDR_ANY);
    /* Attachement socket */
    bind(sock, (struct sockaddr *) &adr_c, sizeof(adr_c));
    /* Sending informations */

    /* Log in request */
    sendto (sock, (void *) &request, sizeof(struct request), 0, (struct sockaddr *) &adr_s, sizeof(adr_s)); 
    lg = sizeof(adr_s);
    if (recvfrom (sock, &request, sizeof(struct request), 0, (struct sockaddr *) &adr_s, &lg)>0){
        printf("%s\n",request.data);
    }
    char token[16];
    strcpy(token,request.data);

    sleep(3);

    /* User list */
    request.type = 0;
    sendto (sock, (void *) &request, sizeof(struct request), 0, (struct sockaddr *) &adr_s, sizeof(adr_s)); 
    lg = sizeof(adr_s);
    if (recvfrom (sock, &request, sizeof(struct request), 0, (struct sockaddr *) &adr_s, &lg)>0){
        printf("%s\n",request.data);
    }

    sleep(6);

    /* Log out request */
    request.type = -1;
    strcpy(request.data,token);
    sendto (sock, (void *) &request, sizeof(struct request), 0, (struct sockaddr *) &adr_s, sizeof(adr_s)); 
    lg = sizeof(adr_s);

    struct request response;
    ssize_t status = recvfrom(sock, &response, sizeof(struct request), 0, (struct sockaddr *) &adr_s, &lg);
    if (status == -1){
        printf("Unable to receive message\n");
        return EXIT_FAILURE;
    }
    //Close socket
    close(sock);

    return 0;
}
