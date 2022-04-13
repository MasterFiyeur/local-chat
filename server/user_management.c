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

int add_user(struct user *shared_memory, char username[MAX_USER_USERNAME_LENGTH]){
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
            shared_memory[i] = new_user;
            return 0;
        }
    }
    return 2;
}



int numberOfLines(char* path) {
    FILE* file = fopen(path,"r");
    int res = 0;
    int target = 0;
    int line;
    if (file != NULL) {
        do {
            target = fgetc(file);
            if (target == 10) {res+=1;}
        } while (target != EOF);
    }
    fclose(file);

    return(res);
}


char** listOfCouples(char* path) {
    char** res;
    int length = numberOfLines(path);
    res = malloc(2*length*sizeof(char*));
    for(int i=0;i<length;i++) {
        res[2*i] = malloc(MAX_USER_USERNAME_LENGTH*sizeof(char));
        res[2*i+1] = malloc(MAX_USER_PASSWORD_LENGTH*sizeof(char));
    }
    
    FILE* file = NULL;
    file = fopen(path,"r");
    if (file!=NULL) {
        for(int i = 0;i < length;i++) {
            fscanf(file,"%s\t%s\n",res[2*i],res[2*i+1]);
        }
    }
    fclose(file);
    return(res);
}

int findNickname(char* nickname, char* password, char* path, int checkPass) { 
    /*checkpass : 0 -> doesn't check the password and returns the position of the nickname | 1 -> check the password and returns 0 if it doesn't fit, 1 if it fits*/
    int length = numberOfLines(path);
    char** couples = listOfCouples(path);
    for(int k=0;k<length;k++) {
        if (strcmp(couples[2*k],nickname) == 0) {
            if (checkPass == 0) {
                free(couples);
                return(k);
            }
            else if (checkPass == 1) {
                return((strcmp(couples[2*k+1],password)==0));
            }
        }
    }
    free(couples);
    return(-1);
}

void creation(char* nickname,char* password,char* path) {
    if (findNickname(nickname,"",path,0) == -1) {
        FILE* file = NULL;
        file = fopen(path,"a");
        if (file!=NULL) {
            fprintf(file,"%s\t%s\n",nickname,password);
        }
        fclose(file);
    }
    else {printf("The nickname already exists !\n");}
}

void delete(char* nickname,char* path){
    char** couples = listOfCouples(path);
    int length = numberOfLines(path);
    int var = findNickname(nickname,"",path,0);
    if (var != -1) {
        FILE* file = NULL;
        file = fopen(path,"w+");
        for (int i=0;i<length;i++) {
            if (i != var) {
                fprintf(file,"%s\t%s\n",couples[2*i],couples[2*i+1]);
            }
        }
        fclose(file);
    }
}