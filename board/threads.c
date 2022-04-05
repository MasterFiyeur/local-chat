// define functions used by board threads (one per message type)

#include "threads.h"
#include <stdio.h>
#include <sys/msg.h>

void collectMessages(int msgid) {
    messageSignal req;
    while (1) {
        if (msgrcv(msgid, &req, sizeof(req), 1, 0) == -1) {
            printf("P1: Erreur de réception de requête:");
            perror("");
            return;
        }
        printf("msg received from %s: %s\n", req.username, req.message);
    }
}

void collectKill(int msgid) {
    stopSignal req;
    while (1) {
        if (msgrcv(msgid, &req, sizeof(req), 3, 0) == -1) {
            printf("P3: Erreur de réception de requête:");
            perror("");
            return;
        }
        printf("P3: asked to stop process\n");
        // exit(EXIT_SUCCESS);
        break;
    }
}