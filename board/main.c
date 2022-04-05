#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>

#include "../utils/client-structures.h"
#include "../utils/lectureSecurisee.h"
#include "./threads.h"

int get_msgid() {
    int buffer_size = 100;
    char msgid_str[buffer_size];
    char *envvar = "MSGID";
    // Make sure envar actually exists
    if(!getenv(envvar)){
        fprintf(stderr, "The environment variable %s was not found.\n", envvar);
        exit(1);
    }

    // Make sure the buffer is large enough to hold the environment variable value.
    if(snprintf(msgid_str, buffer_size, "%s", getenv(envvar)) >= buffer_size){
        fprintf(stderr, "BUFSIZE of %d was too small. Aborting\n", buffer_size);
        exit(1);
    }
    // Make sure the env value is actually a usable integer
    if (!isNumber(msgid_str)) {
        fprintf(stderr, "%s value is not a valid integer. Aborting\n", msgid_str);
        exit(1);
    }
    return atoi(msgid_str);
}

int main(int argc, char const *argv[])
{
    int msgid = get_msgid();
    
    // create threads to receive messages
    pid_t pid1, pid2, pid3;
    switch ((pid1 = fork())) {
        case 0: // child 1
            collectMessages(msgid);
            break;
        default:
            switch ((pid2 = fork())) {
                case 0: // child 2
                    // TODO
                    break;
                default:
                    switch ((pid3 = fork())) {
                        case 0: // child 3
                            collectKill(msgid);
                            break;
                        default: // parent
                            printf("");
                            int status;
                            // waitpid(pid1, &status, 0);
                            // printf("HEY %d\n", status);
                            // waitpid(pid2, &status, 0);
                            // printf("HEY2 %d\n", status);
                            waitpid(pid3, &status, 0);
                            // only pid3 needs to be waited, as he is
                            // the one receiving the KILL signal from client
                            printf("\n");
                            exit(EXIT_SUCCESS);
                    }
            }
    }

    return 0;
}
