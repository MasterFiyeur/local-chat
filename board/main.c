#include <stdio.h>
#include <unistd.h>

#include "../utils/client-structures.h"
#include "../utils/lectureSecurisee.h"

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
    printf("Hello I'm board where every message will be displayed !\n");
    int msgid = get_msgid();
    printf("msgid = %d\n", msgid);
    sleep(5);

    return 0;
}
