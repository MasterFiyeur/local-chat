#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

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
    sleep(10);
    return 0;
}
