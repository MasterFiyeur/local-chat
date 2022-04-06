// define functions used by board threads (one per message type)

#include "threads.h"
#include <stdio.h>
#include <sys/msg.h>

void collectMessages(int msgid) {
    messageSignal req;
    size_t size = sizeof(req) - sizeof(long);
    while (1) {
        if (msgrcv(msgid, &req, size, 1, 0) == -1) {
            perror("P1: Error receiving request");
            return;
        }
        printf("%s: %s\n", req.username, req.message);
    }
}

void collectMoves(int msgid) {
    moveSignal req;
    size_t size = sizeof(req) - sizeof(long);
    while (1) {
        if (msgrcv(msgid, &req, size, 2, 0) == -1) {
            perror("P2: Error receiving request");
            return;
        }
        if (req.is_join)
            printf("%s joined the chat\n", req.username);
        else
            printf("%s left the chat\n", req.username);
    }
}

void collectSignals(int msgid) {
    stopSignal req;
    size_t size = sizeof(req) - sizeof(long);
    while (1) {
        if (msgrcv(msgid, &req, size, 3, 0) == -1) {
            perror("P3: Error receiving request");
            return;
        }
        switch (req.signal) {
            case 0:
                printf("Closing console...\n");
                // exit(EXIT_SUCCESS);
                return;
            case 1:
                printf("You joined the chat\n");
                break;
            case 2:
                printf("You left the chat\n");
                break;
            default:
                printf("unknown signal\n");
        }
    }
}