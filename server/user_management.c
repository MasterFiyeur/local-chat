#include "user_management.h"

char* token_generation(){
    char *token;
    token = malloc(TOKEN_SIZE*sizeof(char));
    const char *alphanum = "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456789";
    for (size_t i = 0; i < TOKEN_SIZE-1; i++)
    {
        token[i] = alphanum[rand()%strlen(alphanum)];
    }
    return token;
}

int add_user(struct user *shared_memory, char username[MAX_USER_USERNAME_LENGTH], char** token){
    int i = 0;

    //User creation
    struct user new_user;
    strcpy(new_user.username,username);
    new_user.sock = 0;

    //Check unique username 
    for (i = 0; i < MAX_USERS_CONNECTED; i++)
    {
        if (strcmp(shared_memory[i].username, username)==0){
            return 1;
        }
    }
    for (i = 0; i < MAX_USERS_CONNECTED; i++)
    {
        if (strcmp(shared_memory[i].username, "")==0){
            strcpy(new_user.token,token_generation());
            strcpy(*token,new_user.token);
            shared_memory[i] = new_user;
            return 0;
        }
    }
    return 2;
}

int remove_user(struct user *shared_memory, char token[TOKEN_SIZE]){
    //Check all the shared memory to find which user has this token
    for (int i = 0; i < MAX_USERS_CONNECTED; i++){
        if (strcmp(shared_memory[i].token, token)==0){
            /* Reset access of this user */
            strcpy(shared_memory[i].token,"");
            strcpy(shared_memory[i].username,"");
            shared_memory[i].sock = 0;
            return 0;
        }
    }
    //User not found
    return 1;
}