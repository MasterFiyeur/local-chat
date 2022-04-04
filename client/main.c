#include <stdio.h>
#include <signal.h>
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


int main(int argc, char const *argv[]) {
    // add signal handler for potentially-killing signals
    int signals[6] = {SIGSTOP, SIGABRT, SIGINT, SIGQUIT, SIGTERM, SIGTSTP};
    handle_signals(signals, sizeof(signals)/sizeof(signals[0]));
    printf("Hello I'm the client with pid %d !\n", getpid());

    /* ---UDP connection--- */
    struct request request;
    struct sockaddr_in adr_s, adr_c;
    unsigned int sock, lg;
    /* Request creation */
    request.type = 0;
    strcpy(request.data,"MySuper/Password");

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
    if (bind(sock, (struct sockaddr *) &adr_c, sizeof(adr_c)) == -1) {
        printf("Unable to bind to server\n");
        return EXIT_FAILURE;
    }
    /* Sending informations */
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
