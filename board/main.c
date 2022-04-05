#include <stdio.h>
#include <ctype.h>

#include "../utils/client-structures.h"

int main(int argc, char const *argv[])
{
    printf("Hello I'm board where every message will be displayed !\n");
    // fetch msg id
    char path[100];
    char *envvar = "MSGID";
    // Make sure envar actually exists
    if(!getenv(envvar)){
        fprintf(stderr, "The environment variable %s was not found.\n", envvar);
        exit(1);
    }

    // Make sure the buffer is large enough to hold the environment variable
    // value. 
    if(snprintf(path, 100, "%s", getenv(envvar)) >= 100){
        fprintf(stderr, "BUFSIZE of %d was too small. Aborting\n", 100);
        exit(1);
    }
    printf("%s: %s\n", envvar, path);

    return 0;
}
