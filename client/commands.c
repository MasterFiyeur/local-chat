#include "commands.h"

int is_command(char* message, char* command){
    if((strncmp(message,command,strlen(command)) == 0) 
        && (message[strlen(command)] == ' ' || message[strlen(command)] == '\0')){
        return 1;
    }
    return 0;
}


int commande_detection(char message[REQUEST_DATA_MAX_LENGTH], int* exit_status){

    if(strlen(message) > 0 && message[0] == '/'){
        if (is_command(message,LOGIN_COMMAND)){
            if(message[strlen(LOGIN_COMMAND)] == '\0'){
                printf("Example use : /login MyUser MyPass\n");
            }else{
                printf("Command login !\n");
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