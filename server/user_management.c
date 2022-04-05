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




int nombreLignes(char* chemin) {
    FILE* fichier = fopen(chemin,"r");
    int res = 0;
    int caractere = 0;
    int ligne;
    int compte;
    if (fichier != NULL) {
        do {
            caractere = fgetc(fichier);
            if (caractere == 10) {res+=1;}
        } while (caractere != EOF);
    }
    fclose(fichier);

    return(res);
}


char** contenuOrganise(char* chemin) {
    char** res;
    int taille = nombreLignes(chemin);
    int ligne = MAX_USER_PASSWORD_LENGTH+MAX_USER_USERNAME_LENGTH+2;
    res = malloc(taille*sizeof(char*));
    for(int i=0;i<taille;i++) {
        res[i] = malloc(ligne*sizeof(char));
    }
    
    FILE* fichier = NULL;
    fichier = fopen(chemin,"r");
    if (fichier!=NULL) {
        for(int i = 0;i < taille;i++) {
            fgets(res[i],ligne,fichier);
        }
    }
    fclose(fichier);
    return(res);
}

int cherchePseudo(char* pseudo,char* chemin) {
    int taille = nombreLignes(chemin);
    char** couples = contenuOrganise(chemin);
    int i=0;
    int j=0;
    for(int k=0;k<taille;k++) {
        j=0;
        while (couples[k][j] != '\t') {
            if (pseudo[i] == couples[k][j]) {
                i += 1;
            }
            else {
                i = 0;
            }
            if (pseudo[i] == '\0') {
                return(k);
            }
            j+=1;
        }
    }
    free(couples);
    return(-1);
}
