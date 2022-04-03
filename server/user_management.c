#include "user_management.h"

int add_user(struct user *shared_memory, char username[MAX_USER_USERNAME_LENGTH], char ip_add[16]){
    int i = 0;

    //User creation
    struct user new_user;
    strcpy(new_user.username,username);
    strcpy(new_user.ip_add,ip_add);

    //Check unique username 
    for (i = 0; i < MAX_USERS_CONNECTED; i++)
    {
        if(strcmp(shared_memory[i].username, username)==0){
            return -1;
        }
    }
    for (i = 0; i < MAX_USERS_CONNECTED; i++)
    {
        if(strcmp(shared_memory[i].username, "")==0){
            shared_memory[i] = new_user;
            return 1;
        }
    }
    return 0;
}